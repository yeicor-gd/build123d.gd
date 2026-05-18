# Implementation Status

This repository is being extended toward build123d-style CAD functionality on top of Godot GDExtension and OpenCASCADE.

## Working Rules

- Stay build123d-first. Do not expand the OCCT surface just because it exists.
- Keep each slice small, tested, and documented.
- Validate `doc_classes/*.xml` against `scripts/validate-doc_classes.xsd` before and after each doc change.
- Validate doc names against the bound C++ class/method/property/signal definitions before each merge.
- Keep `validate.sh` green after every meaningful change.
- Fix docs immediately if the editor/doc generator complains.

## Completed Foundation

- `OpenCascadeVersion` baseline wrapper and tests
- Core math and placement helpers: `GeometryVector`, `Axis`, `Location`, `CadPlane`
- Core topology wrappers: `TopoShape`, `Vertex`, `Edge`, `Wire`, `Face`, `Shell`, `Solid`, `Compound`
- Primitive solids: `SolidBox`, `SolidCone`, `SolidCylinder`, `SolidSphere`, `SolidTorus`, `SolidWedge`
- Profile primitives: `RectangleWire`, `RectangleRoundedWire`, `CircleWire`, `EllipseWire`, `RegularPolygonWire`, `SlotOverallWire`, `PolygonWire`
- Shape operations: translate, rotate, scale, mirror, locate, extrude, revolve, loft, sweep, and 2D offset
- Boolean operations: pairwise fuse, cut, common, plus array-based multi-shape helpers
- Measurements and inspection: volume, surface area, center of mass, bounds, typed topology extraction, and edge sampling
- Import/export: STEP and STL file and byte round-trips
- Mesh conversion: `TopoShape.to_array_mesh()`
- Registration regeneration: `src/register_types.sh`

## Current Focus

1. Keep documentation valid on all platforms before adding new features.
2. Fill the remaining build123d modeling gaps in small slices.
3. Add tests alongside each new public API.

## Next Build123d Slices

1. Selectors and topology queries for face, edge, vertex, and orientation-based filtering
2. Higher-level construction helpers such as `extrude`, `revolve`, `loft`, and `sweep` polish
3. Additional import/export behavior only when build123d needs it and the implementation is stable
4. Convenience helpers that directly support build123d use cases, not broad OCCT coverage

## Deferred For Now

- Exhaustive OCCT wrapper coverage
- Rare constructors and niche kernel APIs that do not support build123d parity
- New public methods without tests and doc updates
