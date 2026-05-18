#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>

class TopoShape;
class Axis;

class ShapeList : public godot::RefCounted {
    GDCLASS(ShapeList, godot::RefCounted)

protected:
    static void _bind_methods();

    godot::Array shapes;

public:
    ShapeList();

    void append(const godot::Ref<TopoShape> &p_shape);
    int64_t size() const;
    bool is_empty() const;
    godot::Ref<TopoShape> get_item(int64_t p_index) const;
    godot::Array to_array() const;

    godot::Ref<ShapeList> vertices() const;
    godot::Ref<ShapeList> edges() const;
    godot::Ref<ShapeList> wires() const;
    godot::Ref<ShapeList> faces() const;
    godot::Ref<ShapeList> shells() const;
    godot::Ref<ShapeList> compounds() const;
    godot::Ref<ShapeList> solids() const;

    godot::Ref<ShapeList> filter_by_position(const godot::Ref<Axis> &p_axis, double p_minimum, double p_maximum, bool p_min_inclusive = true, bool p_max_inclusive = true) const;
    godot::Ref<ShapeList> sort_by_distance(const godot::Ref<TopoShape> &p_other, bool p_reverse = false) const;
};

#endif // SHAPE_LIST_H
