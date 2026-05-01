func _assert_vec3_close(actual: Vector3, expected: Vector3, label: String) -> String:
	if not actual.is_equal_approx(expected):
		return "%s expected %s, got %s" % [label, expected, actual]
	return ""


func test_axis_create_from_origin_direction() -> String:
	var axis := Axis.create(Vector3(1, 2, 3), Vector3(0, 0, 4))
	if axis == null:
		return "Axis.create returned null"

	var position_error := _assert_vec3_close(axis.position, Vector3(1, 2, 3), "position")
	if position_error != "":
		return position_error

	return _assert_vec3_close(axis.direction, Vector3(0, 0, 1), "direction")


func test_axis_create_from_edge() -> String:
	var edge := Edge.make_line(Vector3(1, 2, 3), Vector3(1, 2, 7))
	if edge == null or not edge.is_valid():
		return "Edge.make_line did not create a valid edge"

	var axis := Axis.from_edge(edge)
	if axis == null:
		return "Axis.from_edge returned null"

	var position_error := _assert_vec3_close(axis.position, Vector3(1, 2, 3), "position")
	if position_error != "":
		return position_error

	return _assert_vec3_close(axis.direction, Vector3(0, 0, 1), "direction")


func test_axis_create_from_location() -> String:
	var location := Location.create(Vector3(1, 2, 3), Vector3(-90, 0, 0))
	if location == null:
		return "Location.create returned null"

	var axis := Axis.from_location(location)
	if axis == null:
		return "Axis.from_location returned null"

	var position_error := _assert_vec3_close(axis.position, Vector3(1, 2, 3), "position")
	if position_error != "":
		return position_error

	return _assert_vec3_close(axis.direction, Vector3(0, 1, 0), "direction")


func test_axis_rejects_zero_direction() -> String:
	var axis := Axis.create(Vector3.ZERO, Vector3.ZERO)
	if axis != null:
		return "Axis.create should reject a zero direction"
	return ""


func test_axis_copy() -> String:
	var original := Axis.create(Vector3(1, 2, 3), Vector3(4, 0, 0))
	if original == null:
		return "Failed to create original axis"

	var copied := original.copy()
	if copied == null:
		return "Axis.copy returned null"

	if copied == original:
		return "Axis.copy should return a distinct instance"

	var position_error := _assert_vec3_close(copied.position, original.position, "position")
	if position_error != "":
		return position_error

	return _assert_vec3_close(copied.direction, original.direction, "direction")


func test_axis_deepcopy() -> String:
	var original := Axis.create(Vector3(5, 6, 7), Vector3(0, 3, 0))
	if original == null:
		return "Failed to create original axis"

	var copied := original.deepcopy({})
	if copied == null:
		return "Axis.deepcopy returned null"

	if copied == original:
		return "Axis.deepcopy should return a distinct instance"

	var position_error := _assert_vec3_close(copied.position, original.position, "position")
	if position_error != "":
		return position_error

	return _assert_vec3_close(copied.direction, original.direction, "direction")
