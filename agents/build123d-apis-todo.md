[x] Axis(*args, **kwargs)
[x] Axis.**copy**() -> Axis
[x] Axis.**deepcopy**(_memo) -> Axis
[-] Axis.**neg**() -> Axis
[x] Axis.angle_between(other: Axis) -> float
[-] Axis.direction: unknown
[x] Axis.intersect(*args, **kwargs)
[ ] Axis.is_coaxial(other: Axis, angular_tolerance: float = 1e-05, linear_tolerance: float = 1e-05) -> bool
[ ] Axis.is_normal(other: Axis, angular_tolerance: float = 1e-05) -> bool
[ ] Axis.is_opposite(other: Axis, angular_tolerance: float = 1e-05) -> bool
[ ] Axis.is_parallel(other: Axis, angular_tolerance: float = 1e-05) -> bool
[ ] Axis.is_skew(other: Axis, tolerance: float = 1e-05) -> bool
[ ] Axis.located(new_location: Location)
[ ] Axis.location: unknown
[ ] Axis.position: unknown
[ ] Axis.reverse() -> Axis
[ ] Axis.to_plane() -> Plane
[ ] BoundBox(*args, **kwargs)
[ ] BoundBox.add(obj: tuple[float, float, float] | Vector | BoundBox, tol: float | None = None) -> BoundBox
[ ] BoundBox.center() -> Vector
[ ] BoundBox.diagonal: unknown
[ ] BoundBox.find_outside_box_2d(bb1: BoundBox, bb2: BoundBox) -> BoundBox | None
[ ] BoundBox.from_topo_ds(shape: TopoDS_Shape, tolerance: float | None = None, optimal: bool = True) -> BoundBox
[ ] BoundBox.is_inside(second_box: BoundBox) -> bool
[ ] BoundBox.measure: unknown
[ ] BoundBox.overlaps(other: BoundBox, tolerance: float = 1e-06) -> bool
[ ] BoundBox.to_align_offset(align: Align | None | tuple[Align | None, Align | None] | tuple[Align | None, Align | None, Align | None]) -> Vector
[ ] Color(*args, **kwargs)
[ ] Color.**copy**() -> Color
[ ] Color.**deepcopy**(_memo) -> Color
[ ] Color.categorical_set(color_count: int, starting_hue: str | tuple[str, float | int] | tuple[float | int, float | int, float | int] | tuple[float | int, float | int, float | int, float | int] | int | tuple[int, int] | Color | Quantity_ColorRGBA | float = 0.0, alpha: float | Iterable[float] = 1.0) -> list[Color]
[ ] Location(*args, **kwargs)
[ ] Location.**copy**() -> Location
[ ] Location.**deepcopy**(_memo) -> Location
[ ] Location.**eq**(other: object) -> bool
[ ] Location.**mul**(other: Location | Iterable[Location]) -> Location | list[Location]
[ ] Location.**neg**() -> Location
[ ] Location.**pow**(exponent: int) -> Location
[ ] Location.center() -> Vector
[ ] Location.intersect(*args, **kwargs)
[ ] Location.inverse() -> Location
[ ] Location.mirror(mirror_plane: Plane) -> Location
[ ] Location.orientation: unknown
[ ] Location.position: unknown
[ ] Location.to_axis() -> Axis
[ ] Location.to_tuple() -> tuple[tuple[float, float, float], tuple[float, float, float]]
[ ] Location.x_axis: unknown
[ ] Location.y_axis: unknown
[ ] Location.z_axis: unknown
[ ] LocationEncoder(*, skipkeys=False, ensure_ascii=True, check_circular=True, allow_nan=True, sort_keys=False, indent=None, separators=None, default=None)
[ ] LocationEncoder.default(o: Location) -> dict
[ ] LocationEncoder.location_hook(obj) -> dict
[ ] Pos(*args, **kwargs)
[ ] Rot()
[ ] Matrix(*args, **kwargs)
[ ] Matrix.**copy**() -> Matrix
[ ] Matrix.**deepcopy**(_memo) -> Matrix
[ ] Matrix.inverse() -> Matrix
[ ] Matrix.multiply(other)
[ ] Matrix.rotate(axis: Axis, angle: float)
[ ] Matrix.transposed_list() -> Sequence[float]
[ ] Plane(*args, **kwargs)
[ ] Plane.**copy**() -> Plane
[ ] Plane.**deepcopy**(_memo) -> Plane
[ ] Plane.**eq**(other: object)
[ ] Plane.**mul**(other: Location | Plane | Iterable[Location | Plane]) -> Location | list[Location]
[ ] Plane.**neg**() -> Plane
[ ] Plane.contains(obj: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | Axis, tolerance: float = 1e-06) -> bool
[ ] Plane.from_local_coords(obj: tuple | Vector | Any | BoundBox)
[ ] Plane.get_topods_face_normal(face: TopoDS_Face) -> Vector
[ ] Plane.intersect(*args, **kwargs)
[ ] Plane.location: unknown
[ ] Plane.location_between(other: Plane) -> Location
[ ] Plane.move(loc: Location | Plane) -> Plane
[ ] Plane.moved(loc: Location | Plane) -> Plane
[ ] Plane.offset(amount: float) -> Plane
[ ] Plane.origin: unknown
[ ] Plane.reverse() -> Plane
[ ] Plane.rotated(rotation: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 0), ordering: Extrinsic | Intrinsic | None = None) -> Plane
[ ] Plane.shift_origin(locator: Axis | VectorLike | Vertex) -> Plane
[ ] Plane.to_gp_ax2() -> gp_Ax2
[ ] Plane.to_local_coords(obj: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | Any | BoundBox)
[ ] Rotation(*args, **kwargs)
[ ] Vector(*args, **kwargs)
[ ] Vector.X: unknown
[ ] Vector.Y: unknown
[ ] Vector.Z: unknown
[ ] Vector.**abs**() -> float
[ ] Vector.**add**(vec: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Vector
[ ] Vector.**copy**() -> Vector
[ ] Vector.**deepcopy**(_memo) -> Vector
[ ] Vector.**eq**(other: object) -> bool
[ ] Vector.**mul**(scale: float) -> Vector
[ ] Vector.**neg**() -> Vector
[ ] Vector.**rmul**(scale: float) -> Vector
[ ] Vector.**sub**(vec: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Vector
[ ] Vector.**truediv**(denom: float) -> Vector
[ ] Vector.add(vec: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Vector
[ ] Vector.center() -> Vector
[ ] Vector.cross(vec: Vector) -> Vector
[ ] Vector.distance_to_plane(plane: Plane) -> float
[ ] Vector.dot(vec: Vector) -> float
[ ] Vector.get_angle(vec: Vector) -> float
[ ] Vector.get_signed_angle(vec: Vector, normal: Vector | None = None) -> float
[ ] Vector.intersect(*args, **kwargs)
[ ] Vector.length: unknown
[ ] Vector.multiply(scale: float) -> Vector
[ ] Vector.normalized() -> Vector
[ ] Vector.project_to_line(line: Vector) -> Vector
[ ] Vector.project_to_plane(plane: Plane) -> Vector
[ ] Vector.reverse() -> Vector
[ ] Vector.rotate(axis: Axis, angle: float) -> Vector
[ ] Vector.signed_distance_from_plane(plane: Plane) -> float
[ ] Vector.sub(vec: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Vector
[ ] Vector.to_dir() -> gp_Dir
[ ] Vector.to_pnt() -> gp_Pnt
[ ] Vector.to_tuple() -> tuple[float, float, float]
[ ] Vector.transform(affine_transform: Matrix, is_direction: bool = False) -> Vector
[ ] Vector.wrapped: unknown
[ ] Compound(obj: TopoDS_Compound | Iterable[Shape] | None = None, label: str = '', color: Color | None = None, material: str = '', joints: dict[str, Joint] | None = None, parent: Compound | None = None, children: Sequence[Shape] | None = None)
[ ] Compound.cast(obj: TopoDS_Shape) -> Vertex | Edge | Wire | Face | Shell | Solid | Compound
[ ] Compound.center(center_of: ~build123d.build_enums.CenterOf = <CenterOf.MASS>) -> Vector
[ ] Compound.compound() -> Compound | None
[ ] Compound.compounds() -> ShapeList[Compound]
[ ] Compound.do_children_intersect(include_parent: bool = False, tolerance: float = 1e-05) -> tuple[bool, tuple[Shape | None, Shape | None], float]
[ ] Compound.extrude(obj: Shell, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Compound
[ ] Compound.get_type(obj_type: type[Vertex] | type[Edge] | type[Face] | type[Shell] | type[Solid] | type[Wire]) -> list[Vertex | Edge | Face | Shell | Solid | Wire]
[ ] Compound.make_text(txt: str, font_size: float, font: str = 'Arial', font_path: ~os.PathLike[str] | str | None = None, font_style: ~build123d.build_enums.FontStyle = <FontStyle.REGULAR>, text_align: tuple[~build123d.build_enums.TextAlign, ~build123d.build_enums.TextAlign] = (<TextAlign.CENTER>, <TextAlign.CENTER>), align: ~build123d.build_enums.Align | tuple[~build123d.build_enums.Align, ~build123d.build_enums.Align] | None = None, position_on_path: float = 0.0, text_path: ~topology.one_d.Edge | ~topology.one_d.Wire | None = None, single_line_width: float = 0.0) -> Compound
[ ] Compound.make_triad(axes_scale: float) -> Compound
[ ] Compound.order()
[ ] Compound.project_to_viewport(viewport_origin: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], viewport_up: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 1), look_at: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None, focus: float | None = None) -> tuple[ShapeList[Edge], ShapeList[Edge]]
[ ] Compound.touch(other: Shape, tolerance: float = 1e-06) -> ShapeList[Vertex | Edge | Face]
[ ] Compound.unwrap(fully: bool = True) -> Self | Shape
[ ] Compound.volume: unknown
[ ] Edge(obj: TopoDS_Edge | Axis | None | None = None, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] Edge.arc_center: unknown
[ ] Edge.close() -> Edge | Wire
[ ] Edge.distribute_locations(count: int, start: float = 0.0, stop: float = 1.0, positions_only: bool = False) -> list[Location]
[ ] Edge.extrude(obj: Vertex, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Edge
[ ] Edge.find_intersection_points(other: Axis | Edge | None = None, tolerance: float = 1e-06) -> ShapeList[Vector]
[ ] Edge.find_tangent(angle: float) -> list[float]
[ ] Edge.geom_adaptor() -> BRepAdaptor_Curve
[ ] Edge.geom_equal(other: Edge, tol: float = 1e-06, num_interpolation_points: int = 5) -> bool
[ ] Edge.is_infinite: unknown
[ ] Edge.make_bezier(*cntl_pnts: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], weights: list[float] | None = None) -> Edge
[ ] Edge.make_circle(radius: float, plane: ~build123d.geometry.Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), start_angle: float = 360.0, end_angle: float = 360, angular_direction: ~build123d.build_enums.AngularDirection = <AngularDirection.COUNTER_CLOCKWISE>) -> Edge
[ ] Edge.make_constrained_arcs(tangency_one: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], tangency_two: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], *, radius: float, sagitta: Sagitta = Sagitta.SHORT) -> ShapeList[Edge]
[ ] null.make_constrained_arcs(tangency_one: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], tangency_two: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], *, center_on: Axis | Edge, sagitta: Sagitta = Sagitta.SHORT) -> ShapeList[Edge]
[ ] null.make_constrained_arcs(tangency_one: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], tangency_two: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], tangency_three: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], *, sagitta: Sagitta = Sagitta.SHORT) -> ShapeList[Edge]
[ ] null.make_constrained_arcs(tangency_one: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], *, center: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> ShapeList[Edge]
[ ] null.make_constrained_arcs(tangency_one: tuple[Axis | Edge, Tangency] | Axis | Edge | Vertex | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], *, radius: float, center_on: Edge) -> ShapeList[Edge]
[ ] Edge.make_constrained_lines(tangency_one: tuple[Edge, Tangency] | Axis | Edge, tangency_two: tuple[Edge, Tangency] | Axis | Edge) -> ShapeList[Edge]
[ ] null.make_constrained_lines(tangency_one: tuple[Edge, Tangency] | Edge, tangency_two: Vector) -> ShapeList[Edge]
[ ] null.make_constrained_lines(tangency_one: tuple[Edge, Tangency] | Edge, tangency_two: Axis, *, angle: float | None = None, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> ShapeList[Edge]
[ ] Edge.make_ellipse(x_radius: float, y_radius: float, plane: ~build123d.geometry.Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), start_angle: float = 360.0, end_angle: float = 360.0, angular_direction: ~build123d.build_enums.AngularDirection = <AngularDirection.COUNTER_CLOCKWISE>) -> Edge
[ ] Edge.make_helix(pitch: float, height: float, radius: float, center: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 0), normal: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 1), angle: float = 0.0, lefthand: bool = False) -> Wire
[ ] Edge.make_hyperbola(x_radius: float, y_radius: float, plane: ~build123d.geometry.Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), start_angle: float = 360.0, end_angle: float = 360.0, angular_direction: ~build123d.build_enums.AngularDirection = <AngularDirection.COUNTER_CLOCKWISE>) -> Edge
[ ] Edge.make_line(point1: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], point2: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Edge
[ ] Edge.make_mid_way(first: Edge, second: Edge, middle: float = 0.5) -> Edge
[ ] Edge.make_parabola(focal_length: float, plane: ~build123d.geometry.Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), start_angle: float = 0.0, end_angle: float = 90.0, angular_direction: ~build123d.build_enums.AngularDirection = <AngularDirection.COUNTER_CLOCKWISE>) -> Edge
[ ] Edge.make_spline(points: list[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]], tangents: list[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]] | None = None, periodic: bool = False, parameters: list[float] | None = None, scale: bool = True, tol: float = 1e-06) -> Edge
[ ] Edge.make_spline_approx(points: list[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]], tol: float = 0.001, smoothing: tuple[float, float, float] | None = None, min_deg: int = 1, max_deg: int = 6) -> Edge
[ ] Edge.make_tangent_arc(start: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], tangent: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], end: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Edge
[ ] Edge.make_three_point_arc(point1: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], point2: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], point3: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Edge
[ ] Edge.order()
[ ] Edge.param_at(position: float) -> float
[ ] Edge.param_at_point(point: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> float
[ ] Edge.project_to_shape(target_object: Shape, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None, center: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> ShapeList[Edge]
[ ] Edge.reversed(reconstruct: bool = False) -> Edge
[ ] Edge.to_axis() -> Axis
[ ] Edge.to_wire() -> Wire
[ ] Edge.trim(start: float | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], end: float | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Edge
[ ] Edge.trim_infinite(half_length: float) -> Edge
[ ] Edge.trim_to_length(start: float | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], length: float) -> Edge
[ ] Edge.trim_to_other(other: Shape | Axis | Location | Plane | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Edge | None
[ ] Face(obj: TopoDS_Face | Plane, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] null.Face(outer_wire: Wire, inner_wires: Iterable[Wire] | None = None, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] Face.area_without_holes: unknown
[ ] Face.axes_of_symmetry: unknown
[ ] Face.axis_of_rotation: unknown
[ ] Face.center(center_of: ~build123d.build_enums.CenterOf = <CenterOf.GEOMETRY>) -> Vector
[ ] Face.center_location: unknown
[ ] Face.chamfer_2d(distance: float, distance2: float, vertices: Iterable[Vertex], edge: Edge | None = None) -> Face
[ ] Face.extrude(obj: Edge, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Face
[ ] Face.fillet_2d(radius: float, vertices: Iterable[Vertex]) -> Face
[ ] Face.geom_adaptor() -> Geom_Surface
[ ] Face.geometry: unknown
[ ] Face.inner_wires() -> ShapeList[Wire]
[ ] Face.is_circular_concave: unknown
[ ] Face.is_circular_convex: unknown
[ ] Face.is_coplanar(plane: Plane) -> bool
[ ] Face.is_inside(point: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], tolerance: float = 1e-06) -> bool
[ ] Face.is_planar: unknown
[ ] Face.length: unknown
[ ] Face.location_at(surface_point: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None, *, x_dir: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> Location
[ ] null.location_at(u: float, v: float, *, x_dir: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> Location
[ ] Face.make_bezier_surface(points: list[list[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]]], weights: list[list[float]] | None = None) -> Face
[ ] Face.make_gordon_surface(profiles: Iterable[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | Edge], guides: Iterable[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | Edge], tolerance: float = 0.0003) -> Face
[ ] Face.make_holes(interior_wires: list[Wire]) -> Face
[ ] Face.make_plane(plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> Face
[ ] Face.make_rect(width: float, height: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> Face
[ ] Face.make_surface(exterior: Wire | Iterable[Edge], surface_points: Iterable[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]] | None = None, interior_wires: Iterable[Wire] | None = None) -> Face
[ ] Face.make_surface_from_array_of_points(points: list[list[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]]], tol: float = 0.01, smoothing: tuple[float, float, float] | None = None, min_deg: int = 1, max_deg: int = 3) -> Face
[ ] Face.make_surface_from_curves(edge1: Edge, edge2: Edge) -> Face
[ ] null.make_surface_from_curves(wire1: Wire, wire2: Wire) -> Face
[ ] Face.make_surface_patch(edge_face_constraints: Iterable[tuple[Edge, Face, ContinuityLevel]] | None = None, edge_constraints: Iterable[Edge] | None = None, point_constraints: Iterable[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]] | None = None) -> Face
[ ] Face.normal_at(surface_point: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> Vector
[ ] null.normal_at(u: float, v: float) -> Vector
[ ] Face.order()
[ ] Face.outer_wire() -> Wire
[ ] Face.position_at(u: float, v: float) -> Vector
[ ] Face.project_to_shape(target_object: Shape, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> ShapeList[Face | Shell]
[ ] Face.radii: unknown
[ ] Face.radius: unknown
[ ] Face.revolve(profile: Edge, angle: float, axis: Axis) -> Face
[ ] Face.semi_angle: unknown
[ ] Face.sew_faces(faces: Iterable[Face]) -> list[ShapeList[Face]]
[ ] Face.sweep(profile: Curve | Edge | Wire, path: Curve | Edge | Wire, transition=<Transition.TRANSFORMED>) -> Face
[ ] Face.to_arcs(tolerance: float = 0.001) -> Face
[ ] Face.volume: unknown
[ ] Face.width: unknown
[ ] Face.wire() -> Wire
[ ] Face.without_holes() -> Face
[ ] Face.wrap(planar_shape: Edge, surface_loc: Location, tolerance: float = 0.001, extension_factor: float = 0.1) -> Edge
[ ] null.wrap(planar_shape: Wire, surface_loc: Location, tolerance: float = 0.001, extension_factor: float = 0.1) -> Wire
[ ] null.wrap(planar_shape: Face, surface_loc: Location, tolerance: float = 0.001, extension_factor: float = 0.1) -> Face
[ ] Face.wrap_faces(faces: Iterable[Face], path: Wire | Edge, start: float = 0.0) -> ShapeList[Face]
[ ] Mixin1D(obj: TopoDS_Shape | None = None, label: str = '', color: ColorLike | None = None, parent: Compound | None = None)
[ ] Mixin1D.**matmul**(position: float) -> Vector
[ ] Mixin1D.**mod**(position: float) -> Vector
[ ] Mixin1D.cast(obj: TopoDS_Shape) -> Vertex | Edge | Wire
[ ] Mixin1D.center(center_of: ~build123d.build_enums.CenterOf = <CenterOf.GEOMETRY>) -> Vector
[ ] Mixin1D.common_plane(*lines: Edge | Wire | None, tolerance: float = 1e-06) -> None | Plane
[ ] Mixin1D.curvature_comb(count: int = 100, max_tooth_size: float | None = None) -> ShapeList[Edge]
[ ] Mixin1D.derivative_at(position: float | ~build123d.geometry.Vector | tuple[float, float] | tuple[float, float, float] | ~collections.abc.Sequence[float], order: int = 2, position_mode: ~build123d.build_enums.PositionMode = <PositionMode.PARAMETER>) -> Vector
[ ] Mixin1D.end_point() -> Vector
[ ] Mixin1D.extrude(obj: Shape, direction: VectorLike) -> Edge | Face | Shell | Solid | Compound
[ ] Mixin1D.is_closed: unknown
[ ] Mixin1D.is_forward: unknown
[ ] Mixin1D.is_interior: unknown
[ ] Mixin1D.length: unknown
[ ] Mixin1D.location_at(distance: float, position_mode: ~build123d.build_enums.PositionMode = <PositionMode.PARAMETER>, frame_method: ~build123d.build_enums.FrameMethod = <FrameMethod.FRENET>, x_dir: ~build123d.geometry.Vector | tuple[float, float] | tuple[float, float, float] | ~collections.abc.Sequence[float] | None = None) -> Location
[ ] Mixin1D.locations(distances: ~collections.abc.Iterable[float], position_mode: ~build123d.build_enums.PositionMode = <PositionMode.PARAMETER>, frame_method: ~build123d.build_enums.FrameMethod = <FrameMethod.FRENET>, x_dir: ~build123d.geometry.Vector | tuple[float, float] | tuple[float, float, float] | ~collections.abc.Sequence[float] | None = None) -> list[Location]
[ ] Mixin1D.normal() -> Vector
[ ] Mixin1D.offset_2d(distance: float, kind: ~build123d.build_enums.Kind = <Kind.ARC>, side: ~build123d.build_enums.Side = <Side.BOTH>, closed: bool = True) -> Edge | Wire
[ ] Mixin1D.perpendicular_line(length: float, u_value: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> Edge
[ ] Mixin1D.position_at(position: float, position_mode: ~build123d.build_enums.PositionMode = <PositionMode.PARAMETER>) -> Vector
[ ] Mixin1D.positions(distances: ~collections.abc.Iterable[float] | None = None, position_mode: ~build123d.build_enums.PositionMode = <PositionMode.PARAMETER>, deflection: float | None = None) -> list[Vector]
[ ] Mixin1D.project(face: Face, direction: VectorLike, closest: bool = True) -> Edge | Wire | ShapeList[Edge | Wire]
[ ] Mixin1D.project_to_viewport(viewport_origin: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], viewport_up: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 1), look_at: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None, focus: float | None = None) -> tuple[ShapeList[Edge], ShapeList[Edge]]
[ ] Mixin1D.radius: unknown
[ ] Mixin1D.start_point() -> Vector
[ ] Mixin1D.tangent_angle_at(location_param: float = 0.5, position_mode: ~build123d.build_enums.PositionMode = <PositionMode.PARAMETER>, plane: ~build123d.geometry.Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> float
[ ] Mixin1D.tangent_at(position: float | ~build123d.geometry.Vector | tuple[float, float] | tuple[float, float, float] | ~collections.abc.Sequence[float] = 0.5, position_mode: ~build123d.build_enums.PositionMode = <PositionMode.PARAMETER>) -> Vector
[ ] Mixin1D.volume: unknown
[ ] Mixin2D(obj: TopoDS_Shape | None = None, label: str = '', color: ColorLike | None = None, parent: Compound | None = None)
[ ] Mixin2D.cast(obj: TopoDS_Shape) -> Vertex | Edge | Wire | Face | Shell
[ ] Mixin2D.extrude(obj: Shape, direction: VectorLike) -> Edge | Face | Shell | Solid | Compound
[ ] Mixin2D.find_intersection_points(other: Axis, tolerance: float = 1e-06) -> list[tuple[Vector, Vector]]
[ ] Mixin2D.location_at(*args: Any, **kwargs: Any) -> Location
[ ] Mixin2D.offset(amount: float) -> Self
[ ] Mixin2D.project_to_viewport(viewport_origin: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], viewport_up: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 1), look_at: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None, focus: float | None = None) -> tuple[ShapeList[Edge], ShapeList[Edge]]
[ ] Mixin2D.touch(other: Shape, tolerance: float = 1e-06, found_faces: ShapeList | None = None, found_edges: ShapeList | None = None) -> ShapeList
[ ] Mixin3D(obj: TopoDS_Shape | None = None, label: str = '', color: ColorLike | None = None, parent: Compound | None = None)
[ ] Mixin3D.cast(obj: TopoDS_Shape) -> Self
[ ] Mixin3D.center(center_of: ~build123d.build_enums.CenterOf = <CenterOf.MASS>) -> Vector
[ ] Mixin3D.chamfer(length: float, length2: float | None, edge_list: Iterable[Edge], face: Face | None = None) -> Solid | Part
[ ] Mixin3D.dprism(basis: Face | None, bounds: list[Face | Wire], depth: float | None = None, taper: float = 0, up_to_face: Face | None = None, thru_all: bool = True, additive: bool = True) -> Solid
[ ] Mixin3D.extrude(obj: Shape, direction: VectorLike) -> Edge | Face | Shell | Solid | Compound
[ ] Mixin3D.fillet(radius: float, edge_list: Iterable[Edge]) -> Solid | Part
[ ] Mixin3D.find_intersection_points(other: Axis, tolerance: float = 1e-06) -> list[tuple[Vector, Vector]]
[ ] Mixin3D.hollow(faces: ~collections.abc.Iterable[~topology.two_d.Face] | None, thickness: float, tolerance: float = 0.0001, kind: ~build123d.build_enums.Kind = <Kind.ARC>) -> Solid
[ ] Mixin3D.is_inside(point: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], tolerance: float = 1e-06) -> bool
[ ] Mixin3D.max_fillet(edge_list: Iterable[Edge], tolerance=0.1, max_iterations: int = 10) -> float
[ ] Mixin3D.offset_3d(openings: ~collections.abc.Iterable[~topology.two_d.Face] | None, thickness: float, tolerance: float = 0.0001, kind: ~build123d.build_enums.Kind = <Kind.ARC>) -> Solid
[ ] Mixin3D.project_to_viewport(viewport_origin: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], viewport_up: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 1), look_at: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None, focus: float | None = None) -> tuple[ShapeList[Edge], ShapeList[Edge]]
[ ] Shape(obj: TopoDS_Shape | None = None, label: str = '', color: ColorLike | None = None, parent: Compound | None = None)
[ ] Shape.**add**(other: None | Shape | Iterable[Shape]) -> Self | Compound
[ ] Shape.**and**(other: Shape | Iterable[Shape]) -> None | Self | Compound
[ ] Shape.**copy**() -> Self
[ ] Shape.**deepcopy**(memo) -> Self
[ ] Shape.**eq**(other) -> bool
[ ] Shape.**hash**() -> int
[ ] Shape.**rmul**(other: Plane | Location) -> Self
[ ] null.**rmul**(other: Iterable[Plane | Location]) -> list[Self]
[ ] Shape.**sub**(other: None | Shape | Iterable[Shape]) -> Self | Compound
[ ] Shape.area: unknown
[ ] Shape.bounding_box(tolerance: float | None = None, optimal: bool = True) -> BoundBox
[ ] Shape.cast(obj: TopoDS_Shape) -> Self
[ ] Shape.clean() -> Self
[ ] Shape.closest_points(other: Shape | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> tuple[Vector, Vector]
[ ] Shape.color: unknown
[ ] Shape.combined_center(objects: ~collections.abc.Iterable[~topology.shape_core.Shape], center_of: ~build123d.build_enums.CenterOf = <CenterOf.MASS>) -> Vector
[ ] Shape.composite_factories()
[ ] Shape.compound() -> Compound | None
[ ] Shape.compounds() -> ShapeList[Compound]
[ ] Shape.compute_mass(obj: Shape) -> float
[ ] Shape.copy_attributes_to(target: Shape, exceptions: Iterable[str] | None = None)
[ ] Shape.cut(*to_cut: Shape) -> Self | Compound
[ ] Shape.distance(other: Shape) -> float
[ ] Shape.distance_to(other: Shape | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> float
[ ] Shape.distance_to_with_closest_points(other: Shape | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> tuple[float, Vector, Vector]
[ ] Shape.distances(*others: Shape) -> Iterator[float]
[ ] Shape.downcast_LUT()
[ ] Shape.edge() -> Edge | None
[ ] Shape.edges() -> ShapeList[Edge]
[ ] Shape.entities(topo_type: Literal['Vertex', 'Edge', 'Wire', 'Face', 'Shell', 'Solid', 'Compound']) -> list[TopoDS_Shape]
[ ] Shape.extrude(obj: Shape, direction: VectorLike) -> Edge | Face | Shell | Solid | Compound
[ ] Shape.face() -> Face | None
[ ] Shape.faces() -> ShapeList[Face]
[ ] Shape.faces_intersected_by_axis(axis: Axis, tol: float = 0.0001) -> ShapeList[Face]
[ ] Shape.fix() -> Self
[ ] Shape.fuse(*to_fuse: Shape, glue: bool = False, tol: float | None = None) -> Self | Compound
[ ] Shape.geom_LUT_EDGE()
[ ] Shape.geom_LUT_FACE()
[ ] Shape.geom_type: unknown
[ ] Shape.get_shape_list(shape: Shape, entity_type: Literal['Vertex', 'Edge', 'Wire', 'Face', 'Shell', 'Solid', 'Compound']) -> ShapeList
[ ] Shape.get_single_shape(shape: Shape, entity_type: Literal['Vertex', 'Edge', 'Wire', 'Face', 'Shell', 'Solid', 'Compound']) -> Shape | None
[ ] Shape.get_top_level_shapes() -> ShapeList[Shape]
[ ] Shape.global_location: unknown
[ ] Shape.intersect(*to_intersect: Shape | Vector | Location | Axis | Plane, tolerance: float = 1e-06, include_touched: bool = False) -> ShapeList | None
[ ] Shape.inverse_shape_LUT()
[ ] Shape.is_equal(other: Shape) -> bool
[ ] Shape.is_manifold: unknown
[ ] Shape.is_null: unknown
[ ] Shape.is_planar_face: unknown
[ ] Shape.is_same(other: Shape) -> bool
[ ] Shape.is_valid: unknown
[ ] Shape.locate(loc: Location) -> Self
[ ] Shape.located(loc: Location) -> Self
[ ] Shape.location: unknown
[ ] Shape.make_composite(shapes: Iterable[Shape], dimension: int | None = None) -> Shape
[ ] Shape.matrix_of_inertia: unknown
[ ] Shape.mesh(tolerance: float, angular_tolerance: float = 0.1)
[ ] Shape.mirror(mirror_plane: Plane | None = None) -> Self
[ ] Shape.move(loc: Location) -> Self
[ ] Shape.moved(loc: Location | Plane) -> Self
[ ] Shape.orientation: unknown
[ ] Shape.oriented_bounding_box() -> OrientedBoundBox
[ ] Shape.position: unknown
[ ] Shape.principal_properties: unknown
[ ] Shape.project_faces(faces: list[Face] | Compound, path: Wire | Edge, start: float = 0) -> ShapeList[Face]
[ ] Shape.radius_of_gyration(axis: Axis) -> float
[ ] Shape.register_composite_factory(dimension: int | None, factory: Callable[[Iterable[Shape]], Shape]) -> None
[ ] Shape.relocate(loc: Location)
[ ] Shape.rotate(axis: Axis, angle: float, transform: bool = False) -> Self
[ ] Shape.scale(factor: float) -> Self
[ ] Shape.shape_LUT()
[ ] Shape.shape_properties_LUT()
[ ] Shape.shape_type: unknown
[ ] Shape.shell() -> Shell | None
[ ] Shape.shells() -> ShapeList[Shell]
[ ] Shape.show_topology(limit_class: Literal['Compound', 'Edge', 'Face', 'Shell', 'Solid', 'Vertex', 'Wire'] = 'Vertex', show_center: bool | None = None) -> str
[ ] Shape.solid() -> Solid | None
[ ] Shape.solids() -> ShapeList[Solid]
[ ] Shape.split(tool: TrimmingTool, keep: Literal[Keep.TOP, Keep.BOTTOM]) -> Self | list[Self] | None
[ ] null.split(tool: TrimmingTool, keep: Literal[Keep.ALL]) -> list[Self]
[ ] null.split(tool: TrimmingTool, keep: Literal[Keep.BOTH]) -> tuple[Self | list[Self] | None, Self | list[Self] | None]
[ ] null.split(tool: TrimmingTool, keep: Literal[Keep.INSIDE, Keep.OUTSIDE]) -> None
[ ] null.split(tool: TrimmingTool) -> Self | list[Self] | None
[ ] Shape.split_by_perimeter(perimeter: Edge | Wire, keep: Literal[Keep.INSIDE, Keep.OUTSIDE]) -> Face | Shell | ShapeList[Face] | None
[ ] null.split_by_perimeter(perimeter: Edge | Wire, keep: Literal[Keep.BOTH]) -> tuple[Face | Shell | ShapeList[Face] | None, Face | Shell | ShapeList[Face] | None]
[ ] null.split_by_perimeter(perimeter: Edge | Wire) -> Face | Shell | ShapeList[Face] | None
[ ] Shape.static_moments: unknown
[ ] Shape.tessellate(tolerance: float, angular_tolerance: float = 0.1) -> tuple[list[Vector], list[tuple[int, int, int]]]
[ ] Shape.to_splines(degree: int = 3, tolerance: float = 0.001, nurbs: bool = False) -> Self
[ ] Shape.touch(other: Shape, tolerance: float = 1e-06) -> ShapeList
[ ] Shape.transform_geometry(t_matrix: Matrix) -> Self
[ ] Shape.transform_shape(t_matrix: Matrix) -> Self
[ ] Shape.transformed(rotate: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 0), offset: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] = (0, 0, 0)) -> Self
[ ] Shape.translate(vector: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], transform: bool = False) -> Self
[ ] Shape.vertex() -> Vertex | None
[ ] Shape.vertices() -> ShapeList[Vertex]
[ ] Shape.wire() -> Wire | None
[ ] Shape.wires() -> ShapeList[Wire]
[ ] Shape.wrapped: unknown
[ ] ShapeList(iterable=(), /)
[ ] ShapeList.**and**(other: ShapeList) -> ShapeList[T]
[ ] ShapeList.**getitem**(key: SupportsIndex) -> T
[ ] null.**getitem**(key: slice) -> ShapeList[T]
[ ] ShapeList.**gt**(sort_by: Axis | SortBy = Axis((0, 0, 0), (0, 0, 1))) -> ShapeList[T]
[ ] ShapeList.**lshift**(group_by: Axis | SortBy = Axis((0, 0, 0), (0, 0, 1))) -> ShapeList[T]
[ ] ShapeList.**lt**(sort_by: Axis | SortBy = Axis((0, 0, 0), (0, 0, 1))) -> ShapeList[T]
[ ] ShapeList.**or**(filter_by: Axis | GeomType = Axis((0, 0, 0), (0, 0, 1))) -> ShapeList[T]
[ ] ShapeList.**rshift**(group_by: Axis | SortBy = Axis((0, 0, 0), (0, 0, 1))) -> ShapeList[T]
[ ] ShapeList.**sub**(other: ShapeList) -> ShapeList[T]
[ ] ShapeList.center() -> Vector
[ ] ShapeList.compound() -> Compound
[ ] ShapeList.compounds() -> ShapeList[Compound]
[ ] ShapeList.edge() -> Edge
[ ] ShapeList.edges() -> ShapeList[Edge]
[ ] ShapeList.expand() -> ShapeList
[ ] ShapeList.face() -> Face
[ ] ShapeList.faces() -> ShapeList[Face]
[ ] ShapeList.filter_by(filter_by: ShapePredicate | Axis | Plane | GeomType | property, reverse: bool = False, tolerance: float = 1e-05) -> ShapeList[T]
[ ] ShapeList.filter_by_position(axis: Axis, minimum: float, maximum: float, inclusive: tuple[bool, bool] = (True, True)) -> ShapeList[T]
[ ] ShapeList.first: unknown
[ ] ShapeList.group_by(group_by: Callable[[Shape], K] | Axis | Edge | Wire | SortBy | property = Axis((0, 0, 0), (0, 0, 1)), reverse=False, tol_digits=6) -> GroupBy[T, K]
[ ] ShapeList.last: unknown
[ ] ShapeList.shell() -> Shell
[ ] ShapeList.shells() -> ShapeList[Shell]
[ ] ShapeList.solid() -> Solid
[ ] ShapeList.solids() -> ShapeList[Solid]
[ ] ShapeList.sort_by(sort_by: Axis | Callable[[T], K] | Edge | Wire | SortBy | property = Axis((0, 0, 0), (0, 0, 1)), reverse: bool = False) -> ShapeList[T]
[ ] ShapeList.sort_by_distance(other: Shape | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], reverse: bool = False) -> ShapeList[T]
[ ] ShapeList.vertex() -> Vertex
[ ] ShapeList.vertices() -> ShapeList[Vertex]
[ ] ShapeList.wire() -> Wire
[ ] ShapeList.wires() -> ShapeList[Wire]
[ ] Shell(obj: TopoDS_Shell | Face | Iterable[Face] | None = None, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] Shell.center() -> Vector
[ ] Shell.extrude(obj: Wire, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Shell
[ ] Shell.location_at(surface_point: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], *, x_dir: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> Location
[ ] Shell.make_loft(objs: Iterable[Vertex | Wire], ruled: bool = False) -> Shell
[ ] Shell.order()
[ ] Shell.revolve(profile: Curve | Wire, angle: float, axis: Axis) -> Face
[ ] Shell.sweep(profile: Curve | Edge | Wire, path: Curve | Edge | Wire, transition=<Transition.TRANSFORMED>) -> Shell
[ ] Shell.volume: unknown
[ ] Solid(obj: TopoDS_Solid | Shell | None = None, label: str = '', color: Color | None = None, material: str = '', joints: dict[str, Joint] | None = None, parent: Compound | None = None)
[ ] Solid.draft(faces: Iterable[Face], neutral_plane: Plane, angle: float) -> Solid
[ ] Solid.extrude(obj: Face, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Solid
[ ] Solid.extrude_linear_with_rotation(section: Face | Wire, center: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], normal: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], angle: float, inner_wires: list[Wire] | None = None) -> Solid
[ ] Solid.extrude_taper(profile: Face, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], taper: float, flip_inner: bool = True) -> Solid
[ ] Solid.extrude_until(profile: Face, target: Compound | Solid, direction: VectorLike, until: Until = <Until.NEXT>) -> Solid
[ ] Solid.from_bounding_box(bbox: BoundBox | OrientedBoundBox) -> Solid
[ ] Solid.make_box(length: float, width: float, height: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> Solid
[ ] Solid.make_cone(base_radius: float, top_radius: float, height: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), angle: float = 360) -> Solid
[ ] Solid.make_cylinder(radius: float, height: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), angle: float = 360) -> Solid
[ ] Solid.make_loft(objs: Iterable[Vertex | Wire], ruled: bool = False) -> Solid
[ ] Solid.make_sphere(radius: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), angle1: float = -90, angle2: float = 90, angle3: float = 360) -> Solid
[ ] Solid.make_torus(major_radius: float, minor_radius: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), start_angle: float = 0, end_angle: float = 360, major_angle: float = 360) -> Solid
[ ] Solid.make_wedge(delta_x: float, delta_y: float, delta_z: float, min_x: float, min_z: float, max_x: float, max_z: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> Solid
[ ] Solid.order()
[ ] Solid.revolve(section: Face | Wire, angle: float, axis: Axis, inner_wires: list[Wire] | None = None) -> Solid
[ ] Solid.sweep(section: ~topology.two_d.Face | ~topology.one_d.Wire, path: ~topology.one_d.Wire | ~topology.one_d.Edge, inner_wires: list[~topology.one_d.Wire] | None = None, make_solid: bool = True, is_frenet: bool = False, mode: ~build123d.geometry.Vector | ~topology.one_d.Wire | ~topology.one_d.Edge | None = None, transition: ~build123d.build_enums.Transition = <Transition.TRANSFORMED>) -> Solid
[ ] Solid.sweep_multi(profiles: Iterable[Wire | Face], path: Wire | Edge, make_solid: bool = True, is_frenet: bool = False, binormal: Vector | Wire | Edge | None = None) -> Solid
[ ] Solid.thicken(surface: Face | Shell, depth: float, normal_override: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> Solid
[ ] Solid.touch(other: Shape, tolerance: float = 1e-06, found_solids: ShapeList | None = None) -> ShapeList[Vertex | Edge | Face]
[ ] Solid.volume: unknown
[ ] Wire(obj: TopoDS_Wire, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] null.Wire(edge: Edge, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] null.Wire(wire: Wire, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] null.Wire(wire: Curve, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] null.Wire(edges: Iterable[Edge], sequenced: bool = False, label: str = '', color: Color | None = None, parent: Compound | None = None)
[ ] Wire.chamfer_2d(distance: float, distance2: float, vertices: Iterable[Vertex], edge: Edge | None = None) -> Wire
[ ] Wire.close() -> Wire
[ ] Wire.combine(wires: Iterable[Wire | Edge], tol: float = 1e-09) -> ShapeList[Wire]
[ ] Wire.edges() -> ShapeList[Edge]
[ ] Wire.extrude(obj: Shape, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Wire
[ ] Wire.fillet_2d(radius: float, vertices: Iterable[Vertex]) -> Wire
[ ] Wire.fix_degenerate_edges(precision: float) -> Wire
[ ] Wire.geom_adaptor() -> BRepAdaptor_CompCurve
[ ] Wire.geom_equal(other: Wire, tol: float = 1e-06, num_interpolation_points: int = 5) -> bool
[ ] Wire.make_circle(radius: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> Wire
[ ] Wire.make_convex_hull(edges: Iterable[Edge], tolerance: float = 0.001) -> Wire
[ ] Wire.make_ellipse(x_radius: float, y_radius: float, plane: ~build123d.geometry.Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1)), start_angle: float = 360.0, end_angle: float = 360.0, angular_direction: ~build123d.build_enums.AngularDirection = <AngularDirection.COUNTER_CLOCKWISE>, closed: bool = True) -> Wire
[ ] Wire.make_polygon(vertices: Iterable[Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]], close: bool = True) -> Wire
[ ] Wire.make_rect(width: float, height: float, plane: Plane = Plane((0, 0, 0), (1, 0, 0), (0, 0, 1))) -> Wire
[ ] Wire.order()
[ ] Wire.order_chamfer_edges(reference_edge: Edge | None, edges: tuple[Edge, Edge]) -> tuple[Edge, Edge]
[ ] Wire.order_edges() -> ShapeList[Edge]
[ ] Wire.param_at(position: float) -> float
[ ] Wire.param_at_point(point: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> float
[ ] Wire.project_to_shape(target_object: Shape, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None, center: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float] | None = None) -> ShapeList[Wire]
[ ] Wire.stitch(other: Wire) -> Wire
[ ] Wire.to_wire() -> Wire
[ ] Wire.trim(start: float | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float], end: float | Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Wire
[ ] Vertex()
[ ] null.Vertex(ocp_vx: TopoDS_Vertex)
[ ] null.Vertex(X: float, Y: float, Z: float)
[ ] null.Vertex(v: Iterable[float])
[ ] Vertex.**add**(other: Vertex | Vector | tuple[float, float, float]) -> Vertex
[ ] Vertex.**sub**(other: Vertex | Vector | tuple) -> Vertex
[ ] Vertex.cast(obj: TopoDS_Shape) -> Self
[ ] Vertex.center() -> Vector
[ ] Vertex.extrude(obj: Shape, direction: Vector | tuple[float, float] | tuple[float, float, float] | Sequence[float]) -> Vertex
[ ] Vertex.order()
[ ] Vertex.split(tool: TrimmingTool, keep: Keep = <Keep.TOP>)
[ ] Vertex.to_tuple() -> tuple[float, float, float]
[ ] Vertex.transform_shape(t_matrix: Matrix) -> Vertex
[ ] Vertex.vertex() -> Vertex
[ ] Vertex.vertices() -> ShapeList[Vertex]
[ ] Vertex.volume: unknown
[ ] Curve(obj: TopoDS_Compound | Iterable[Shape] | None = None, label: str = '', color: ColorLike | None = None, material: str = '', joints: dict[str, Joint] | None = None, parent: Compound | None = None, children: Sequence[Shape] | None = None)
[ ] Curve.**matmul**(position: float) -> Vector
[ ] Curve.**mod**(position: float) -> Vector
[ ] Curve.wires() -> ShapeList[Wire]
[ ] Part(obj: TopoDS_Compound | Iterable[Shape] | None = None, label: str = '', color: ColorLike | None = None, material: str = '', joints: dict[str, Joint] | None = None, parent: Compound | None = None, children: Sequence[Shape] | None = None)
[ ] Sketch(obj: TopoDS_Compound | Iterable[Shape] | None = None, label: str = '', color: ColorLike | None = None, material: str = '', joints: dict[str, Joint] | None = None, parent: Compound | None = None, children: Sequence[Shape] | None = None)
[ ] null.import_brep(file_name: PathLike | str | bytes) -> Shape
[ ] null.import_step(filename: PathLike | str | bytes) -> Compound
[ ] null.import_stl(file_name: ~os.PathLike | str | bytes, model_unit: ~build123d.build_enums.Unit = <Unit.MM>) -> Face
[ ] null.import_svg(svg_file: str | ~pathlib.Path | ~typing.TextIO, *, flip_y: bool = True, align: ~build123d.build_enums.Align | tuple[~build123d.build_enums.Align, ~build123d.build_enums.Align] | None = <Align.MIN>, ignore_visibility: bool = False, label_by: ~typing.Literal['id', 'class', 'inkscape:label'] | str = 'id', is_inkscape_label: bool | None = None) -> ShapeList[Wire | Face]
[ ] null.import_svg_as_buildline_code(file_name: PathLike | str | bytes, precision: int = 6) -> tuple[str, str]
[ ] Joint(label: str, parent: BuildPart | Solid | Compound)
[ ] Joint.connect_to(*args, **kwargs)
[ ] Joint.location: unknown
[ ] Joint.relative_to(*args, **kwargs) -> Location
[ ] Joint.symbol: unknown
