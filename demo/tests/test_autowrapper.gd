class_name TestAutowrapper

static func run():
	var occ = OpenCascadeVersion.new()
	print("OpenCASCADE Version: ", occ.get_version_string())
	print("Major: ", occ.get_version_major())
	print("Minor: ", occ.get_version_minor())
	print("Maintenance: ", occ.get_version_maintenance())


	print("Autowrapper test completed.")
