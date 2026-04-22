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

	return ""
