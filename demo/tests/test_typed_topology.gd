class_name TestTypedTopology


static func _approx(a: float, b: float, epsilon := 0.001) -> bool:
	return absf(a - b) <= epsilon


static func _approx_vec(a: Vector3, b: Vector3, epsilon := 0.001) -> bool:
	return _approx(a.x, b.x, epsilon) and _approx(a.y, b.y, epsilon) and _approx(a.z, b.z, epsilon)


static func test_vertex_wrapper() -> String:
	var vertex := Vertex.new()
	vertex.build_vertex(Vector3(1.0, -2.0, 3.5))

	if not _approx_vec(vertex.get_position(), Vector3(1.0, -2.0, 3.5), 0.001):
		return "unexpected vertex position: %s" % str(vertex.get_position())

	return ""


static func test_edge_wrapper() -> String:
	var edge := Edge.new()
	edge.build_line(Vector3.ZERO, Vector3(0.0, 3.0, 4.0))

	if not _approx(edge.get_length(), 5.0, 0.001):
		return "unexpected edge length: %s" % edge.get_length()
	if not _approx_vec(edge.get_start_position(), Vector3.ZERO, 0.001):
		return "unexpected edge start: %s" % str(edge.get_start_position())
	if not _approx_vec(edge.get_end_position(), Vector3(0.0, 3.0, 4.0), 0.001):
		return "unexpected edge end: %s" % str(edge.get_end_position())

	var polyline := edge.get_polyline(0.05)
	if polyline.size() < 2:
		return "edge polyline had fewer than 2 points"

	return ""


static func test_wire_wrapper() -> String:
	var wire := Wire.new()
	wire.build_polygon(PackedVector3Array([
		Vector3.ZERO,
		Vector3.RIGHT,
		Vector3(1.0, 0.0, 1.0),
		Vector3(0.0, 0.0, 1.0),
	]), true)

	if not wire.is_closed():
		return "expected wire to be closed"
	if not _approx(wire.get_length(), 4.0, 0.01):
		return "unexpected wire length: %s" % wire.get_length()

	var edges := wire.get_edges()
	if edges.size() != 4:
		return "expected 4 wire edges but got %s" % edges.size()
	if not edges[0] is Edge:
		return "first wire edge was not an Edge instance"

	var polyline := wire.get_polyline(0.05)
	if polyline.size() < 4:
		return "wire polyline had too few points"
	if not _approx_vec(polyline[0], polyline[polyline.size() - 1], 0.001):
		return "closed wire polyline did not return to its start point"

	return ""


static func test_face_wrapper() -> String:
	var face := Face.new()
	face.build_polygon(PackedVector3Array([
		Vector3.ZERO,
		Vector3.RIGHT,
		Vector3(1.0, 1.0, 0.0),
		Vector3.UP,
	]), true)

	if not face.is_planar():
		return "expected face to be planar"
	if not _approx(face.get_surface_area(), 1.0, 0.01):
		return "unexpected face area: %s" % face.get_surface_area()

	var outer_wire := face.get_outer_wire()
	if outer_wire == null or outer_wire.is_null():
		return "face outer wire was null"
	if not outer_wire.is_closed():
		return "face outer wire was not closed"

	var normal := face.get_normal()
	if not _approx(absf(normal.z), 1.0, 0.01):
		return "unexpected face normal: %s" % str(normal)

	return ""


static func test_toposhape_typed_extraction() -> String:
	var box := SolidBox.new()
	box.build_box(Vector3(1.0, 2.0, 3.0))

	var vertices := box.get_vertices()
	if vertices.size() != 8:
		return "expected 8 typed vertices but got %s" % vertices.size()
	if not vertices[0] is Vertex:
		return "first typed vertex was not a Vertex instance"

	var edges := box.get_edges()
	if edges.size() != 12:
		return "expected 12 typed edges but got %s" % edges.size()
	if not edges[0] is Edge:
		return "first typed edge was not an Edge instance"

	var edge: Edge = edges[0]
	if edge.get_polyline(0.05).size() < 2:
		return "typed edge polyline had fewer than 2 points"

	var wires := box.get_wires()
	if wires.size() != 6:
		return "expected 6 typed wires but got %s" % wires.size()
	if not wires[0] is Wire:
		return "first typed wire was not a Wire instance"

	var wire: Wire = wires[0]
	if wire.get_edges().is_empty():
		return "typed wire did not expose any edges"

	var faces := box.get_faces()
	if faces.size() != 6:
		return "expected 6 typed faces but got %s" % faces.size()
	if not faces[0] is Face:
		return "first typed face was not a Face instance"

	var face: Face = faces[0]
	if face.get_outer_wire() == null:
		return "typed face did not expose an outer wire"

	return ""
