#include "axis.h"

#include "occt_utils.h"

#include <BRep_Tool.hxx>
#include <Geom_Curve.hxx>
#include <Standard_Failure.hxx>
#include <TopLoc_Location.hxx>
#include <gp.hxx>

using namespace godot;

namespace build123d {

void Axis::_bind_methods() {
    ClassDB::bind_static_method("Axis", D_METHOD("create", "origin", "direction"), &Axis::create);
    ClassDB::bind_static_method("Axis", D_METHOD("from_edge", "edge"), &Axis::from_edge);
    ClassDB::bind_static_method("Axis", D_METHOD("from_location", "location"), &Axis::from_location);

    ClassDB::bind_method(D_METHOD("set_position", "position"), &Axis::set_position);
    ClassDB::bind_method(D_METHOD("get_position"), &Axis::get_position);
    ClassDB::bind_method(D_METHOD("set_direction", "direction"), &Axis::set_direction);
    ClassDB::bind_method(D_METHOD("get_direction"), &Axis::get_direction);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "direction"), "set_direction", "get_direction");
}

Ref<Axis> Axis::create_from_gp_ax1(const gp_Ax1 &p_axis) {
    Ref<Axis> axis;
    axis.instantiate();
    axis->wrapped = p_axis;
    return axis;
}

Ref<Axis> Axis::create(const Vector3 &p_origin, const Vector3 &p_direction) {
    if (p_direction.is_zero_approx()) {
        return Ref<Axis>();
    }

    try {
        return create_from_gp_ax1(gp_Ax1(to_gp_pnt(p_origin), to_gp_dir(p_direction)));
    } catch (const Standard_Failure &) {
        return Ref<Axis>();
    }
}

Ref<Axis> Axis::from_edge(const Ref<Edge> &p_edge) {
    if (p_edge.is_null() || !p_edge->is_valid()) {
        return Ref<Axis>();
    }

    Standard_Real first = 0.0;
    Standard_Real last = 0.0;
    TopLoc_Location location;
    const Handle(Geom_Curve) curve = BRep_Tool::Curve(p_edge->get_wrapped(), location, first, last);
    if (curve.IsNull()) {
        return Ref<Axis>();
    }

    gp_Pnt origin;
    gp_Vec tangent;
    curve->D1(first, origin, tangent);
    origin.Transform(location.Transformation());
    tangent.Transform(location.Transformation());

    if (tangent.SquareMagnitude() <= gp::Resolution()) {
        return Ref<Axis>();
    }

    return create_from_gp_ax1(gp_Ax1(origin, gp_Dir(tangent)));
}

Ref<Axis> Axis::from_location(const Ref<Location> &p_location) {
    if (p_location.is_null()) {
        return Ref<Axis>();
    }

    const gp_Ax1 base_axis(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(0.0, 0.0, 1.0));
    return create_from_gp_ax1(base_axis.Transformed(p_location->get_wrapped().Transformation()));
}

void Axis::set_position(const Vector3 &p_position) {
    wrapped.SetLocation(to_gp_pnt(p_position));
}

Vector3 Axis::get_position() const {
    return to_vector3(wrapped.Location());
}

void Axis::set_direction(const Vector3 &p_direction) {
    if (p_direction.is_zero_approx()) {
        ERR_FAIL_MSG("Axis direction must be non-zero.");
    }

    wrapped.SetDirection(to_gp_dir(p_direction));
}

Vector3 Axis::get_direction() const {
    return to_vector3(wrapped.Direction());
}

const gp_Ax1 &Axis::get_wrapped() const {
    return wrapped;
}

void Axis::set_wrapped(const gp_Ax1 &p_axis) {
    wrapped = p_axis;
}

} // namespace build123d
