class_name TestShapeListSelectors


static func _approx(a: float, b: float, epsilon := 0.001) -> bool:
	return absf(a - b) <= epsilon


static func test_shape_list_position_and_distance() -> String:
	var left := SolidBox.new()
	left.build_box(Vector3.ONE, Vector3.ZERO)

	var middle := SolidBox.new()
	middle.build_box(Vector3.ONE, Vector3(2.0, 0.0, 0.0))

	var right := SolidBox.new()
	right.build_box(Vector3.ONE, Vector3(6.0, 0.0, 0.0))

	var shapes := ShapeList.new()
	shapes.append(right)
	shapes.append(left)
	shapes.append(middle)

	var axis := Axis.new()
	axis.set_axis(Vector3.ZERO, Vector3.RIGHT)

	if shapes.size() != 3:
		return "unexpected shape list size: %s" % shapes.size()
	if shapes.is_empty():
		return "shape list unexpectedly empty"

	var filtered := shapes.filter_by_axis(axis, 1.0, 3.0)
	if filtered.size() != 1:
		return "expected one shape in filtered list but got %s" % filtered.size()
	if not _approx(filtered.get_item(0).get_center_of_mass().x, 2.5, 0.02):
		return "unexpected filtered shape center: %s" % filtered.get_item(0).get_center_of_mass().x

	var axis_sorted := shapes.sort_by_axis(axis)
	if axis_sorted.size() != 3:
		return "unexpected axis-sorted list size: %s" % axis_sorted.size()
	if not _approx(axis_sorted.get_item(0).get_center_of_mass().x, 0.5, 0.02):
		return "axis sort did not place the nearest shape first"

	var sorted := shapes.sort_by_distance(middle)
	if sorted.size() != 3:
		return "unexpected sorted list size: %s" % sorted.size()
	if not _approx(sorted.get_item(0).get_center_of_mass().x, 2.5, 0.02):
		return "distance sort did not place middle shape first"
	if not _approx(sorted.get_item(2).get_center_of_mass().x, 6.5, 0.02):
		return "distance sort did not place farthest shape last"

	var expanded := shapes.solids()
	if expanded.size() != 3:
		return "expected solids() to preserve all solids but got %s" % expanded.size()

	return ""
