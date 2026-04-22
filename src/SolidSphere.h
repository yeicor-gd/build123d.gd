#ifndef SOLID_SPHERE_H
#define SOLID_SPHERE_H

#include "TopoShape.h"

class SolidSphere : public TopoShape {
    GDCLASS(SolidSphere, TopoShape)

protected:
    static void _bind_methods();

public:
    SolidSphere();

    void build_sphere(double p_radius, const godot::Vector3 &p_center = godot::Vector3());
};

#endif // SOLID_SPHERE_H
