#ifndef BUILD123D_LOCATION_H
#define BUILD123D_LOCATION_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <TopLoc_Location.hxx>

namespace build123d {

class Location : public godot::RefCounted {
    GDCLASS(Location, godot::RefCounted);

    TopLoc_Location wrapped;

protected:
    static void _bind_methods();

public:
    Location() = default;

    static godot::Ref<Location> create(
        const godot::Vector3 &p_position,
        const godot::Vector3 &p_orientation = godot::Vector3()
    );

    void set_position(const godot::Vector3 &p_position);
    godot::Vector3 get_position() const;

    void set_orientation(const godot::Vector3 &p_orientation);
    godot::Vector3 get_orientation() const;

    const TopLoc_Location &get_wrapped() const;
    void set_wrapped(const TopLoc_Location &p_location);
};

} // namespace build123d

using Location = build123d::Location;

#endif // BUILD123D_LOCATION_H
