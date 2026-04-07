extends Node

func _ready() -> void:
	var total_passed := 0
	var total_failed := 0
	var suite_results: Array[String] = []

	var dir := DirAccess.open("res://tests")
	if dir == null:
		push_error("Could not open res://tests/")
		get_tree().quit(1)
		return

	var files: Array[String] = []
	dir.list_dir_begin()
	var fname := dir.get_next()
	while fname != "":
		if not dir.current_is_dir() and fname.begins_with("test_") and fname.ends_with(".gd"):
			files.append(fname)
		fname = dir.get_next()
	dir.list_dir_end()
	files.sort()

	for file in files:
		var path := "res://tests/" + file
		var script := load(path)
		if script == null:
			push_error("Failed to load script: " + path)
			total_failed += 1
			suite_results.append("  SUITE LOAD ERROR: " + file)
			continue

		# Discover test_* static methods via the script's method list
		var methods: Array[String] = []
		for m in script.get_script_method_list():
			if m["name"].begins_with("test_"):
				methods.append(m["name"])
		methods.sort()

		if methods.is_empty():
			continue

		var suite_name := file.trim_suffix(".gd")
		print("\n--- %s ---" % suite_name)

		var suite_passed := 0
		var suite_failed := 0

		for method in methods:
			var result: String = script.call(method)
			if result == "":
				print("  ✓ %s" % method)
				suite_passed += 1
			else:
				print("  ✗ %s: %s" % [method, result])
				suite_failed += 1

		total_passed += suite_passed
		total_failed += suite_failed
		if suite_failed > 0:
			suite_results.append("  %s: %d passed, %d failed" % [suite_name, suite_passed, suite_failed])
		else:
			suite_results.append("  %s: %d passed" % [suite_name, suite_passed])

	print("\n==============================")
	print("Results:")
	for line in suite_results:
		print(line)
	if total_failed > 0:
		print("Total: %d passed, %d failed" % [total_passed, total_failed])
	else:
		print("Total: %d passed" % total_passed)

	if total_failed > 0:
		print("TESTS FAILED")
		get_tree().quit(1)
	else:
		print("TESTS PASSED")
		get_tree().quit(0)
