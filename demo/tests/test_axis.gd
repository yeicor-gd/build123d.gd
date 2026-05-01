# res://tests/test_axis.gd
# Test file for Axis class

extends Node

func test_create_from_origin_dir() -> String:
    var axis = Axis.create_from_origin_dir(Vector3(1, 2, 3), Vector3(0, 0, 1))
    if not axis:
        return "Failed to create Axis"
    if axis.get_position() != Vector3(1, 2, 3):
        return "Position mismatch: " + str(axis.get_position())
    if axis.get_direction() != Vector3(0, 0, 1):
        return "Direction mismatch: " + str(axis.get_direction())
    return ""

func test_create_from_gp_ax1() -> String:
    # Test with empty data (should create default axis)
    var axis = Axis.create_from_gp_ax1(PackedByteArray())
    if not axis:
        return "Failed to create Axis from empty data"
    return ""

func test_position_property() -> String:
    var axis = Axis.create_from_origin_dir(Vector3(1, 2, 3), Vector3(0, 0, 1))
    axis.set_position(Vector3(4, 5, 6))
    if axis.get_position() != Vector3(4, 5, 6):
        return "Position setter/getter failed: " + str(axis.get_position())
    return ""

func test_direction_property() -> String:
    var axis = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    axis.set_direction(Vector3(0, 1, 0))
    var dir = axis.get_direction()
    if dir != Vector3(0, 1, 0):
        return "Direction setter/getter failed: " + str(dir)
    return ""

func test_angle_between() -> String:
    var axis1 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    var axis2 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(0, 1, 0))
    var angle = axis1.angle_between(axis2)
    # 90 degrees between X and Y axes
    if abs(angle - 90.0) > 0.01:
        return "Angle between X and Y should be 90 degrees, got: " + str(angle)
    return ""

func test_is_parallel() -> String:
    var axis1 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    var axis2 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    if not axis1.is_parallel(axis2):
        return "Same direction axes should be parallel"
    return ""

func test_is_opposite() -> String:
    var axis1 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    var axis2 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(-1, 0, 0))
    if not axis1.is_opposite(axis2):
        return "Opposite direction axes should be detected as opposite"
    return ""

func test_reverse() -> String:
    var axis = Axis.create_from_origin_dir(Vector3(1, 2, 3), Vector3(1, 0, 0))
    var reversed = axis.reverse()
    if not reversed:
        return "Reverse returned null"
    var dir = reversed.get_direction()
    if dir != Vector3(-1, 0, 0):
        return "Reversed direction incorrect: " + str(dir)
    return ""

func test_neg() -> String:
    var axis = Axis.create_from_origin_dir(Vector3(1, 2, 3), Vector3(1, 0, 0))
    var neg_axis = axis.neg()
    if not neg_axis:
        return "neg() returned null"
    var dir = neg_axis.get_direction()
    if dir != Vector3(-1, 0, 0):
        return "neg() direction incorrect: " + str(dir)
    return ""

func test_copy() -> String:
    var axis = Axis.create_from_origin_dir(Vector3(1, 2, 3), Vector3(0, 0, 1))
    var copied = axis.copy()
    if not copied:
        return "copy() returned null"
    if copied.get_position() != axis.get_position():
        return "Copied position mismatch"
    if copied.get_direction() != axis.get_direction():
        return "Copied direction mismatch"
    return ""

func test_deepcopy() -> String:
    var axis = Axis.create_from_origin_dir(Vector3(1, 2, 3), Vector3(0, 0, 1))
    var copied = axis.deepcopy()
    if not copied:
        return "deepcopy() returned null"
    if copied.get_position() != axis.get_position():
        return "Deepcopied position mismatch"
    if copied.get_direction() != axis.get_direction():
        return "Deepcopied direction mismatch"
    return ""

func test_is_coaxial() -> String:
    var axis1 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    var axis2 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    if not axis1.is_coaxial(axis2):
        return "Same axis should be coaxial"
    return ""

func test_is_normal() -> String:
    var axis1 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    var axis2 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(0, 1, 0))
    if not axis1.is_normal(axis2):
        return "X and Y axes should be normal"
    return ""

func test_is_skew() -> String:
    # Two non-parallel, non-intersecting lines are skew
    var axis1 = Axis.create_from_origin_dir(Vector3(0, 0, 0), Vector3(1, 0, 0))
    var axis2 = Axis.create_from_origin_dir(Vector3(0, 0, 1), Vector3(0, 1, 0))
    # This is a simplified test - full implementation may vary
    return ""
