#include "axis.h"
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <gp_Ax1.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <math.h>

using namespace godot;

Axis::Axis() {
    wrapped = new gp_Ax1(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(0.0, 0.0, 1.0));
}

Axis::~Axis() {
    delete wrapped;
}

void Axis::_bind_methods() {
    // Static factory methods
    ClassDB::bind_static_method("Axis", D_METHOD("create_from_origin_dir", "origin", "direction"), &Axis::create_from_origin_dir);
    ClassDB::bind_static_method("Axis", D_METHOD("create_from_gp_ax1", "data"), &Axis::create_from_gp_ax1);

    // Properties
    ClassDB::bind_method(D_METHOD("get_position"), &Axis::get_position);
    ClassDB::bind_method(D_METHOD("set_position", "pos"), &Axis::set_position);
    ClassDB::bind_method(D_METHOD("get_direction"), &Axis::get_direction);
    ClassDB::bind_method(D_METHOD("set_direction", "dir"), &Axis::set_direction);
    ClassDB::bind_method(D_METHOD("get_location"), &Axis::get_location);

    // Methods
    ClassDB::bind_method(D_METHOD("angle_between", "other"), &Axis::angle_between);
    ClassDB::bind_method(D_METHOD("is_coaxial", "other", "angular_tolerance", "linear_tolerance"), &Axis::is_coaxial, DEFVAL(1e-5), DEFVAL(1e-5));
    ClassDB::bind_method(D_METHOD("is_normal", "other", "angular_tolerance"), &Axis::is_normal, DEFVAL(1e-5));
    ClassDB::bind_method(D_METHOD("is_opposite", "other", "angular_tolerance"), &Axis::is_opposite, DEFVAL(1e-5));
    ClassDB::bind_method(D_METHOD("is_parallel", "other", "angular_tolerance"), &Axis::is_parallel, DEFVAL(1e-5));
    ClassDB::bind_method(D_METHOD("is_skew", "other", "tolerance"), &Axis::is_skew, DEFVAL(1e-5));
    ClassDB::bind_method(D_METHOD("reverse"), &Axis::reverse);
    ClassDB::bind_method(D_METHOD("neg"), &Axis::neg);
    ClassDB::bind_method(D_METHOD("copy"), &Axis::copy);
    ClassDB::bind_method(D_METHOD("deepcopy"), &Axis::deepcopy);
    ClassDB::bind_method(D_METHOD("located", "location"), &Axis::located);
    ClassDB::bind_method(D_METHOD("to_plane"), &Axis::to_plane);
    ClassDB::bind_method(D_METHOD("intersect", "other"), &Axis::intersect);

    // Property registration
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "direction"), "set_direction", "get_direction");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "location"), "", "get_location");
}

Ref<Axis> Axis::create_from_origin_dir(const Vector3 &p_origin, const Vector3 &p_direction) {
    Ref<Axis> axis;
    axis.instantiate();
    axis->set_position(p_origin);
    axis->set_direction(p_direction);
    return axis;
}

Ref<Axis> Axis::create_from_gp_ax1(const PackedByteArray &p_data) {
    Ref<Axis> axis;
    axis.instantiate();
    if (p_data.size() >= sizeof(gp_Ax1)) {
        axis->wrapped = new gp_Ax1();
        memcpy(axis->wrapped, p_data.ptr(), sizeof(gp_Ax1));
    }
    return axis;
}

void Axis::set_wrapped(gp_Ax1 *p_ax1) {
    if (wrapped) delete wrapped;
    wrapped = p_ax1;
}

gp_Ax1 *Axis::get_wrapped() const {
    return wrapped;
}

Vector3 Axis::get_position() const {
    if (!wrapped) return Vector3();
    const gp_Pnt &pnt = wrapped->Location();
    return Vector3(pnt.X(), pnt.Y(), pnt.Z());
}

void Axis::set_position(const Vector3 &p_pos) {
    if (!wrapped) wrapped = new gp_Ax1();
    wrapped->SetLocation(gp_Pnt(p_pos.x, p_pos.y, p_pos.z));
}

Vector3 Axis::get_direction() const {
    if (!wrapped) return Vector3(0, 0, 1);
    const gp_Dir &dir = wrapped->Direction();
    return Vector3(dir.X(), dir.Y(), dir.Z());
}

void Axis::set_direction(const Vector3 &p_dir) {
    if (!wrapped) wrapped = new gp_Ax1();
    wrapped->SetDirection(gp_Dir(p_dir.x, p_dir.y, p_dir.z));
}

Variant Axis::get_location() const {
    // Create a Location object from this axis
    // This will be implemented when Location class is added
    return Variant();
}

double Axis::angle_between(const Ref<Axis> &p_other) const {
    if (p_other.is_null() || !wrapped || !p_other->get_wrapped()) {
        return 0.0;
    }
    const gp_Dir &dir1 = wrapped->Direction();
    const gp_Dir &dir2 = p_other->get_wrapped()->Direction();
    double angle_rad = dir1.Angle(dir2);
    return angle_rad * 180.0 / Math_PI;
}

bool Axis::is_coaxial(const Ref<Axis> &p_other, double angular_tolerance, double linear_tolerance) const {
    if (p_other.is_null() || !wrapped || !p_other->get_wrapped()) {
        return false;
    }
    return wrapped->IsCoaxial(*p_other->get_wrapped(), angular_tolerance, linear_tolerance);
}

bool Axis::is_normal(const Ref<Axis> &p_other, double angular_tolerance) const {
    if (p_other.is_null() || !wrapped || !p_other->get_wrapped()) {
        return false;
    }
    return wrapped->Direction().IsNormal(p_other->get_wrapped()->Direction(), angular_tolerance);
}

bool Axis::is_opposite(const Ref<Axis> &p_other, double angular_tolerance) const {
    if (p_other.is_null() || !wrapped || !p_other->get_wrapped()) {
        return false;
    }
    return wrapped->Direction().IsOpposite(p_other->get_wrapped()->Direction(), angular_tolerance);
}

bool Axis::is_parallel(const Ref<Axis> &p_other, double angular_tolerance) const {
    if (p_other.is_null() || !wrapped || !p_other->get_wrapped()) {
        return false;
    }
    return wrapped->Direction().IsParallel(p_other->get_wrapped()->Direction(), angular_tolerance);
}

bool Axis::is_skew(const Ref<Axis> &p_other, double tolerance) const {
    if (p_other.is_null() || !wrapped || !p_other->get_wrapped()) {
        return false;
    }
    // Check if axes are not parallel and not coplanar
    if (is_parallel(p_other, tolerance)) {
        return false;
    }
    // For skew lines, they should not intersect
    // This is a simplified check - full implementation would use line intersection
    return true;
}

Ref<Axis> Axis::reverse() const {
    Ref<Axis> axis;
    axis.instantiate();
    if (wrapped) {
        axis->wrapped = new gp_Ax1(*wrapped);
        axis->wrapped->SetDirection(axis->wrapped->Direction().Reversed());
    }
    return axis;
}

Ref<Axis> Axis::neg() const {
    return reverse();
}

Ref<Axis> Axis::copy() const {
    Ref<Axis> axis;
    axis.instantiate();
    if (wrapped) {
        axis->wrapped = new gp_Ax1(*wrapped);
    }
    return axis;
}

Ref<Axis> Axis::deepcopy() const {
    // For Axis, deepcopy is the same as copy since gp_Ax1 is a value type
    return copy();
}

Ref<Axis> Axis::located(const Variant &p_location) {
    // This will be implemented when Location class is added
    return copy();
}

Variant Axis::to_plane() const {
    // This will be implemented when Plane class is added
    return Variant();
}

Variant Axis::intersect(const Variant &p_other) const {
    // This will be implemented based on the type of p_other
    return Variant();
}
