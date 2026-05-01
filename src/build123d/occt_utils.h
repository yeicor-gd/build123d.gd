#ifndef BUILD123D_OCCT_UTILS_H
#define BUILD123D_OCCT_UTILS_H

#include <godot_cpp/variant/vector3.hpp>

#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_XYZ.hxx>

namespace build123d {

inline gp_Pnt to_gp_pnt(const godot::Vector3 &p_vector) {
    return gp_Pnt(p_vector.x, p_vector.y, p_vector.z);
}

inline gp_Vec to_gp_vec(const godot::Vector3 &p_vector) {
    return gp_Vec(p_vector.x, p_vector.y, p_vector.z);
}

inline gp_Dir to_gp_dir(const godot::Vector3 &p_vector) {
    return gp_Dir(p_vector.x, p_vector.y, p_vector.z);
}

inline godot::Vector3 to_vector3(const gp_Pnt &p_point) {
    return godot::Vector3(p_point.X(), p_point.Y(), p_point.Z());
}

inline godot::Vector3 to_vector3(const gp_Dir &p_direction) {
    return godot::Vector3(p_direction.X(), p_direction.Y(), p_direction.Z());
}

inline godot::Vector3 to_vector3(const gp_XYZ &p_xyz) {
    return godot::Vector3(p_xyz.X(), p_xyz.Y(), p_xyz.Z());
}

} // namespace build123d

#endif // BUILD123D_OCCT_UTILS_H
