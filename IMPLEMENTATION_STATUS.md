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

## Next In Progress

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
