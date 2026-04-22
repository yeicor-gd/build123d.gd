# Implementation Status

This repository is being extended incrementally toward build123d-style CAD functionality on top of Godot GDExtension and OpenCASCADE.

## Current Strategy

Build the API in vertical slices, keeping the project passing `validate.sh` after each slice:

1. Foundational math and shape wrappers
2. Primitive solids and sketches
3. Boolean and transform operations
4. Topology inspection and selectors
5. Import/export
6. Higher-level build123d-style construction helpers

## Completed

- `OpenCascadeVersion` baseline wrapper and tests
- Project build/test pipeline

### Slice 1: Core wrappers

Implemented:

- `GeometryVector` backed by `gp_Vec`
- `TopoShape` backed by `TopoDS_Shape`
- `SolidBox` backed by `BRepPrimAPI_MakeBox`
- boolean operations: `fuse`, `cut`, `common`
- measurements: volume, surface area, center of mass, axis-aligned bounds
- regression coverage for vector math, primitive construction, and boolean volumes
- registration generator updated to register inherited `GDCLASS` types in parent-before-child order

Validation status:

- `GODOT_VERSION=system ./validate.sh /tmp/errors.log >/tmp/verbose_output.log` passes

## Completed

### Slice 2: Interchange and Mesh Conversion

Goal: make the OCCT-backed shapes practical in Godot by supporting robust CAD interchange and render-mesh generation.

Implemented:

- STEP import/export from file paths and byte buffers on `TopoShape`
- STL import/export from file paths and byte buffers on `TopoShape`
- `TopoShape.to_array_mesh()` using OCCT triangulation
- regression coverage for STEP round-trips, STL round-trips, and mesh conversion

Current blocker:

- BREP import/export was investigated and partially implemented, but OCCT serialization paths in this build still crash under repeated in-process use. The public API for BREP has been deferred until a stable approach is identified.

Planned validation:

- STEP file/byte round-trip tests
- STL file/byte round-trip tests
- mesh AABB and surface generation tests

Validation status:

- `GODOT_VERSION=system ./validate.sh /tmp/errors.log >/tmp/verbose_output.log` passes

## Completed

### Slice 3: More Solids and Basic Transforms

Goal: keep extending the low-level modeling surface with reusable primitives and shape transforms.

Implemented:

- `TopoShape.translated()`
- `TopoShape.rotated()`
- `TopoShape.scaled()`
- `SolidCylinder`
- `SolidSphere`
- `SolidCone`

Planned validation:

- primitive volume and bounding-box tests
- transform invariants and transformed bounds tests

Validation status:

- `GODOT_VERSION=system ./validate.sh /tmp/errors.log >/tmp/verbose_output.log` passes

## Next In Progress

### Slice 4: Typed Topology and Placement Helpers

Goal: move toward build123d’s richer modeling API with typed topology wrappers and placement/orientation helpers.

Implemented in progress:

- `Vertex` wrapper with direct point construction and inspection
- `Edge` wrapper with line construction, endpoint inspection, length, and polyline sampling
- `Wire` wrapper with polygon construction, closure/length inspection, ordered edge traversal, and stitched polyline extraction
- `Face` wrapper with wire/polygon construction, planarity checks, outer-wire extraction, and representative normal access
- `Solid` wrapper with closure and shell-count inspection, now serving as the common base for solid primitives
- `Axis` helper backed by `gp_Ax1`
- `CadPlane` helper backed by `gp_Pln` to avoid colliding with Godot's built-in `Plane` type
- `Location` helper backed by `gp_Trsf`
- `TopoShape.get_vertices()` and `TopoShape.get_edges()` for unique typed topology extraction
- `TopoShape.get_wires()` for unique typed wire extraction
- `TopoShape.get_faces()` for unique typed face extraction
- `TopoShape.get_solids()` for unique typed solid extraction
- `TopoShape.get_vertex_positions()` for direct point extraction from topological vertices
- `TopoShape.get_edge_polylines(deflection)` for direct edge sampling without forcing mesh conversion
- `TopoShape.located()` for applying reusable placement transforms

Why this slice starts here:

- it exposes topology-native data immediately in Godot
- it keeps non-mesh workflows practical for vertices and edges
- it provides a stable base for future typed `Wire`, `Face`, and `Solid` wrappers

Planned classes:

- `Vertex`, `Edge`, `Wire`, `Face`, `Solid`
- `Axis`, `Plane`, `Location`

Planned validation:

- topology extraction tests for vertices and edges
- wire construction and wire extraction tests
- face construction and face extraction tests
- solid extraction and solid-wrapper tests
- axis/location construction and transform tests
- plane construction, projection, and transform tests
- typed wrapper construction and inspection tests
- placement and orientation tests

## Next Likely Slices

- typed topology wrappers (`Vertex`, `Edge`, `Wire`, `Face`, `Solid`)
- transforms (`translate`, `rotate`, `mirror`)
- more 3D primitives (`Cylinder`, `Sphere`, `Cone`)
- profile construction (`Line`, `Circle`, `Rectangle`, `Polygon`)
- feature operations (`extrude`, `revolve`, `loft`, `sweep`)
- import/export and selectors

## Notes For Resuming

- Prefer adding small, tested OCCT-backed capabilities instead of broad stubs.
- Keep names stable and documented in `doc_classes/`.
- Regenerate `src/register_types.cpp` and `src/register_types.h` with `./src/register_types.sh` after adding any `GDCLASS`.
