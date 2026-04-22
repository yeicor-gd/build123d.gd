#ifndef TOPO_SHAPE_H
#define TOPO_SHAPE_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <TopoDS_Shape.hxx>

class TopoShape : public godot::RefCounted {
    GDCLASS(TopoShape, godot::RefCounted)

protected:
    static void _bind_methods();

    TopoDS_Shape occt_shape;

public:
    TopoShape();

    static godot::Ref<TopoShape> from_occt(const TopoDS_Shape &p_shape);

    bool is_null() const;
    godot::Ref<TopoShape> copy() const;
    godot::Ref<TopoShape> fuse(const godot::Ref<TopoShape> &p_other) const;
    godot::Ref<TopoShape> cut(const godot::Ref<TopoShape> &p_other) const;
    godot::Ref<TopoShape> common(const godot::Ref<TopoShape> &p_other) const;

    double get_volume() const;
    double get_surface_area() const;
    godot::Vector3 get_center_of_mass() const;
    godot::Vector3 get_bounding_box_min() const;
    godot::Vector3 get_bounding_box_max() const;
    godot::Vector3 get_bounding_box_size() const;

    void set_occt_shape(const TopoDS_Shape &p_shape);
    const TopoDS_Shape &get_occt_shape() const;
};

#endif // TOPO_SHAPE_H
