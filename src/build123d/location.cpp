#include "location.h"

#include "occt_utils.h"

#include <gp_EulerSequence.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf.hxx>

using namespace godot;

namespace build123d {

void Location::_bind_methods() {
    ClassDB::bind_static_method("Location", D_METHOD("create", "position", "orientation"), &Location::create, DEFVAL(Vector3()));
    ClassDB::bind_method(D_METHOD("set_position", "position"), &Location::set_position);
    ClassDB::bind_method(D_METHOD("get_position"), &Location::get_position);
    ClassDB::bind_method(D_METHOD("set_orientation", "orientation"), &Location::set_orientation);
    ClassDB::bind_method(D_METHOD("get_orientation"), &Location::get_orientation);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "orientation"), "set_orientation", "get_orientation");
}

Ref<Location> Location::create(const Vector3 &p_position, const Vector3 &p_orientation) {
    Ref<Location> location;
    location.instantiate();
    location->set_position(p_position);
    location->set_orientation(p_orientation);
    return location;
}

void Location::set_position(const Vector3 &p_position) {
    gp_Trsf trsf = wrapped.Transformation();
    trsf.SetTranslationPart(to_gp_vec(p_position));
    wrapped = TopLoc_Location(trsf);
}

Vector3 Location::get_position() const {
    return to_vector3(wrapped.Transformation().TranslationPart());
}

void Location::set_orientation(const Vector3 &p_orientation) {
    gp_Trsf trsf = wrapped.Transformation();

    gp_Quaternion rotation;
    rotation.SetEulerAngles(
        gp_Intrinsic_XYZ,
        Math::deg_to_rad(static_cast<double>(p_orientation.x)),
        Math::deg_to_rad(static_cast<double>(p_orientation.y)),
        Math::deg_to_rad(static_cast<double>(p_orientation.z))
    );
    trsf.SetRotationPart(rotation);
    wrapped = TopLoc_Location(trsf);
}

Vector3 Location::get_orientation() const {
    Standard_Real alpha = 0.0;
    Standard_Real beta = 0.0;
    Standard_Real gamma = 0.0;

    gp_Quaternion rotation;
    rotation.SetMatrix(wrapped.Transformation().VectorialPart());
    rotation.GetEulerAngles(gp_Intrinsic_XYZ, alpha, beta, gamma);

    return Vector3(
        Math::rad_to_deg(static_cast<double>(alpha)),
        Math::rad_to_deg(static_cast<double>(beta)),
        Math::rad_to_deg(static_cast<double>(gamma))
    );
}

const TopLoc_Location &Location::get_wrapped() const {
    return wrapped;
}

void Location::set_wrapped(const TopLoc_Location &p_location) {
    wrapped = p_location;
}

} // namespace build123d
