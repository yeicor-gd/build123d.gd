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
