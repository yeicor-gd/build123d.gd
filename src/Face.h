#ifndef FACE_H
#define FACE_H

#include "TopoShape.h"

#include <TopoDS_Face.hxx>

class Wire;
class Solid;

class Face : public TopoShape {
    GDCLASS(Face, TopoShape)

protected:
    static void _bind_methods();

public:
    Face();

    static godot::Ref<Face> from_occt(const TopoDS_Face &p_face);

    void build_from_wire(const godot::Ref<Wire> &p_wire, bool p_only_plane = false);
    void build_polygon(const godot::PackedVector3Array &p_points, bool p_only_plane = true);
    godot::Ref<Solid> extruded(const godot::Vector3 &p_direction) const;
    bool is_planar() const;
    godot::Ref<Wire> get_outer_wire() const;
    godot::Vector3 get_normal() const;
};

#endif // FACE_H
