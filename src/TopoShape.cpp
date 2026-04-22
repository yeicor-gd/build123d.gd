#include "TopoShape.h"

#include "OCCTUtils.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepGProp.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>

using namespace godot;

namespace {

template <typename TOperation>
Ref<TopoShape> do_boolean_operation(const TopoDS_Shape &p_left, const TopoDS_Shape &p_right) {
    TOperation operation(p_left, p_right);
    operation.Build();
    ERR_FAIL_COND_V_MSG(!operation.IsDone(), Ref<TopoShape>(), "OpenCASCADE boolean operation did not complete.");
    return TopoShape::from_occt(operation.Shape());
}

void ensure_shape_present(const TopoDS_Shape &p_shape, const char *p_context) {
    ERR_FAIL_COND_MSG(p_shape.IsNull(), p_context);
}

} // namespace

void TopoShape::_bind_methods() {
    ClassDB::bind_method(D_METHOD("is_null"), &TopoShape::is_null);
    ClassDB::bind_method(D_METHOD("copy"), &TopoShape::copy);
    ClassDB::bind_method(D_METHOD("fuse", "other"), &TopoShape::fuse);
    ClassDB::bind_method(D_METHOD("cut", "other"), &TopoShape::cut);
    ClassDB::bind_method(D_METHOD("common", "other"), &TopoShape::common);
    ClassDB::bind_method(D_METHOD("get_volume"), &TopoShape::get_volume);
    ClassDB::bind_method(D_METHOD("get_surface_area"), &TopoShape::get_surface_area);
    ClassDB::bind_method(D_METHOD("get_center_of_mass"), &TopoShape::get_center_of_mass);
    ClassDB::bind_method(D_METHOD("get_bounding_box_min"), &TopoShape::get_bounding_box_min);
    ClassDB::bind_method(D_METHOD("get_bounding_box_max"), &TopoShape::get_bounding_box_max);
    ClassDB::bind_method(D_METHOD("get_bounding_box_size"), &TopoShape::get_bounding_box_size);
}

TopoShape::TopoShape() = default;

Ref<TopoShape> TopoShape::from_occt(const TopoDS_Shape &p_shape) {
    Ref<TopoShape> result;
    result.instantiate();
    result->occt_shape = p_shape;
    return result;
}

bool TopoShape::is_null() const {
    return occt_shape.IsNull();
}

Ref<TopoShape> TopoShape::copy() const {
    ensure_shape_present(occt_shape, "TopoShape.copy requires a non-null shape.");

    try {
        BRepBuilderAPI_Copy copier(occt_shape, Standard_True, Standard_False);
        return from_occt(copier.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Ref<TopoShape>(), occt_utils::exception_to_string(failure));
    }
}

Ref<TopoShape> TopoShape::fuse(const Ref<TopoShape> &p_other) const {
    ERR_FAIL_COND_V_MSG(p_other.is_null() || p_other->is_null(), Ref<TopoShape>(), "TopoShape.fuse requires a non-null other shape.");
    ensure_shape_present(occt_shape, "TopoShape.fuse requires a non-null shape.");

    try {
        return do_boolean_operation<BRepAlgoAPI_Fuse>(occt_shape, p_other->occt_shape);
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Ref<TopoShape>(), occt_utils::exception_to_string(failure));
    }
}

Ref<TopoShape> TopoShape::cut(const Ref<TopoShape> &p_other) const {
    ERR_FAIL_COND_V_MSG(p_other.is_null() || p_other->is_null(), Ref<TopoShape>(), "TopoShape.cut requires a non-null other shape.");
    ensure_shape_present(occt_shape, "TopoShape.cut requires a non-null shape.");

    try {
        return do_boolean_operation<BRepAlgoAPI_Cut>(occt_shape, p_other->occt_shape);
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Ref<TopoShape>(), occt_utils::exception_to_string(failure));
    }
}

Ref<TopoShape> TopoShape::common(const Ref<TopoShape> &p_other) const {
    ERR_FAIL_COND_V_MSG(p_other.is_null() || p_other->is_null(), Ref<TopoShape>(), "TopoShape.common requires a non-null other shape.");
    ensure_shape_present(occt_shape, "TopoShape.common requires a non-null shape.");

    try {
        return do_boolean_operation<BRepAlgoAPI_Common>(occt_shape, p_other->occt_shape);
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Ref<TopoShape>(), occt_utils::exception_to_string(failure));
    }
}

double TopoShape::get_volume() const {
    ensure_shape_present(occt_shape, "TopoShape.get_volume requires a non-null shape.");

    try {
        GProp_GProps properties;
        BRepGProp::VolumeProperties(occt_shape, properties);
        return properties.Mass();
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(0.0, occt_utils::exception_to_string(failure));
    }
}

double TopoShape::get_surface_area() const {
    ensure_shape_present(occt_shape, "TopoShape.get_surface_area requires a non-null shape.");

    try {
        GProp_GProps properties;
        BRepGProp::SurfaceProperties(occt_shape, properties);
        return properties.Mass();
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(0.0, occt_utils::exception_to_string(failure));
    }
}

Vector3 TopoShape::get_center_of_mass() const {
    ensure_shape_present(occt_shape, "TopoShape.get_center_of_mass requires a non-null shape.");

    try {
        GProp_GProps properties;
        BRepGProp::VolumeProperties(occt_shape, properties);
        return occt_utils::to_godot_vector3(properties.CentreOfMass());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Vector3(), occt_utils::exception_to_string(failure));
    }
}

Vector3 TopoShape::get_bounding_box_min() const {
    ensure_shape_present(occt_shape, "TopoShape.get_bounding_box_min requires a non-null shape.");

    try {
        Bnd_Box bounds;
        BRepBndLib::Add(occt_shape, bounds, Standard_False);
        ERR_FAIL_COND_V_MSG(bounds.IsVoid(), Vector3(), "Could not compute a bounding box for the shape.");

        double xmin = 0.0;
        double ymin = 0.0;
        double zmin = 0.0;
        double xmax = 0.0;
        double ymax = 0.0;
        double zmax = 0.0;
        bounds.Get(xmin, ymin, zmin, xmax, ymax, zmax);
        return Vector3(static_cast<real_t>(xmin), static_cast<real_t>(ymin), static_cast<real_t>(zmin));
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Vector3(), occt_utils::exception_to_string(failure));
    }
}

Vector3 TopoShape::get_bounding_box_max() const {
    ensure_shape_present(occt_shape, "TopoShape.get_bounding_box_max requires a non-null shape.");

    try {
        Bnd_Box bounds;
        BRepBndLib::Add(occt_shape, bounds, Standard_False);
        ERR_FAIL_COND_V_MSG(bounds.IsVoid(), Vector3(), "Could not compute a bounding box for the shape.");

        double xmin = 0.0;
        double ymin = 0.0;
        double zmin = 0.0;
        double xmax = 0.0;
        double ymax = 0.0;
        double zmax = 0.0;
        bounds.Get(xmin, ymin, zmin, xmax, ymax, zmax);
        return Vector3(static_cast<real_t>(xmax), static_cast<real_t>(ymax), static_cast<real_t>(zmax));
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Vector3(), occt_utils::exception_to_string(failure));
    }
}

Vector3 TopoShape::get_bounding_box_size() const {
    return get_bounding_box_max() - get_bounding_box_min();
}

void TopoShape::set_occt_shape(const TopoDS_Shape &p_shape) {
    occt_shape = p_shape;
}

const TopoDS_Shape &TopoShape::get_occt_shape() const {
    return occt_shape;
}
