#ifndef BUILD123D_AXIS_H
#define BUILD123D_AXIS_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/ref.hpp>

#include <gp_Ax1.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <math.h>

using namespace godot;

class Axis : public RefCounted {
    GDCLASS(Axis, RefCounted);

private:
    gp_Ax1 *wrapped;

protected:
    static void _bind_methods();

public:
    Axis();
    ~Axis();

    // Static factory methods
    static Ref<Axis> create_from_origin_dir(const Vector3 &p_origin, const Vector3 &p_direction);
    static Ref<Axis> create_from_gp_ax1(const PackedByteArray &p_data);

    // Wrapped gp_Ax1 access
    void set_wrapped(gp_Ax1 *p_ax1);
    gp_Ax1 *get_wrapped() const;

    // Properties
    Vector3 get_position() const;
    void set_position(const Vector3 &p_pos);

    Vector3 get_direction() const;
    void set_direction(const Vector3 &p_dir);

    // Location property (read-only, returns a Location object)
    Variant get_location() const;

    // Methods
    double angle_between(const Ref<Axis> &p_other) const;
    bool is_coaxial(const Ref<Axis> &p_other, double angular_tolerance = 1e-5, double linear_tolerance = 1e-5) const;
    bool is_normal(const Ref<Axis> &p_other, double angular_tolerance = 1e-5) const;
    bool is_opposite(const Ref<Axis> &p_other, double angular_tolerance = 1e-5) const;
    bool is_parallel(const Ref<Axis> &p_other, double angular_tolerance = 1e-5) const;
    bool is_skew(const Ref<Axis> &p_other, double tolerance = 1e-5) const;

    Ref<Axis> reverse() const;
    Ref<Axis> neg() const;
    Ref<Axis> copy() const;
    Ref<Axis> deepcopy() const;

    Ref<Axis> located(const Variant &p_location);
    Variant to_plane() const;

    Variant intersect(const Variant &p_other) const;
};

#endif // BUILD123D_AXIS_H
