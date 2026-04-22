#ifndef SOLID_CONE_H
#define SOLID_CONE_H

#include "TopoShape.h"

class SolidCone : public TopoShape {
    GDCLASS(SolidCone, TopoShape)

protected:
    static void _bind_methods();

public:
    SolidCone();

    void build_cone(double p_radius_bottom, double p_radius_top, double p_height, const godot::Vector3 &p_origin = godot::Vector3());
};

#endif // SOLID_CONE_H
