#include "ShapeList.h"

#include "Axis.h"
#include "TopoShape.h"

#include <godot_cpp/core/error_macros.hpp>

#include <algorithm>
#include <vector>

#include <gp_Dir.hxx>

using namespace godot;

namespace {

Vector3 shape_center(const Ref<TopoShape> &p_shape) {
    return (p_shape->get_bounding_box_min() + p_shape->get_bounding_box_max()) * 0.5;
}

Ref<ShapeList> shape_list_from_flattened(const Array &p_shapes) {
    Ref<ShapeList> list;
    list.instantiate();
    for (int64_t index = 0; index < p_shapes.size(); ++index) {
        const Ref<TopoShape> shape = p_shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        list->append(shape);
    }
    return list;
}

} // namespace

void ShapeList::_bind_methods() {
    ClassDB::bind_method(D_METHOD("append", "shape"), &ShapeList::append);
    ClassDB::bind_method(D_METHOD("size"), &ShapeList::size);
    ClassDB::bind_method(D_METHOD("is_empty"), &ShapeList::is_empty);
    ClassDB::bind_method(D_METHOD("get_item", "index"), &ShapeList::get_item);
    ClassDB::bind_method(D_METHOD("to_array"), &ShapeList::to_array);
    ClassDB::bind_method(D_METHOD("vertices"), &ShapeList::vertices);
    ClassDB::bind_method(D_METHOD("edges"), &ShapeList::edges);
    ClassDB::bind_method(D_METHOD("wires"), &ShapeList::wires);
    ClassDB::bind_method(D_METHOD("faces"), &ShapeList::faces);
    ClassDB::bind_method(D_METHOD("shells"), &ShapeList::shells);
    ClassDB::bind_method(D_METHOD("compounds"), &ShapeList::compounds);
    ClassDB::bind_method(D_METHOD("solids"), &ShapeList::solids);
    ClassDB::bind_method(D_METHOD("filter_by_position", "axis", "minimum", "maximum", "min_inclusive", "max_inclusive"), &ShapeList::filter_by_position, DEFVAL(true), DEFVAL(true));
    ClassDB::bind_method(D_METHOD("sort_by_distance", "other", "reverse"), &ShapeList::sort_by_distance, DEFVAL(false));
}

ShapeList::ShapeList() = default;

void ShapeList::append(const Ref<TopoShape> &p_shape) {
    ERR_FAIL_COND_MSG(p_shape.is_null() || p_shape->is_null(), "ShapeList.append requires a non-null TopoShape.");
    shapes.push_back(p_shape);
}

int64_t ShapeList::size() const {
    return shapes.size();
}

bool ShapeList::is_empty() const {
    return shapes.is_empty();
}

Ref<TopoShape> ShapeList::get_item(int64_t p_index) const {
    ERR_FAIL_INDEX_V_MSG(p_index, shapes.size(), Ref<TopoShape>(), "ShapeList.get_item index out of range.");
    return shapes[p_index];
}

Array ShapeList::to_array() const {
    return shapes;
}

Ref<ShapeList> ShapeList::vertices() const {
    Ref<ShapeList> result;
    result.instantiate();
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Array nested = shape->get_vertices();
        for (int64_t nested_index = 0; nested_index < nested.size(); ++nested_index) {
            result->append(nested[nested_index]);
        }
    }
    return result;
}

Ref<ShapeList> ShapeList::edges() const {
    Ref<ShapeList> result;
    result.instantiate();
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Array nested = shape->get_edges();
        for (int64_t nested_index = 0; nested_index < nested.size(); ++nested_index) {
            result->append(nested[nested_index]);
        }
    }
    return result;
}

Ref<ShapeList> ShapeList::wires() const {
    Ref<ShapeList> result;
    result.instantiate();
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Array nested = shape->get_wires();
        for (int64_t nested_index = 0; nested_index < nested.size(); ++nested_index) {
            result->append(nested[nested_index]);
        }
    }
    return result;
}

Ref<ShapeList> ShapeList::faces() const {
    Ref<ShapeList> result;
    result.instantiate();
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Array nested = shape->get_faces();
        for (int64_t nested_index = 0; nested_index < nested.size(); ++nested_index) {
            result->append(nested[nested_index]);
        }
    }
    return result;
}

Ref<ShapeList> ShapeList::shells() const {
    Ref<ShapeList> result;
    result.instantiate();
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Array nested = shape->get_shells();
        for (int64_t nested_index = 0; nested_index < nested.size(); ++nested_index) {
            result->append(nested[nested_index]);
        }
    }
    return result;
}

Ref<ShapeList> ShapeList::compounds() const {
    Ref<ShapeList> result;
    result.instantiate();
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Array nested = shape->get_compounds();
        for (int64_t nested_index = 0; nested_index < nested.size(); ++nested_index) {
            result->append(nested[nested_index]);
        }
    }
    return result;
}

Ref<ShapeList> ShapeList::solids() const {
    Ref<ShapeList> result;
    result.instantiate();
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Array nested = shape->get_solids();
        for (int64_t nested_index = 0; nested_index < nested.size(); ++nested_index) {
            result->append(nested[nested_index]);
        }
    }
    return result;
}

Ref<ShapeList> ShapeList::filter_by_position(const Ref<Axis> &p_axis, double p_minimum, double p_maximum, bool p_min_inclusive, bool p_max_inclusive) const {
    ERR_FAIL_COND_V_MSG(p_axis.is_null(), Ref<ShapeList>(), "ShapeList.filter_by_position requires a non-null axis.");
    ERR_FAIL_COND_V_MSG(p_minimum > p_maximum, Ref<ShapeList>(), "ShapeList.filter_by_position requires minimum <= maximum.");

    const gp_Dir direction = p_axis->get_occt_axis().Direction();
    const Vector3 origin = p_axis->get_origin();

    std::vector<std::pair<double, Ref<TopoShape>>> filtered;
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        const Vector3 center = shape_center(shape);
        const Vector3 relative = center - origin;
        const double position = static_cast<double>(relative.x) * direction.X() + static_cast<double>(relative.y) * direction.Y() + static_cast<double>(relative.z) * direction.Z();

        const bool above_min = p_min_inclusive ? position >= p_minimum : position > p_minimum;
        const bool below_max = p_max_inclusive ? position <= p_maximum : position < p_maximum;
        if (above_min && below_max) {
            filtered.emplace_back(position, shape);
        }
    }

    std::sort(filtered.begin(), filtered.end(), [](const auto &p_a, const auto &p_b) {
        return p_a.first < p_b.first;
    });

    Array ordered;
    for (const auto &entry : filtered) {
        ordered.push_back(entry.second);
    }
    return shape_list_from_flattened(ordered);
}

Ref<ShapeList> ShapeList::sort_by_distance(const Ref<TopoShape> &p_other, bool p_reverse) const {
    ERR_FAIL_COND_V_MSG(p_other.is_null() || p_other->is_null(), Ref<ShapeList>(), "ShapeList.sort_by_distance requires a non-null shape.");

    const Vector3 other_center = shape_center(p_other);
    std::vector<std::pair<double, Ref<TopoShape>>> ordered;
    ordered.reserve(shapes.size());
    for (int64_t index = 0; index < shapes.size(); ++index) {
        const Ref<TopoShape> shape = shapes[index];
        if (shape.is_null() || shape->is_null()) {
            continue;
        }
        ordered.emplace_back(shape_center(shape).distance_to(other_center), shape);
    }

    std::sort(ordered.begin(), ordered.end(), [p_reverse](const auto &p_a, const auto &p_b) {
        if (p_reverse) {
            return p_a.first > p_b.first;
        }
        return p_a.first < p_b.first;
    });

    Array sorted;
    for (const auto &entry : ordered) {
        sorted.push_back(entry.second);
    }
    return shape_list_from_flattened(sorted);
}
