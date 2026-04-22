class_name TestProfilePrimitives


static func _approx(a: float, b: float, epsilon := 0.001) -> bool:
	return absf(a - b) <= epsilon


static func _approx_vec(a: Vector3, b: Vector3, epsilon := 0.001) -> bool:
	return _approx(a.x, b.x, epsilon) and _approx(a.y, b.y, epsilon) and _approx(a.z, b.z, epsilon)


static func test_rectangle_wire_default_plane() -> String:
	var rectangle := RectangleWire.new()
	rectangle.build_rectangle(Vector2(2.0, 4.0))

	if not rectangle.is_closed():
		return "rectangle wire was not closed"
	if not _approx(rectangle.get_length(), 12.0, 0.01):
		return "unexpected rectangle perimeter: %s" % rectangle.get_length()
	if not _approx_vec(rectangle.get_bounding_box_size(), Vector3(2.0, 4.0, 0.0), 0.01):
		return "unexpected rectangle bounds size: %s" % str(rectangle.get_bounding_box_size())

	return ""


static func test_rectangle_wire_custom_plane() -> String:
	var plane := CadPlane.new()
	plane.set_plane(Vector3(10.0, 0.0, 0.0), Vector3.UP, Vector3.RIGHT)

	var rectangle := RectangleWire.new()
	rectangle.build_rectangle(Vector2(2.0, 6.0), plane, false)

	if not _approx_vec(rectangle.get_bounding_box_min(), Vector3(10.0, 0.0, -6.0), 0.01):
		return "unexpected custom-plane rectangle bounds min: %s" % str(rectangle.get_bounding_box_min())
	if not _approx_vec(rectangle.get_bounding_box_max(), Vector3(12.0, 0.0, 0.0), 0.01):
		return "unexpected custom-plane rectangle bounds max: %s" % str(rectangle.get_bounding_box_max())

	var polyline := rectangle.get_polyline(0.05)
	if polyline.size() < 4:
		return "rectangle polyline had too few points"

	return ""
