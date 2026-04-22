#include "SolidCone.h"

#include "OCCTUtils.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRepPrimAPI_MakeCone.hxx>
#include <gp_Ax2.hxx>
#include <gp_Dir.hxx>

using namespace godot;

void SolidCone::_bind_methods() {
    ClassDB::bind_method(D_METHOD("build_cone", "radius_bottom", "radius_top", "height", "origin"), &SolidCone::build_cone, DEFVAL(Vector3()));
}

SolidCone::SolidCone() = default;

void SolidCone::build_cone(double p_radius_bottom, double p_radius_top, double p_height, const Vector3 &p_origin) {
    ERR_FAIL_COND_MSG(p_radius_bottom < 0.0 || p_radius_top < 0.0, "SolidCone.build_cone requires non-negative radii.");
    ERR_FAIL_COND_MSG(p_radius_bottom == 0.0 && p_radius_top == 0.0, "SolidCone.build_cone requires at least one non-zero radius.");
    ERR_FAIL_COND_MSG(p_height <= 0.0, "SolidCone.build_cone requires a height greater than zero.");

    try {
        const gp_Ax2 axis(occt_utils::to_occt_point(p_origin), gp_Dir(0.0, 0.0, 1.0));
        BRepPrimAPI_MakeCone cone(axis, p_radius_bottom, p_radius_top, p_height);
        cone.Build();
        ERR_FAIL_COND_MSG(!cone.IsDone(), "OpenCASCADE cone construction did not complete.");
        set_occt_shape(cone.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}
