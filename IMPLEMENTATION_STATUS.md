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

### Slice 2: Typed topology and transforms

Goal: build on `TopoShape` with more shape-specialized and transform-oriented APIs.

Planned classes:

- `Vertex`, `Edge`, `Wire`, `Face`, `Solid`
- `Plane`, `Axis`, `Location`
- transform helpers on shapes (`translate`, `rotate`, `mirror`)

Planned validation:

- shape transform tests
- typed wrapper construction tests
- additional primitive tests (`Cylinder`, `Sphere`, `Cone`)

## Next Likely Slices

- profile construction (`Line`, `Circle`, `Rectangle`, `Polygon`)
- feature operations (`extrude`, `revolve`, `loft`, `sweep`)
- import/export and selectors

## Notes For Resuming

- Prefer adding small, tested OCCT-backed capabilities instead of broad stubs.
- Keep names stable and documented in `doc_classes/`.
- Regenerate `src/register_types.cpp` and `src/register_types.h` with `./src/register_types.sh` after adding any `GDCLASS`.
