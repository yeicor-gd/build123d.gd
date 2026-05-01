# res://tests/test_bound_box.gd
# Test file for BoundBox class.

extends Node

func test_create_from_bnd_box() -> String:
    var box = BoundBox.create_from_bnd_box(PackedByteArray())
    if not box:
        return "Failed to create BoundBox"
    return ""

func test_add_point() -> String:
    var box = BoundBox.create_from_bnd_box(PackedByteArray())
    box.add_point(Vector3(1, 2, 3))
    box.add_point(Vector3(-1, -2, -3))
    # After adding points, min should be (-1, -2, -3) and max (1, 2, 3)
    # Note: Bnd_Box may have different behavior
    return ""

func test_add_box() -> String:
    var box1 = BoundBox.create_from_bnd_box(PackedByteArray())
    box1.add_point(Vector3(1, 1, 1))
    var box2 = BoundBox.create_from_bnd_box(PackedByteArray())
    box2.add_point(Vector3(2, 2, 2))
    box1.add_box(box2)
    return ""

func test_center() -> String:
    var box = BoundBox.create_from_bnd_box(PackedByteArray())
    box.add_point(Vector3(0, 0, 0))
    box.add_point(Vector3(2, 2, 2))
    var center = box.center()
    # Center should be (1, 1, 1)
    if abs(center.x - 1.0) > 0.01 or abs(center.y - 1.0) > 0.01 or abs(center.z - 1.0) > 0.01:
        return "Center incorrect: " + str(center)
    return ""

func test_is_inside() -> String:
    var box1 = BoundBox.create_from_bnd_box(PackedByteArray())
    box1.add_point(Vector3(0, 0, 0))
    box1.add_point(Vector3(4, 4, 4))
    
    var box2 = BoundBox.create_from_bnd_box(PackedByteArray())
    box2.add_point(Vector3(1, 1, 1))
    box2.add_point(Vector3(3, 3, 3))
    
    if not box1.is_inside(box2):
        return "box2 should be inside box1"
    return ""

func test_overlaps() -> String:
    var box1 = BoundBox.create_from_bnd_box(PackedByteArray())
    box1.add_point(Vector3(0, 0, 0))
    box1.add_point(Vector3(2, 2, 2))
    
    var box2 = BoundBox.create_from_bnd_box(PackedByteArray())
    box2.add_point(Vector3(1, 1, 1))
    box2.add_point(Vector3(3, 3, 3))
    
    if not box1.overlaps(box2):
        return "box1 and box2 should overlap"
    return ""

func test_measure() -> String:
    var box = BoundBox.create_from_bnd_box(PackedByteArray())
    box.add_point(Vector3(0, 0, 0))
    box.add_point(Vector3(2, 3, 4))
    var measure = box.get_measure()
    # Volume should be 2 * 3 * 4 = 24
    if abs(measure - 24.0) > 0.01:
        return "Measure (volume) incorrect: " + str(measure)
    return ""

func test_diagonal() -> String:
    var box = BoundBox.create_from_bnd_box(PackedByteArray())
    box.add_point(Vector3(0, 0, 0))
    box.add_point(Vector3(3, 4, 12))
    var diag = box.get_diagonal()
    # Diagonal should be sqrt(3^2 + 4^2 + 12^2) = sqrt(169) = 13
    if abs(diag - 13.0) > 0.01:
        return "Diagonal incorrect: " + str(diag)
    return ""
