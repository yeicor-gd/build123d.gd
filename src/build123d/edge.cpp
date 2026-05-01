#include "edge.h"

#include "occt_utils.h"

#include <BRepBuilderAPI_MakeEdge.hxx>

using namespace godot;

namespace build123d {

void Edge::_bind_methods() {
    ClassDB::bind_static_method("Edge", D_METHOD("make_line", "start", "end"), &Edge::make_line);
    ClassDB::bind_method(D_METHOD("is_valid"), &Edge::is_valid);
}

Ref<Edge> Edge::make_line(const Vector3 &p_start, const Vector3 &p_end) {
    Ref<Edge> edge;
    edge.instantiate();
    edge->wrapped = BRepBuilderAPI_MakeEdge(to_gp_pnt(p_start), to_gp_pnt(p_end)).Edge();
    return edge;
}

bool Edge::is_valid() const {
    return !wrapped.IsNull();
}

const TopoDS_Edge &Edge::get_wrapped() const {
    return wrapped;
}

void Edge::set_wrapped(const TopoDS_Edge &p_edge) {
    wrapped = p_edge;
}

} // namespace build123d
