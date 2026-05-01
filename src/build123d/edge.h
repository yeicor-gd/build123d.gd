#ifndef BUILD123D_EDGE_H
#define BUILD123D_EDGE_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <TopoDS_Edge.hxx>

namespace build123d {

class Edge : public godot::RefCounted {
    GDCLASS(Edge, godot::RefCounted);

    TopoDS_Edge wrapped;

protected:
    static void _bind_methods();

public:
    Edge() = default;

    static godot::Ref<Edge> make_line(const godot::Vector3 &p_start, const godot::Vector3 &p_end);

    bool is_valid() const;

    const TopoDS_Edge &get_wrapped() const;
    void set_wrapped(const TopoDS_Edge &p_edge);
};

} // namespace build123d

using Edge = build123d::Edge;

#endif // BUILD123D_EDGE_H
