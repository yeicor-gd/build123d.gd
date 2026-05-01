#ifndef BUILD123D_AXIS_H
#define BUILD123D_AXIS_H

#include "edge.h"
#include "location.h"

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <gp_Ax1.hxx>

namespace build123d {

class Axis : public godot::RefCounted {
    GDCLASS(Axis, godot::RefCounted);

    gp_Ax1 wrapped;

    static godot::Ref<Axis> create_from_gp_ax1(const gp_Ax1 &p_axis);

protected:
    static void _bind_methods();

public:
    Axis() = default;

    static godot::Ref<Axis> create(const godot::Vector3 &p_origin, const godot::Vector3 &p_direction);
    static godot::Ref<Axis> from_edge(const godot::Ref<Edge> &p_edge);
    static godot::Ref<Axis> from_location(const godot::Ref<Location> &p_location);

    void set_position(const godot::Vector3 &p_position);
    godot::Vector3 get_position() const;

    void set_direction(const godot::Vector3 &p_direction);
    godot::Vector3 get_direction() const;

    const gp_Ax1 &get_wrapped() const;
    void set_wrapped(const gp_Ax1 &p_axis);
};

} // namespace build123d

using Axis = build123d::Axis;

#endif // BUILD123D_AXIS_H
