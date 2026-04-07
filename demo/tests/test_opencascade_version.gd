class_name TestOpenCascadeVersion


static func test_get_version_string() -> String:
	var occ := OpenCascadeVersion.new()
	var version_str := occ.get_version_string()
	occ.free()
	if not version_str is String or version_str == "":
		return "expected non-empty String, got: %s" % str(version_str)
	return ""


static func test_get_version_major() -> String:
	var occ := OpenCascadeVersion.new()
	var major := occ.get_version_major()
	occ.free()
	if not major is int or major < 0:
		return "expected non-negative int, got: %s" % str(major)
	return ""


static func test_get_version_minor() -> String:
	var occ := OpenCascadeVersion.new()
	var minor := occ.get_version_minor()
	occ.free()
	if not minor is int or minor < 0:
		return "expected non-negative int, got: %s" % str(minor)
	return ""


static func test_get_version_maintenance() -> String:
	var occ := OpenCascadeVersion.new()
	var maintenance := occ.get_version_maintenance()
	occ.free()
	if not maintenance is int or maintenance < 0:
		return "expected non-negative int, got: %s" % str(maintenance)
	return ""


static func test_version_string_contains_major() -> String:
	var occ := OpenCascadeVersion.new()
	var version_str := occ.get_version_string()
	var major := occ.get_version_major()
	occ.free()
	if not version_str.contains(str(major)):
		return "version string %s does not contain major %d" % [str(version_str), major]
	return ""


static func test_version_immutability() -> String:
	var occ := OpenCascadeVersion.new()
	var major_1 := occ.get_version_major()
	var minor_1 := occ.get_version_minor()
	var maintenance_1 := occ.get_version_maintenance()
	var string_1 := occ.get_version_string()
	var major_2 := occ.get_version_major()
	var minor_2 := occ.get_version_minor()
	var maintenance_2 := occ.get_version_maintenance()
	var string_2 := occ.get_version_string()
	occ.free()
	if major_1 != major_2:
		return "major changed between calls: %d -> %d" % [major_1, major_2]
	if minor_1 != minor_2:
		return "minor changed between calls: %d -> %d" % [minor_1, minor_2]
	if maintenance_1 != maintenance_2:
		return "maintenance changed between calls: %d -> %d" % [maintenance_1, maintenance_2]
	if string_1 != string_2:
		return "version string changed between calls: %s -> %s" % [str(string_1), str(string_2)]
	return ""
