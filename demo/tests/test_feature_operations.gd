class_name TestFeatureOperations


static func _approx(a: float, b: float, epsilon := 0.001) -> bool:
	return absf(a - b) <= epsilon


static func _approx_vec(a: Vector3, b: Vector3, epsilon := 0.001) -> bool:
	return _approx(a.x, b.x, epsilon) and _approx(a.y, b.y, epsilon) and _approx(a.z, b.z, epsilon)


static func test_face_extrusion() -> String:
	var face := Face.new()
	face.build_polygon(PackedVector3Array([
		Vector3.ZERO,
		Vector3(2.0, 0.0, 0.0),
		Vector3(2.0, 3.0, 0.0),
		Vector3(0.0, 3.0, 0.0),
	]))

	var solid := face.extruded(Vector3(0.0, 0.0, 4.0))
	if solid == null or solid.is_null():
		return "face extrusion returned a null solid"
	if not solid.is_closed():
		return "face extrusion did not return a closed solid"
	if not _approx(solid.get_volume(), 24.0, 0.05):
		return "unexpected extruded face volume: %s" % solid.get_volume()
	if not _approx_vec(solid.get_bounding_box_size(), Vector3(2.0, 3.0, 4.0), 0.02):
		return "unexpected extruded face bounds size: %s" % str(solid.get_bounding_box_size())

	return ""


static func test_wire_extrusion() -> String:
	var wire := CircleWire.new()
	wire.build_circle(2.0)

	var solid := wire.extruded(Vector3(0.0, 0.0, 5.0))
	if solid == null or solid.is_null():
		return "wire extrusion returned a null solid"
	if not solid.is_closed():
		return "wire extrusion did not return a closed solid"
	if not _approx(solid.get_volume(), PI * 4.0 * 5.0, 0.1):
		return "unexpected extruded wire volume: %s" % solid.get_volume()
	if not _approx_vec(solid.get_bounding_box_size(), Vector3(4.0, 4.0, 5.0), 0.05):
		return "unexpected extruded wire bounds size: %s" % str(solid.get_bounding_box_size())

	return ""


static func test_face_revolution() -> String:
	var face := Face.new()
	face.build_polygon(PackedVector3Array([
		Vector3(1.0, 0.0, 0.0),
		Vector3(2.0, 0.0, 0.0),
		Vector3(2.0, 0.0, 3.0),
		Vector3(1.0, 0.0, 3.0),
	]))

	var axis := Axis.new()
	axis.set_axis(Vector3.ZERO, Vector3.FORWARD)

	var solid := face.revolved(axis)
	if solid == null or solid.is_null():
		return "face revolution returned a null solid"
	if not solid.is_closed():
		return "face revolution did not return a closed solid"
	if not _approx(solid.get_volume(), PI * 9.0, 0.1):
		return "unexpected revolved face volume: %s" % solid.get_volume()
	if not _approx_vec(solid.get_bounding_box_size(), Vector3(4.0, 4.0, 3.0), 0.05):
		return "unexpected revolved face bounds size: %s" % str(solid.get_bounding_box_size())

	return ""


static func test_wire_revolution() -> String:
	var plane := CadPlane.new()
	plane.set_plane(Vector3(3.0, 0.0, 0.0), Vector3.UP, Vector3.RIGHT)

	var wire := CircleWire.new()
	wire.build_circle(1.0, plane)

	var axis := Axis.new()
	axis.set_axis(Vector3.ZERO, Vector3.FORWARD)

	var solid := wire.revolved(axis)
	if solid == null or solid.is_null():
		return "wire revolution returned a null solid"
	if not solid.is_closed():
		return "wire revolution did not return a closed solid"
	if not _approx(solid.get_volume(), 2.0 * PI * PI * 3.0, 0.2):
		return "unexpected revolved wire volume: %s" % solid.get_volume()

	var bounds_size := solid.get_bounding_box_size()
	if not _approx(bounds_size.z, 2.0, 0.05):
		return "unexpected revolved wire z bounds size: %s" % bounds_size.z
	if not _approx(bounds_size.x, bounds_size.y, 0.05):
		return "revolved wire x/y bounds were not symmetric: %s" % str(bounds_size)
	if bounds_size.x < 8.0 or bounds_size.x > 8.8:
		return "unexpected revolved wire radial bounds size: %s" % bounds_size.x

	return ""
