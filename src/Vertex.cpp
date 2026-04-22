#include "Vertex.h"

#include "OCCTUtils.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>

using namespace godot;

void Vertex::_bind_methods() {
    ClassDB::bind_method(D_METHOD("build_vertex", "position"), &Vertex::build_vertex);
    ClassDB::bind_method(D_METHOD("get_position"), &Vertex::get_position);
}

Vertex::Vertex() = default;

Ref<Vertex> Vertex::from_occt(const TopoDS_Vertex &p_vertex) {
    Ref<Vertex> result;
    result.instantiate();
    result->set_occt_shape(p_vertex);
    return result;
}

void Vertex::build_vertex(const Vector3 &p_position) {
    try {
        BRepBuilderAPI_MakeVertex builder(occt_utils::to_occt_point(p_position));
        builder.Build();
        ERR_FAIL_COND_MSG(!builder.IsDone(), "OpenCASCADE vertex construction did not complete.");
        set_occt_shape(builder.Shape());
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}

Vector3 Vertex::get_position() const {
    ERR_FAIL_COND_V_MSG(is_null(), Vector3(), "Vertex.get_position requires a non-null shape.");

    try {
        return occt_utils::to_godot_vector3(BRep_Tool::Pnt(TopoDS::Vertex(get_occt_shape())));
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(Vector3(), occt_utils::exception_to_string(failure));
    }
}
