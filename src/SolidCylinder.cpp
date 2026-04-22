#include "SolidCylinder.h"

#include "OCCTUtils.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <gp_Ax2.hxx>
#include <gp_Dir.hxx>

using namespace godot;

void SolidCylinder::_bind_methods() {
    ClassDB::bind_method(D_METHOD("build_cylinder", "radius", "height", "origin"), &SolidCylinder::build_cylinder, DEFVAL(Vector3()));
}

SolidCylinder::SolidCylinder() = default;

void SolidCylinder::build_cylinder(double p_radius, double p_height, const Vector3 &p_origin) {
    ERR_FAIL_COND_MSG(p_radius <= 0.0, "SolidCylinder.build_cylinder requires a radius greater than zero.");
    ERR_FAIL_COND_MSG(p_height <= 0.0, "SolidCylinder.build_cylinder requires a height greater than zero.");

    try {
        const gp_Ax2 axis(occt_utils::to_occt_point(p_origin), gp_Dir(0.0, 0.0, 1.0));
        BRepPrimAPI_MakeCylinder cylinder(axis, p_radius, p_height);
        cylinder.Build();
        ERR_FAIL_COND_MSG(!cylinder.IsDone(), "OpenCASCADE cylinder construction did not complete.");
        set_occt_shape(cylinder.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}
