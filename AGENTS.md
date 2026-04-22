# Agents Working Documentation

This document provides comprehensive details for agents working on reimplementing build123d's CAD functionalities using godot-cpp and OpenCASCADE.

## Project Overview

- **Goal**: Reimplement build123d (https://github.com/gumyr/build123d) as a Godot GDExtension
- **Backend**: OpenCASCADE Technology (OCCT) - the same kernel used by build123d
- **Language**: C++ with godot-cpp bindings
- **Build System**: CMake + vcpkg

## Project Structure

```
build123d.gd/
├── src/                    # C++ wrapper classes
│   ├── OpenCascadeVersion.h/.cpp  # Already implemented
│   ├── register_types.h/.cpp     # Auto-generated registration
│   └── register_types.sh          # Script to regenerate registration
├── demo/                   # Godot demo project
│   ├── tests/              # GDScript test files
│   └── addons/build123d.gd/  # Built extension (.so/.dll)
├── vcpkg/                 # vcpkg installation
├── vcpkg_ports/           # Custom vcpkg ports
├── vcpkg_triplets/        # Compiler triplet configs
├── CMakeLists.txt        # Build configuration
└── validate.sh           # Test runner script
```

## Adding New Functionality

Follow this workflow for each new class/feature:

### 1. Create C++ Class Headers in `src/`

Each wrapper class should:
- Inherit from `godot::RefCounted` (or appropriate godot type)
- Use `GDCLASS(ClassName, godot::RefCounted)` macro
- Define binding in `_bind_methods()` using `ClassDB::bind_method()`
- Implement methods that call OpenCASCADE APIs

**Example structure**:
```cpp
// src/GeometryVector.h
#ifndef GEOMETRY_VECTOR_H
#define GEOMETRY_VECTOR_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <gp_Vec.hxx>

class GeometryVector : public godot::RefCounted {
    GDCLASS(GeometryVector, godot::RefCounted)

protected:
    static void _bind_methods() {...}

public:
    gp_Vec occt_vector;
    
    // Constructor from Godot Vector3
    static GeometryVector* create(godot::Vector3 v);
    
    godot::Vector3 to_godot_vector3() const;
    double length() const;
    // ... more methods
};

#endif
```

### 2. Add to register_types.cpp with register_types.sh

Run the regeneration script:
```bash
./src/register_types.sh
```

### 3. Write docs for class

Write `./doc_classes/<ClassName>.xml` with comprehensive and accurate documentation. See `./doc_classes/OpenCascadeVersion.xml` for an example and see `https://docs.godotengine.org/en/stable/engine_details/class_reference/index.html` for more information.

### 4. Create Tests

Add test files in `demo/tests/`:
- Filename: `test_<feature>.gd`
- Functions: `static func test_<name>() -> String` returning error message or empty string for pass.

```gdscript
class_name TestFeatureName

static func test_example() -> String:
    var obj := MyClass.new()
    # Test code...
    var result := obj.some_method()
    obj.free()
    
    if result == expected:
        return ""
    return "Expected %s but got %s" % [expected, result]
```

### 5. Run Tests

```bash
GODOT_VERSION=system ./validate.sh /tmp/errors.log >/tmp/output.log
```

## OpenCASCADE Integration

### Available OCCT Headers

The following OCCT modules are available (found via vcpkg):

- `gp` - Geometric Primitives (Vec, Dir, Axis, Plane, Trsf, Mat, etc.)
- `GC` - Geometers Construction (MakeArc, MakeCircle, MakeLine, etc.)
- `Geom` - Geometry (Curve, Surface, BezierCurve, BSplineCurve, etc.)
- `TopoDS` - Topology (TopoDS_Shape, TopoDS_Vertex, TopoDS_Edge, etc.)
- `BRep` - BREP Framework (BRepBuilderAPI, BRepAlgoAPI, BRepFilletAPI, etc.)
- `STEP` - STEP file reading/writing
- `StlMesh` - STL reading/writing
- `Bnd` - Bounding boxes

### Key OCCT Classes to Wrap

Based on build123d's functionality:

#### 1. Geometry Classes (Geometry/)
| build123d Class | Description | OCCT Class |
|---------------|-------------|-----------|
| Vector | 3D vector | `gp_Vec`, `gp_Dir` |
| Plane | Work plane | `gp_Pln`, `Geom_Plane` |
| Axis | X/Y/Z axis | `gp_Ax1`, `gp_Ax2`, `gp_Ax3` |
| Location | Position+orientation | `gp_Trsf`, `TopLoc_Location` |

#### 2. Topology Classes (Topology/)
| build123d Class | Description | OCCT Class |
|---------------|-------------|-----------|
| Vertex | 0D point | `TopoDS_Vertex`, `BRep_Tool` |
| Edge | 1D curve | `TopoDS_Edge` |
| Wire | Connected edges | `TopoDS_Wire` |
| Face | 2D surface | `TopoDS_Face` |
| Shell | Connected faces | `TopoDS_Shell` |
| Solid | 3D volume | `TopoDS_Solid` |
| Compound | Collection | `TopoDS_Compound` |

#### 3. 2D Objects (Objects2D/)
| build123d Class | Description | OCCT Class |
|---------------|-------------|-----------|
| Line | Straight line | `Geom_Line`, `GC_MakeLine` |
| Circle | Circle arc | `Geom_Circle`, `GC_MakeCircle` |
| Ellipse | Ellipse arc | `Geom_Ellipse`, `GC_MakeEllipse` |
| Spline | Bezier/Spline | `Geom_BSplineCurve` |
| Bezier | Bezier curve | `Geom_BezierCurve` |
| Arc | Circular arc | `Geom_Circle` segment |
| Polygon | Multi-segment | `TopoDS_Wire` closed |
| Rectangle | Rectangle | Lines |
| RectangleRounded | Rounded rect | Lines + arcs |

#### 4. 3D Objects (Objects3D/)
| build123d Class | Description | OCCT Class |
|---------------|-------------|-----------|
| Box | Rectangular box | `BRepPrimAPI_MakeBox` |
| Cylinder | Cylinder | `BRepPrimAPI_MakeCylinder` |
| Cone | Cone | `BRepPrimAPI_MakeCone` |
| Sphere | Sphere | `BRepPrimAPI_MakeSphere` |
| Torus | Torus | `BRepPrimAPI_MakeTorus` |
| Wedge | Wedge | `BRepPrimAPI_MakeWedge` |

#### 5. Operations (Operations/)
| build123d Method | Description | OCCT Class |
|-----------------|-------------|-----------|
| extrude | Extrude sketch | `BRepPrimAPI_MakeSweep` |
| revolve | Revolve sketch | `BRepPrimAPI_MakeRevolution` |
| loft | Blend surfaces | `BRepFill_API_ShapeToFace` or `BRepOffsetAPI_MakeLoft` |
| sweep | Sweep along path | `BRepBuilderAPI_Sweep` |
| sweep_with_guide | Sweep with guide | `BRepFill_Sweep` |
| offset | Offset geometry | `BRepOffsetAPI_MakeOffset` |
| offset2d | 2D offset | `GCE2d_MakeOffset` |
| split | Split object | `BRepCut_API` or `BRepSplit` |

#### 6. Boolean Operations (Boolean/)
| build123d Method | Description | OCCT Class |
|-----------------|-------------|-----------|
| fuse | Union | `BRepAlgoAPI_Fuse` |
| cut | Subtraction | `BRepAlgoAPI_Cut` |
| common | Intersection | `BRepAlgoAPI_Common` |
| cut_all | Multiple cuts | `BRepAlgoAPI_Cut` loop |
| split | Split with tools | `BRepAlgoAPI_Section` |

#### 7. Fillets/Chamfers (Fillets/)
| build123d Method | Description | OCCT Class |
|-----------------|-------------|-----------|
| fillet | Round edges | `BRepFilletAPI_MakeFillet` |
| chamfer | Bevel edges | `BRepChamferAPI_MakeChamfer` |

#### 8. Selectors
- Need to implement flexible querying of topology
- Use `TopExp_Explorer` for traversing topology
- Filter by geometry type, normal direction, etc.

#### 9. Import/Export
| Format | OCCT Class |
|--------|-----------|
| STEP | `STEPControl_Reader`, `STEPControl_Writer` |
| STL | `StlMesh_Mesh`, `RWMesh` |
| IGES | `IGESControl_Reader`, `IGESControl_Writer` |
| BREP | `BRepTools` |

## Important Details

### Memory Management
- OCCT uses native handles (`Handle<TopoDS_Shape>`)
- Must properly manage memory to avoid leaks
- Use Godot's reference counting where possible

### Error Handling
- OCCT exceptions: catch with `Standard_Failure`
- Return error messages as `String` in tests for failures

### Thread Safety
- OCCT is generally thread-safe
- Check godot-cpp threading model

### Naming Conventions
- Classes: `PascalCase` e.g., `GeometryVector`
- Methods: `camelCase` e.g., `getVersionString`
- GDScript: `snake_case` when exposed via godot-cpp

## Documentation References

- Build123d: https://build123d.readthedocs.io/
- Build123d GitHub: https://github.com/gumyr/build123d
- Godot GDExtension: https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/
- godot-cpp: https://github.com/godotengine/godot-cpp
- OpenCASCADE: https://dev.opencascade.org/doc/overview

## Current Status

- `OpenCascadeVersion` class implemented and tested
- Test runner passes
- Project structure ready for expanded functionality
