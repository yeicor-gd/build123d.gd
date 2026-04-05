#ifndef OPENCASCADE_VERSION_H
#define OPENCASCADE_VERSION_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>

#include <Standard_Version.hxx>

class OpenCascadeVersion : public godot::Object {
    GDCLASS(OpenCascadeVersion, godot::Object)

protected:
    static void _bind_methods() {
        godot::ClassDB::bind_method(godot::D_METHOD("get_version_string"), &OpenCascadeVersion::get_version_string);
        godot::ClassDB::bind_method(godot::D_METHOD("get_version_major"), &OpenCascadeVersion::get_version_major);
        godot::ClassDB::bind_method(godot::D_METHOD("get_version_minor"), &OpenCascadeVersion::get_version_minor);
        godot::ClassDB::bind_method(godot::D_METHOD("get_version_maintenance"), &OpenCascadeVersion::get_version_maintenance);
    }

public:
    godot::String get_version_string() const {
        return godot::String(OCC_VERSION_STRING);
    }

    int64_t get_version_major() const {
        return static_cast<int64_t>(OCC_VERSION_MAJOR);
    }

    int64_t get_version_minor() const {
        return static_cast<int64_t>(OCC_VERSION_MINOR);
    }

    int64_t get_version_maintenance() const {
        return static_cast<int64_t>(OCC_VERSION_MAINTENANCE);
    }
};

#endif // OPENCASCADE_VERSION_H
