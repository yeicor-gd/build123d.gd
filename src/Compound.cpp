#include "Compound.h"

#include "OCCTUtils.h"

#include <godot_cpp/core/error_macros.hpp>

#include <BRep_Builder.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Iterator.hxx>

using namespace godot;

void Compound::_bind_methods() {
    ClassDB::bind_method(D_METHOD("build_compound", "shapes"), &Compound::build_compound);
    ClassDB::bind_method(D_METHOD("get_child_count"), &Compound::get_child_count);
}

Compound::Compound() = default;

Ref<Compound> Compound::from_occt(const TopoDS_Compound &p_compound) {
    Ref<Compound> result;
    result.instantiate();
    result->set_occt_shape(p_compound);
    return result;
}

void Compound::build_compound(const Array &p_shapes) {
    ERR_FAIL_COND_MSG(p_shapes.is_empty(), "Compound.build_compound requires at least one child shape.");

    try {
        BRep_Builder builder;
        TopoDS_Compound compound;
        builder.MakeCompound(compound);

        for (int64_t index = 0; index < p_shapes.size(); ++index) {
            Ref<TopoShape> child = p_shapes[index];
            ERR_FAIL_COND_MSG(child.is_null() || child->is_null(), "Compound.build_compound requires all child shapes to be non-null TopoShape instances.");
            builder.Add(compound, child->get_occt_shape());
        }

        set_occt_shape(compound);
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_MSG(occt_utils::exception_to_string(failure));
    }
}

int Compound::get_child_count() const {
    ERR_FAIL_COND_V_MSG(is_null(), 0, "Compound.get_child_count requires a non-null shape.");

    try {
        int count = 0;
        for (TopoDS_Iterator iterator(get_occt_shape()); iterator.More(); iterator.Next()) {
            ++count;
        }
        return count;
    } catch (const Standard_Failure &failure) {
        ERR_FAIL_V_MSG(0, occt_utils::exception_to_string(failure));
    }
}
