#ifndef BUILD123D_BOUNDBOX_H
#define BUILD123D_BOUNDBOX_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/ref.hpp>

#include <Bnd_Box.hxx>

using namespace godot;

class BoundBox : public RefCounted {
    GDCLASS(BoundBox, RefCounted);

private:
    Bnd_Box *wrapped;
    Vector3 min_pt;
    Vector3 max_pt;
    Vector3 size;

protected:
    static void _bind_methods();

public:
    BoundBox();
    ~BoundBox();

    // Static factory methods
    static Ref<BoundBox> create_from_bnd_box(const PackedByteArray &p_data);
    static Ref<BoundBox> create_from_shape(const Variant &p_shape, double p_tolerance = -1.0, bool p_optimal = true);

    // Wrapped access
    void set_wrapped(Bnd_Box *p_box);
    Bnd_Box *get_wrapped() const;

    // Properties
    Vector3 get_min() const;
    Vector3 get_max() const;
    Vector3 get_size() const;
    double get_measure() const;
    double get_diagonal() const;

    // Methods
    void add_point(const Vector3 &p_point, double p_tolerance = -1.0);
    void add_box(const Ref<BoundBox> &p_other);
    Vector3 center() const;
    bool is_inside(const Ref<BoundBox> &p_other) const;
    bool overlaps(const Ref<BoundBox> &p_other, double p_tolerance = 1e-6) const;
    Vector3 to_align_offset(const Variant &p_align) const;
};

#endif // BUILD123D_BOUNDBOX_H
