#ifndef TOPO_SHAPE_H
#define TOPO_SHAPE_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
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
    godot::Ref<TopoShape> translated(const godot::Vector3 &p_offset) const;
    godot::Ref<TopoShape> rotated(const godot::Vector3 &p_axis_origin, const godot::Vector3 &p_axis_direction, double p_angle_radians) const;
    godot::Ref<TopoShape> scaled(const godot::Vector3 &p_center, double p_factor) const;

    double get_volume() const;
    double get_surface_area() const;
    godot::Vector3 get_center_of_mass() const;
    godot::Vector3 get_bounding_box_min() const;
    godot::Vector3 get_bounding_box_max() const;
    godot::Vector3 get_bounding_box_size() const;
    bool import_step_file(const godot::String &p_file_path);
    bool export_step_file(const godot::String &p_file_path) const;
    bool import_step_bytes(const godot::PackedByteArray &p_data);
    godot::PackedByteArray export_step_bytes() const;
    bool import_stl_file(const godot::String &p_file_path);
    bool export_stl_file(const godot::String &p_file_path, bool p_ascii = false) const;
    bool import_stl_bytes(const godot::PackedByteArray &p_data);
    godot::PackedByteArray export_stl_bytes(bool p_ascii = false) const;
    godot::Ref<godot::ArrayMesh> to_array_mesh(double p_linear_deflection = 0.1, double p_angular_deflection = 0.5) const;

    void set_occt_shape(const TopoDS_Shape &p_shape);
    const TopoDS_Shape &get_occt_shape() const;
};

#endif // TOPO_SHAPE_H
