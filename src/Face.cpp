#include "Face.h"

#include "Axis.h"
#include "OCCTUtils.h"
#include "Solid.h"
#include "Wire.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRepAdaptor_Surface.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <GeomAbs_SurfaceType.hxx>
#include <GeomLProp_SLProps.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>

using namespace godot;

namespace {

void build_face_from_wires_impl(Face *p_face, const Ref<Wire> &p_outer_wire, const Array &p_inner_wires, bool p_only_plane) {
    ERR_FAIL_COND_MSG(p_outer_wire.is_null() || p_outer_wire->is_null(), "Face.build_from_wires requires a non-null outer wire.");

    try {
        BRepBuilderAPI_MakeFace builder(TopoDS::Wire(p_outer_wire->get_occt_shape()), p_only_plane ? Standard_True : Standard_False);
        for (int64_t index = 0; index < p_inner_wires.size(); ++index) {
            const Ref<Wire> inner_wire = p_inner_wires[index];
            ERR_FAIL_COND_MSG(inner_wire.is_null() || inner_wire->is_null(), "Face.build_from_wires requires every inner wire entry to be a non-null Wire.");
            TopoDS_Wire occt_inner_wire = TopoDS::Wire(inner_wire->get_occt_shape());
            occt_inner_wire.Reverse();
            builder.Add(occt_inner_wire);
        }
        builder.Build();
        ERR_FAIL_COND_MSG(!builder.IsDone(), "OpenCASCADE face construction did not complete.");
        p_face->set_occt_shape(builder.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}

} // namespace

void Face::_bind_methods() {
    ClassDB::bind_method(D_METHOD("build_from_wire", "wire", "only_plane"), &Face::build_from_wire, DEFVAL(false));
    ClassDB::bind_method(D_METHOD("build_from_wires", "outer_wire", "inner_wires", "only_plane"), &Face::build_from_wires, DEFVAL(Array()), DEFVAL(false));
    ClassDB::bind_method(D_METHOD("build_polygon", "points", "only_plane"), &Face::build_polygon, DEFVAL(true));
    ClassDB::bind_method(D_METHOD("extruded", "direction"), &Face::extruded);
    ClassDB::bind_method(D_METHOD("revolved", "axis", "angle_radians"), &Face::revolved, DEFVAL(6.28318530717958647692));
    ClassDB::bind_method(D_METHOD("is_planar"), &Face::is_planar);
    ClassDB::bind_method(D_METHOD("get_outer_wire"), &Face::get_outer_wire);
    ClassDB::bind_method(D_METHOD("get_inner_wires"), &Face::get_inner_wires);
    ClassDB::bind_method(D_METHOD("get_normal"), &Face::get_normal);
}

Face::Face() = default;

Ref<Face> Face::from_occt(const TopoDS_Face &p_face) {
    Ref<Face> result;
    result.instantiate();
    result->set_occt_shape(p_face);
    return result;
}

void Face::build_from_wire(const Ref<Wire> &p_wire, bool p_only_plane) {
    build_face_from_wires_impl(this, p_wire, Array(), p_only_plane);
}

void Face::build_from_wires(const Ref<Wire> &p_outer_wire, const Array &p_inner_wires, bool p_only_plane) {
    build_face_from_wires_impl(this, p_outer_wire, p_inner_wires, p_only_plane);
}

void Face::build_polygon(const PackedVector3Array &p_points, bool p_only_plane) {
    ERR_FAIL_COND_MSG(p_points.size() < 3, "Face.build_polygon requires at least 3 points.");

    try {
        BRepBuilderAPI_MakePolygon polygon_builder;
        for (int64_t index = 0; index < p_points.size(); ++index) {
            polygon_builder.Add(occt_utils::to_occt_point(p_points[index]));
        }
        polygon_builder.Close();
        polygon_builder.Build();
        ERR_FAIL_COND_MSG(!polygon_builder.IsDone(), "OpenCASCADE polygon wire construction did not complete.");

        BRepBuilderAPI_MakeFace face_builder(TopoDS::Wire(polygon_builder.Shape()), p_only_plane ? Standard_True : Standard_False);
        face_builder.Build();
        ERR_FAIL_COND_MSG(!face_builder.IsDone(), "OpenCASCADE polygon face construction did not complete.");
        set_occt_shape(face_builder.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}

Ref<Solid> Face::extruded(const Vector3 &p_direction) const {
    ERR_FAIL_COND_V_MSG(is_null(), Ref<Solid>(), "Face.extruded requires a non-null face.");
    ERR_FAIL_COND_V_MSG(p_direction.length() == 0.0, Ref<Solid>(), "Face.extruded requires a non-zero direction.");

    try {
        BRepPrimAPI_MakePrism builder(get_occt_shape(), occt_utils::to_occt_vec(p_direction), Standard_True, Standard_True);
        builder.Build();
        ERR_FAIL_COND_V_MSG(!builder.IsDone(), Ref<Solid>(), "OpenCASCADE prism extrusion did not complete.");

        const TopoDS_Shape result = builder.Shape();
        ERR_FAIL_COND_V_MSG(result.IsNull(), Ref<Solid>(), "OpenCASCADE prism extrusion returned a null shape.");
        ERR_FAIL_COND_V_MSG(result.ShapeType() != TopAbs_SOLID, Ref<Solid>(), "Face.extruded expected a solid result.");
        return Solid::from_occt(TopoDS::Solid(result));
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Ref<Solid>(), occt_utils::exception_to_string(failure));
    }
}

Ref<Solid> Face::revolved(const Ref<Axis> &p_axis, double p_angle_radians) const {
    ERR_FAIL_COND_V_MSG(is_null(), Ref<Solid>(), "Face.revolved requires a non-null face.");
    ERR_FAIL_COND_V_MSG(p_axis.is_null(), Ref<Solid>(), "Face.revolved requires a non-null axis.");
    ERR_FAIL_COND_V_MSG(p_angle_radians == 0.0, Ref<Solid>(), "Face.revolved requires a non-zero angle.");

    try {
        BRepPrimAPI_MakeRevol builder(get_occt_shape(), p_axis->get_occt_axis(), p_angle_radians, Standard_True);
        builder.Build();
        ERR_FAIL_COND_V_MSG(!builder.IsDone(), Ref<Solid>(), "OpenCASCADE revolve operation did not complete.");

        const TopoDS_Shape result = builder.Shape();
        ERR_FAIL_COND_V_MSG(result.IsNull(), Ref<Solid>(), "OpenCASCADE revolve operation returned a null shape.");
        ERR_FAIL_COND_V_MSG(result.ShapeType() != TopAbs_SOLID, Ref<Solid>(), "Face.revolved expected a solid result.");
        return Solid::from_occt(TopoDS::Solid(result));
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Ref<Solid>(), occt_utils::exception_to_string(failure));
    }
}

bool Face::is_planar() const {
    ERR_FAIL_COND_V_MSG(is_null(), false, "Face.is_planar requires a non-null shape.");

    try {
        return BRepAdaptor_Surface(TopoDS::Face(get_occt_shape())).GetType() == GeomAbs_Plane;
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(false, occt_utils::exception_to_string(failure));
    }
}

Ref<Wire> Face::get_outer_wire() const {
    ERR_FAIL_COND_V_MSG(is_null(), Ref<Wire>(), "Face.get_outer_wire requires a non-null shape.");

    try {
        const TopoDS_Wire outer_wire = BRepTools::OuterWire(TopoDS::Face(get_occt_shape()));
        ERR_FAIL_COND_V_MSG(outer_wire.IsNull(), Ref<Wire>(), "OpenCASCADE could not determine an outer wire for the face.");
        return Wire::from_occt(outer_wire);
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Ref<Wire>(), occt_utils::exception_to_string(failure));
    }
}

Array Face::get_inner_wires() const {
    ERR_FAIL_COND_V_MSG(is_null(), Array(), "Face.get_inner_wires requires a non-null shape.");

    try {
        const TopoDS_Face face = TopoDS::Face(get_occt_shape());
        const TopoDS_Wire outer_wire = BRepTools::OuterWire(face);

        Array inner_wires;
        for (TopExp_Explorer explorer(face, TopAbs_WIRE); explorer.More(); explorer.Next()) {
            const TopoDS_Wire wire = TopoDS::Wire(explorer.Current());
            if (!outer_wire.IsNull() && wire.IsSame(outer_wire)) {
                continue;
            }
            inner_wires.push_back(Wire::from_occt(wire));
        }
        return inner_wires;
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Array(), occt_utils::exception_to_string(failure));
    }
}

Vector3 Face::get_normal() const {
    ERR_FAIL_COND_V_MSG(is_null(), Vector3(), "Face.get_normal requires a non-null shape.");

    try {
        const TopoDS_Face face = TopoDS::Face(get_occt_shape());
        Standard_Real umin = 0.0;
        Standard_Real umax = 0.0;
        Standard_Real vmin = 0.0;
        Standard_Real vmax = 0.0;
        BRepTools::UVBounds(face, umin, umax, vmin, vmax);

        const Handle(Geom_Surface) surface = BRep_Tool::Surface(face);
        ERR_FAIL_COND_V_MSG(surface.IsNull(), Vector3(), "OpenCASCADE could not determine a supporting surface for the face.");

        GeomLProp_SLProps properties(surface, (umin + umax) * 0.5, (vmin + vmax) * 0.5, 1, 1e-9);
        ERR_FAIL_COND_V_MSG(!properties.IsNormalDefined(), Vector3(), "OpenCASCADE could not determine the face normal.");

        gp_Dir normal = properties.Normal();
        if (face.Orientation() == TopAbs_REVERSED) {
            normal.Reverse();
        }
        return Vector3(
            static_cast<real_t>(normal.X()),
            static_cast<real_t>(normal.Y()),
            static_cast<real_t>(normal.Z())
        );
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Vector3(), occt_utils::exception_to_string(failure));
    }
}
