#include "Edge.h"

#include "OCCTUtils.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepGProp.hxx>
#include <GCPnts_QuasiUniformDeflection.hxx>
#include <GProp_GProps.hxx>
#include <TopoDS.hxx>

using namespace godot;

namespace {

PackedVector3Array sample_edge_polyline(const TopoDS_Edge &p_edge, double p_deflection) {
    BRepAdaptor_Curve curve(p_edge);
    GCPnts_QuasiUniformDeflection sampler(curve, p_deflection, curve.FirstParameter(), curve.LastParameter());

    PackedVector3Array polyline;
    if (sampler.IsDone() && sampler.NbPoints() >= 2) {
        for (int index = 1; index <= sampler.NbPoints(); ++index) {
            polyline.push_back(occt_utils::to_godot_vector3(sampler.Value(index)));
        }
    } else {
        polyline.push_back(occt_utils::to_godot_vector3(curve.Value(curve.FirstParameter())));
        polyline.push_back(occt_utils::to_godot_vector3(curve.Value(curve.LastParameter())));
    }

    return polyline;
}

} // namespace

void Edge::_bind_methods() {
    ClassDB::bind_method(D_METHOD("build_line", "start", "end"), &Edge::build_line);
    ClassDB::bind_method(D_METHOD("get_start_position"), &Edge::get_start_position);
    ClassDB::bind_method(D_METHOD("get_end_position"), &Edge::get_end_position);
    ClassDB::bind_method(D_METHOD("get_length"), &Edge::get_length);
    ClassDB::bind_method(D_METHOD("get_polyline", "deflection"), &Edge::get_polyline, DEFVAL(0.1));
}

Edge::Edge() = default;

Ref<Edge> Edge::from_occt(const TopoDS_Edge &p_edge) {
    Ref<Edge> result;
    result.instantiate();
    result->set_occt_shape(p_edge);
    return result;
}

void Edge::build_line(const Vector3 &p_start, const Vector3 &p_end) {
    ERR_FAIL_COND_MSG(p_start == p_end, "Edge.build_line requires distinct start and end points.");

    try {
        BRepBuilderAPI_MakeEdge builder(occt_utils::to_occt_point(p_start), occt_utils::to_occt_point(p_end));
        builder.Build();
        ERR_FAIL_COND_MSG(!builder.IsDone(), "OpenCASCADE edge construction did not complete.");
        set_occt_shape(builder.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}

Vector3 Edge::get_start_position() const {
    ERR_FAIL_COND_V_MSG(is_null(), Vector3(), "Edge.get_start_position requires a non-null shape.");

    try {
        const PackedVector3Array polyline = sample_edge_polyline(TopoDS::Edge(get_occt_shape()), 0.1);
        ERR_FAIL_COND_V_MSG(polyline.is_empty(), Vector3(), "OpenCASCADE could not determine the edge start point.");
        return polyline[0];
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Vector3(), occt_utils::exception_to_string(failure));
    }
}

Vector3 Edge::get_end_position() const {
    ERR_FAIL_COND_V_MSG(is_null(), Vector3(), "Edge.get_end_position requires a non-null shape.");

    try {
        const PackedVector3Array polyline = sample_edge_polyline(TopoDS::Edge(get_occt_shape()), 0.1);
        ERR_FAIL_COND_V_MSG(polyline.is_empty(), Vector3(), "OpenCASCADE could not determine the edge end point.");
        return polyline[polyline.size() - 1];
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Vector3(), occt_utils::exception_to_string(failure));
    }
}

double Edge::get_length() const {
    ERR_FAIL_COND_V_MSG(is_null(), 0.0, "Edge.get_length requires a non-null shape.");

    try {
        GProp_GProps properties;
        BRepGProp::LinearProperties(get_occt_shape(), properties);
        return properties.Mass();
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(0.0, occt_utils::exception_to_string(failure));
    }
}

PackedVector3Array Edge::get_polyline(double p_deflection) const {
    ERR_FAIL_COND_V_MSG(is_null(), PackedVector3Array(), "Edge.get_polyline requires a non-null shape.");
    ERR_FAIL_COND_V_MSG(p_deflection <= 0.0, PackedVector3Array(), "Edge.get_polyline requires a positive deflection.");

    try {
        return sample_edge_polyline(TopoDS::Edge(get_occt_shape()), p_deflection);
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(PackedVector3Array(), occt_utils::exception_to_string(failure));
    }
}
