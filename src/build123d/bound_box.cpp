#include "bound_box.h"
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <Bnd_Box.hxx>
#include <gp_Pnt.hxx>

using namespace godot;

BoundBox::BoundBox() {
    wrapped = new Bnd_Box();
    min_pt = Vector3();
    max_pt = Vector3();
    size = Vector3();
}

BoundBox::~BoundBox() {
    delete wrapped;
}

void BoundBox::_bind_methods() {
    // Static factory methods
    ClassDB::bind_static_method("BoundBox", D_METHOD("create_from_bnd_box", "data"), &BoundBox::create_from_bnd_box);
    ClassDB::bind_static_method("BoundBox", D_METHOD("create_from_shape", "shape", "tolerance", "optimal"), &BoundBox::create_from_shape, DEFVAL(-1.0), DEFVAL(true));

    // Properties
    ClassDB::bind_method(D_METHOD("get_min"), &BoundBox::get_min);
    ClassDB::bind_method(D_METHOD("get_max"), &BoundBox::get_max);
    ClassDB::bind_method(D_METHOD("get_size"), &BoundBox::get_size);
    ClassDB::bind_method(D_METHOD("get_measure"), &BoundBox::get_measure);
    ClassDB::bind_method(D_METHOD("get_diagonal"), &BoundBox::get_diagonal);

    // Methods
    ClassDB::bind_method(D_METHOD("add_point", "point", "tolerance"), &BoundBox::add_point, DEFVAL(-1.0));
    ClassDB::bind_method(D_METHOD("add_box", "other"), &BoundBox::add_box);
    ClassDB::bind_method(D_METHOD("center"), &BoundBox::center);
    ClassDB::bind_method(D_METHOD("is_inside", "other"), &BoundBox::is_inside);
    ClassDB::bind_method(D_METHOD("overlaps", "other", "tolerance"), &BoundBox::overlaps, DEFVAL(1e-6));
    ClassDB::bind_method(D_METHOD("to_align_offset", "align"), &BoundBox::to_align_offset);

    // Property registration
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "min"), "", "get_min");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "max"), "", "get_max");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "size"), "", "get_size");
}

Ref<BoundBox> BoundBox::create_from_bnd_box(const PackedByteArray &p_data) {
    Ref<BoundBox> box;
    box.instantiate();
    if (p_data.size() >= sizeof(Bnd_Box)) {
        box->wrapped = new Bnd_Box();
        memcpy(box->wrapped, p_data.ptr(), sizeof(Bnd_Box));
        // Update min/max/size
        if (!box->wrapped->IsVoid()) {
            Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
            box->wrapped->Get(xmin, ymin, zmin, xmax, ymax, zmax);
            box->min_pt = Vector3(xmin, ymin, zmin);
            box->max_pt = Vector3(xmax, ymax, zmax);
            box->size = Vector3(xmax - xmin, ymax - ymin, zmax - zmin);
        }
    }
    return box;
}

Ref<BoundBox> BoundBox::create_from_shape(const Variant &p_shape, double p_tolerance, bool p_optimal) {
    // This will be implemented when Shape class is added
    Ref<BoundBox> box;
    box.instantiate();
    box->wrapped = new Bnd_Box();
    return box;
}

void BoundBox::set_wrapped(Bnd_Box *p_box) {
    if (wrapped) delete wrapped;
    wrapped = p_box;
    if (wrapped && !wrapped->IsVoid()) {
        Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
        wrapped->Get(xmin, ymin, zmin, xmax, ymax, zmax);
        min_pt = Vector3(xmin, ymin, zmin);
        max_pt = Vector3(xmax, ymax, zmax);
        size = Vector3(xmax - xmin, ymax - ymin, zmax - zmin);
    }
}

Bnd_Box *BoundBox::get_wrapped() const {
    return wrapped;
}

Vector3 BoundBox::get_min() const {
    return min_pt;
}

Vector3 BoundBox::get_max() const {
    return max_pt;
}

Vector3 BoundBox::get_size() const {
    return size;
}

double BoundBox::get_measure() const {
    if (wrapped && !wrapped->IsVoid()) {
        return size.x * size.y * size.z; // Volume for 3D
    }
    return 0.0;
}

double BoundBox::get_diagonal() const {
    if (wrapped && !wrapped->IsVoid()) {
        return Math::sqrt(size.x * size.x + size.y * size.y + size.z * size.z);
    }
    return 0.0;
}

void BoundBox::add_point(const Vector3 &p_point, double p_tolerance) {
    if (!wrapped) wrapped = new Bnd_Box();
    wrapped->Add(gp_Pnt(p_point.x, p_point.y, p_point.z));
    // Update min/max/size
    if (!wrapped->IsVoid()) {
        Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
        wrapped->Get(xmin, ymin, zmin, xmax, ymax, zmax);
        min_pt = Vector3(xmin, ymin, zmin);
        max_pt = Vector3(xmax, ymax, zmax);
        size = Vector3(xmax - xmin, ymax - ymin, zmax - zmin);
    }
}

void BoundBox::add_box(const Ref<BoundBox> &p_other) {
    if (p_other.is_valid() && p_other->get_wrapped()) {
        if (!wrapped) wrapped = new Bnd_Box();
        wrapped->Add(*p_other->get_wrapped());
        // Update min/max/size
        if (!wrapped->IsVoid()) {
            Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
            wrapped->Get(xmin, ymin, zmin, xmax, ymax, zmax);
            min_pt = Vector3(xmin, ymin, zmin);
            max_pt = Vector3(xmax, ymax, zmax);
            size = Vector3(xmax - xmin, ymax - ymin, zmax - zmin);
        }
    }
}

Vector3 BoundBox::center() const {
    if (wrapped && !wrapped->IsVoid()) {
        return Vector3(
            (min_pt.x + max_pt.x) / 2.0,
            (min_pt.y + max_pt.y) / 2.0,
            (min_pt.z + max_pt.z) / 2.0
        );
    }
    return Vector3();
}

bool BoundBox::is_inside(const Ref<BoundBox> &p_other) const {
    if (!wrapped || !p_other.is_valid() || !p_other->get_wrapped()) {
        return false;
    }
    if (wrapped->IsVoid() || p_other->get_wrapped()->IsVoid()) {
        return false;
    }
    // Check if other is inside this box
    Vector3 other_min = p_other->get_min();
    Vector3 other_max = p_other->get_max();
    return (other_min.x >= min_pt.x && other_max.x <= max_pt.x &&
            other_min.y >= min_pt.y && other_max.y <= max_pt.y &&
            other_min.z >= min_pt.z && other_max.z <= max_pt.z);
}

bool BoundBox::overlaps(const Ref<BoundBox> &p_other, double p_tolerance) const {
    if (!wrapped || !p_other.is_valid() || !p_other->get_wrapped()) {
        return false;
    }
    if (wrapped->IsVoid() || p_other->get_wrapped()->IsVoid()) {
        return false;
    }
    Vector3 other_min = p_other->get_min();
    Vector3 other_max = p_other->get_max();
    // Check for overlap (with tolerance)
    return !(other_max.x < min_pt.x - p_tolerance ||
            other_min.x > max_pt.x + p_tolerance ||
            other_max.y < min_pt.y - p_tolerance ||
            other_min.y > max_pt.y + p_tolerance ||
            other_max.z < min_pt.z - p_tolerance ||
            other_min.z > max_pt.z + p_tolerance);
}

Vector3 BoundBox::to_align_offset(const Variant &p_align) const {
    // This will be implemented with Align enum
    return Vector3();
}
