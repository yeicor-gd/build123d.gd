#ifndef SOLID_BOX_H
#define SOLID_BOX_H

#include "TopoShape.h"

class SolidBox : public TopoShape {
    GDCLASS(SolidBox, TopoShape)

protected:
    static void _bind_methods();

public:
    SolidBox();

    void build_box(const godot::Vector3 &p_size, const godot::Vector3 &p_origin = godot::Vector3());
};

#endif // SOLID_BOX_H
