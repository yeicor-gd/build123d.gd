#include "Wire.h"

#include "Axis.h"
#include "Edge.h"
#include "Face.h"
#include "OCCTUtils.h"
#include "Solid.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepGProp.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
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

bool points_match(const Vector3 &p_a, const Vector3 &p_b, double p_tolerance = 1e-9) {
    return p_a.distance_squared_to(p_b) <= static_cast<real_t>(p_tolerance * p_tolerance);
}

} // namespace

void Wire::_bind_methods() {
    ClassDB::bind_method(D_METHOD("build_polygon", "points", "closed"), &Wire::build_polygon, DEFVAL(true));
    ClassDB::bind_method(D_METHOD("extruded", "direction", "only_plane"), &Wire::extruded, DEFVAL(true));
    ClassDB::bind_method(D_METHOD("revolved", "axis", "angle_radians", "only_plane"), &Wire::revolved, DEFVAL(6.28318530717958647692), DEFVAL(true));
    ClassDB::bind_method(D_METHOD("is_closed"), &Wire::is_closed);
    ClassDB::bind_method(D_METHOD("get_length"), &Wire::get_length);
    ClassDB::bind_method(D_METHOD("get_edges"), &Wire::get_edges);
    ClassDB::bind_method(D_METHOD("get_polyline", "deflection"), &Wire::get_polyline, DEFVAL(0.1));
}

Wire::Wire() = default;

Ref<Wire> Wire::from_occt(const TopoDS_Wire &p_wire) {
    Ref<Wire> result;
    result.instantiate();
    result->set_occt_shape(p_wire);
    return result;
}

void Wire::build_polygon(const PackedVector3Array &p_points, bool p_closed) {
    ERR_FAIL_COND_MSG(p_points.size() < (p_closed ? 3 : 2), "Wire.build_polygon requires at least 3 points for closed wires or 2 for open wires.");

    try {
        BRepBuilderAPI_MakePolygon builder;
        for (int64_t index = 0; index < p_points.size(); ++index) {
            builder.Add(occt_utils::to_occt_point(p_points[index]));
        }
        if (p_closed) {
            builder.Close();
        }
        builder.Build();
        ERR_FAIL_COND_MSG(!builder.IsDone(), "OpenCASCADE wire construction did not complete.");
        set_occt_shape(builder.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}

Ref<Solid> Wire::extruded(const Vector3 &p_direction, bool p_only_plane) const {
    ERR_FAIL_COND_V_MSG(is_null(), Ref<Solid>(), "Wire.extruded requires a non-null wire.");
    ERR_FAIL_COND_V_MSG(!is_closed(), Ref<Solid>(), "Wire.extruded requires a closed wire.");

    Ref<Face> profile;
    profile.instantiate();
    profile->build_from_wire(Wire::from_occt(TopoDS::Wire(get_occt_shape())), p_only_plane);
    return profile->extruded(p_direction);
}

Ref<Solid> Wire::revolved(const Ref<Axis> &p_axis, double p_angle_radians, bool p_only_plane) const {
    ERR_FAIL_COND_V_MSG(is_null(), Ref<Solid>(), "Wire.revolved requires a non-null wire.");
    ERR_FAIL_COND_V_MSG(!is_closed(), Ref<Solid>(), "Wire.revolved requires a closed wire.");

    Ref<Face> profile;
    profile.instantiate();
    profile->build_from_wire(Wire::from_occt(TopoDS::Wire(get_occt_shape())), p_only_plane);
    return profile->revolved(p_axis, p_angle_radians);
}

bool Wire::is_closed() const {
    ERR_FAIL_COND_V_MSG(is_null(), false, "Wire.is_closed requires a non-null shape.");

    try {
        return BRep_Tool::IsClosed(get_occt_shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(false, occt_utils::exception_to_string(failure));
    }
}

double Wire::get_length() const {
    ERR_FAIL_COND_V_MSG(is_null(), 0.0, "Wire.get_length requires a non-null shape.");

    try {
        GProp_GProps properties;
        BRepGProp::LinearProperties(get_occt_shape(), properties);
        return properties.Mass();
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(0.0, occt_utils::exception_to_string(failure));
    }
}

Array Wire::get_edges() const {
    ERR_FAIL_COND_V_MSG(is_null(), Array(), "Wire.get_edges requires a non-null shape.");

    try {
        Array edges;
        BRepTools_WireExplorer explorer(TopoDS::Wire(get_occt_shape()));
        for (; explorer.More(); explorer.Next()) {
            edges.push_back(Edge::from_occt(explorer.Current()));
        }
        return edges;
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Array(), occt_utils::exception_to_string(failure));
    }
}

PackedVector3Array Wire::get_polyline(double p_deflection) const {
    ERR_FAIL_COND_V_MSG(is_null(), PackedVector3Array(), "Wire.get_polyline requires a non-null shape.");
    ERR_FAIL_COND_V_MSG(p_deflection <= 0.0, PackedVector3Array(), "Wire.get_polyline requires a positive deflection.");

    try {
        PackedVector3Array polyline;
        BRepTools_WireExplorer explorer(TopoDS::Wire(get_occt_shape()));
        for (; explorer.More(); explorer.Next()) {
            const PackedVector3Array edge_polyline = sample_edge_polyline(explorer.Current(), p_deflection);
            for (int64_t index = 0; index < edge_polyline.size(); ++index) {
                const Vector3 point = edge_polyline[index];
                if (!polyline.is_empty() && index == 0 && points_match(polyline[polyline.size() - 1], point)) {
                    continue;
                }
                polyline.push_back(point);
            }
        }
        return polyline;
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(PackedVector3Array(), occt_utils::exception_to_string(failure));
    }
}
