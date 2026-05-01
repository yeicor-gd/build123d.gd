# godot-cpp

## Introduction

godot-cpp provides C++ bindings for the Godot Engine's GDExtensions API, enabling developers to extend Godot's functionality using native C++ code. This library allows you to create custom nodes, resources, and editor plugins that integrate seamlessly with the Godot editor and runtime. GDExtensions built with godot-cpp can target multiple Godot versions through configurable API versioning, with extensions targeting earlier versions remaining compatible with later minor releases.

The library includes a complete object model mirroring Godot's class hierarchy, automatic memory management through reference counting, signal/slot mechanisms, property binding systems, and full access to Godot's variant type system. Building is supported through both SCons and CMake build systems across Windows, macOS, Linux, iOS, Android, and Web platforms. The codebase generates C++ bindings from Godot's extension API JSON files, providing type-safe wrappers for all engine classes and methods.

---

## Library Initialization

This is handled by register_types.sh, so you do not have to worry about it. Just re-run the script after defining a new GDCLASS.

---

## GDCLASS Macro

Declare custom classes that inherit from Godot engine classes using the GDCLASS macro, which sets up required type information, binding callbacks, and virtual method infrastructure.

```cpp
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class MyCustomNode : public Control {
    GDCLASS(MyCustomNode, Control);  // Declares class with parent

private:
    Vector2 custom_position;
    int custom_value = 0;

protected:
    static void _bind_methods();  // Required: must be implemented

    void _notification(int p_what);  // Optional: handle notifications
    bool _set(const StringName &p_name, const Variant &p_value);  // Optional: custom property setter
    bool _get(const StringName &p_name, Variant &r_ret) const;    // Optional: custom property getter

public:
    MyCustomNode();
    ~MyCustomNode();

    void set_custom_position(const Vector2 &pos);
    Vector2 get_custom_position() const;

    void set_custom_value(int value);
    int get_custom_value() const;

    void do_something();
};
```

---

## ClassDB Method Binding

Bind C++ methods to make them callable from GDScript and the Godot editor using ClassDB::bind_method with D_METHOD for argument naming.

```cpp
#include <godot_cpp/core/class_db.hpp>

void MyCustomNode::_bind_methods() {
    // Bind simple methods
    ClassDB::bind_method(D_METHOD("do_something"), &MyCustomNode::do_something);

    // Bind methods with arguments (argument names for editor/docs)
    ClassDB::bind_method(D_METHOD("set_custom_value", "value"), &MyCustomNode::set_custom_value);
    ClassDB::bind_method(D_METHOD("get_custom_value"), &MyCustomNode::get_custom_value);

    // Bind property getters/setters
    ClassDB::bind_method(D_METHOD("get_custom_position"), &MyCustomNode::get_custom_position);
    ClassDB::bind_method(D_METHOD("set_custom_position", "position"), &MyCustomNode::set_custom_position);

    // Bind methods with default arguments
    ClassDB::bind_method(D_METHOD("compute", "a", "b"), &MyCustomNode::compute, DEFVAL(100), DEFVAL(200));

    // Bind static methods
    ClassDB::bind_static_method("MyCustomNode", D_METHOD("static_helper", "a", "b"), &MyCustomNode::static_helper);
}

// Implementation
void MyCustomNode::set_custom_value(int value) { custom_value = value; }
int MyCustomNode::get_custom_value() const { return custom_value; }
void MyCustomNode::set_custom_position(const Vector2 &pos) { custom_position = pos; }
Vector2 MyCustomNode::get_custom_position() const { return custom_position; }
void MyCustomNode::do_something() { /* implementation */ }
```

## Static Constructors & Factory Methods

Godot classes exposed through `godot-cpp` always require a default (no-arg) constructor so the engine can instantiate them internally. However, you can simulate “custom constructors” by binding **static factory methods** that return new instances configured with arguments.

This is the idiomatic way to support construction with parameters or provide utility-style creation helpers.

```cpp
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class MyData : public RefCounted {
    GDCLASS(MyData, RefCounted);

private:
    int value = 0;
    String name;

protected:
    static void _bind_methods();

public:
    // Required default constructor
    MyData() = default;

    // Regular setters/getters
    void set_value(int v) { value = v; }
    int get_value() const { return value; }

    void set_name(const String &n) { name = n; }
    String get_name() const { return name; }

    // Static factory methods ("constructors")
    static Ref<MyData> create(int p_value, const String &p_name);
    static Ref<MyData> from_value(int p_value);
};
```

---

### Binding Static Constructors

Use `ClassDB::bind_static_method` to expose factory-style constructors to GDScript:

```cpp
void MyData::_bind_methods() {
    // Standard bindings
    ClassDB::bind_method(D_METHOD("set_value", "value"), &MyData::set_value);
    ClassDB::bind_method(D_METHOD("get_value"), &MyData::get_value);

    // Static "constructors"
    ClassDB::bind_static_method("MyData",
        D_METHOD("create", "value", "name"),
        &MyData::create);

    ClassDB::bind_static_method("MyData",
        D_METHOD("from_value", "value"),
        &MyData::from_value);
}
```

---

### Implementation of Factory Methods

These methods allocate and initialize instances, mimicking constructors with arguments:

```cpp
Ref<MyData> MyData::create(int p_value, const String &p_name) {
    Ref<MyData> instance = memnew(MyData);
    instance->set_value(p_value);
    instance->set_name(p_name);
    return instance;
}

Ref<MyData> MyData::from_value(int p_value) {
    Ref<MyData> instance = memnew(MyData);
    instance->set_value(p_value);
    return instance;
}
```

---

## Property Registration

Register properties that appear in the Godot inspector with property groups, subgroups, and hints for better organization.

```cpp
void MyCustomNode::_bind_methods() {
    // First bind the getter/setter methods
    ClassDB::bind_method(D_METHOD("get_health"), &MyCustomNode::get_health);
    ClassDB::bind_method(D_METHOD("set_health", "health"), &MyCustomNode::set_health);
    ClassDB::bind_method(D_METHOD("get_speed"), &MyCustomNode::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &MyCustomNode::set_speed);
    ClassDB::bind_method(D_METHOD("get_custom_position"), &MyCustomNode::get_custom_position);
    ClassDB::bind_method(D_METHOD("set_custom_position", "position"), &MyCustomNode::set_custom_position);

    // Create property groups in inspector
    ADD_GROUP("Stats", "stats_");
    ADD_SUBGROUP("Combat", "stats_combat_");

    // Register properties with PropertyInfo
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stats_combat_health"), "set_health", "get_health");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "stats_combat_speed"), "set_speed", "get_speed");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "custom_position"), "set_custom_position", "get_custom_position");
}
```

---

## Signal Declaration and Emission

Define custom signals that can be connected to from GDScript or other C++ classes, with typed arguments.

```cpp
void MyCustomNode::_bind_methods() {
    // Declare signals with arguments
    ADD_SIGNAL(MethodInfo("health_changed",
        PropertyInfo(Variant::INT, "old_health"),
        PropertyInfo(Variant::INT, "new_health")));

    ADD_SIGNAL(MethodInfo("custom_signal",
        PropertyInfo(Variant::STRING, "name"),
        PropertyInfo(Variant::INT, "value")));

    // Signal with no arguments
    ADD_SIGNAL(MethodInfo("died"));

    // Bind method to emit signal
    ClassDB::bind_method(D_METHOD("emit_custom_signal", "name", "value"), &MyCustomNode::emit_custom_signal);
}

void MyCustomNode::emit_custom_signal(const String &name, int value) {
    emit_signal("custom_signal", name, value);
}

void MyCustomNode::set_health(int new_health) {
    int old_health = health;
    health = new_health;
    emit_signal("health_changed", old_health, new_health);

    if (health <= 0) {
        emit_signal("died");
    }
}
```

---

## Constants and Enums

Expose constants, enums, and bitfield flags to GDScript with proper type casting support.

```cpp
class MyCustomNode : public Control {
    GDCLASS(MyCustomNode, Control);

public:
    enum State {
        STATE_IDLE,
        STATE_RUNNING,
        STATE_JUMPING,
        STATE_ANSWER = 42,
    };

    enum Flags {
        FLAG_INVINCIBLE = 1,
        FLAG_INVISIBLE = 2,
        FLAG_FLYING = 4,
    };

    enum {
        CONSTANT_WITHOUT_ENUM = 314,
    };

protected:
    static void _bind_methods() {
        // Bind enum constants
        BIND_ENUM_CONSTANT(STATE_IDLE);
        BIND_ENUM_CONSTANT(STATE_RUNNING);
        BIND_ENUM_CONSTANT(STATE_JUMPING);
        BIND_ENUM_CONSTANT(STATE_ANSWER);

        // Bind bitfield flags
        BIND_BITFIELD_FLAG(FLAG_INVINCIBLE);
        BIND_BITFIELD_FLAG(FLAG_INVISIBLE);
        BIND_BITFIELD_FLAG(FLAG_FLYING);

        // Bind standalone constants
        BIND_CONSTANT(CONSTANT_WITHOUT_ENUM);
    }
};

// Required for enum type casting in GDScript
VARIANT_ENUM_CAST(MyCustomNode::State);
VARIANT_BITFIELD_CAST(MyCustomNode::Flags);
```

---

## Ref Smart Pointer

Use Ref<T> for automatic reference counting of RefCounted-derived objects, preventing memory leaks and dangling pointers.

```cpp
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/image.hpp>

class MyResource : public RefCounted {
    GDCLASS(MyResource, RefCounted);

private:
    int id = 0;

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("set_id", "id"), &MyResource::set_id);
        ClassDB::bind_method(D_METHOD("get_id"), &MyResource::get_id);
        ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    }

public:
    void set_id(int p_id) { id = p_id; }
    int get_id() const { return id; }
};

// Usage examples
class MyNode : public Node {
    GDCLASS(MyNode, Node);

public:
    // Accept Ref as parameter
    int process_resource(Ref<MyResource> p_ref) {
        return p_ref.is_valid() ? p_ref->get_id() : -1;
    }

    // Accept const reference
    int process_resource_const(const Ref<MyResource> &p_ref) {
        return p_ref.is_valid() ? p_ref->get_id() : -1;
    }

    // Return empty ref
    Ref<MyResource> return_empty_ref() const {
        Ref<MyResource> ref;
        return ref;
    }

    // Create and return new ref
    Ref<MyResource> create_resource() const {
        Ref<MyResource> ref;
        ref.instantiate();  // Creates new instance
        ref->set_id(42);
        return ref;
    }

    // Work with engine types
    String process_image(Ref<Image> p_image) {
        return p_image.is_valid() ? String("valid") : String("invalid");
    }
};
```

---

## Memory Management

Use memnew/memdelete macros for proper Godot memory allocation that integrates with the engine's memory tracking.

```cpp
#include <godot_cpp/core/memory.hpp>

// Allocate single objects
MyClass *obj = memnew(MyClass);
MyClass *obj_with_args = memnew(MyClass(arg1, arg2));

// Delete objects
memdelete(obj);

// Allocate arrays
int *arr = memnew_arr(int, 100);  // Array of 100 ints

// Get array length
size_t len = memarr_len(arr);

// Delete arrays
memdelete_arr(arr);

// Raw memory allocation (rarely needed)
void *raw = memalloc(1024);  // Allocate 1024 bytes
raw = memrealloc(raw, 2048); // Reallocate to 2048 bytes
memfree(raw);                // Free memory

// Note: For RefCounted objects, use Ref<T> instead:
Ref<MyResource> ref;
ref.instantiate();  // Proper way to create RefCounted objects
// No need to manually delete - reference counting handles it
```

---

## Virtual Method Override

Override Godot engine virtual methods to customize node behavior, such as input handling and process callbacks.

```cpp
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/label.hpp>

class MyControl : public Control {
    GDCLASS(MyControl, Control);

protected:
    static void _bind_methods() {}

public:
    // Override _has_point for custom hit detection
    virtual bool _has_point(const Vector2 &point) const override {
        Label *label = get_node<Label>("Label");
        if (label) {
            label->set_text("Got point: " + Variant(point).stringify());
        }
        return false;  // Return true if point is inside control
    }

    // Override _input for input handling
    virtual void _input(const Ref<InputEvent> &event) override {
        const InputEventKey *key_event = Object::cast_to<const InputEventKey>(*event);
        if (key_event && key_event->is_pressed()) {
            // Handle key press
            emit_signal("key_pressed", key_event->get_keycode());
        }
    }

    // Override _process for frame updates
    virtual void _process(double delta) override {
        // Called every frame
    }

    // Override _ready for initialization
    virtual void _ready() override {
        // Called when node enters tree for first time
    }
};
```

---

## Notification Handling

Handle Godot's notification system for lifecycle events like entering/exiting the scene tree.

```cpp
class MyNode : public Node {
    GDCLASS(MyNode, Node);

protected:
    static void _bind_methods() {}

    void _notification(int p_what) {
        switch (p_what) {
            case NOTIFICATION_POSTINITIALIZE:
                // Called after object is fully initialized
                break;

            case NOTIFICATION_READY:
                // Equivalent to _ready(), called when node and children are ready
                setup_rpc_config();
                break;

            case NOTIFICATION_ENTER_TREE:
                // Called when node enters the scene tree
                initialize_values();
                break;

            case NOTIFICATION_EXIT_TREE:
                // Called when node exits the scene tree
                cleanup();
                break;

            case NOTIFICATION_PROCESS:
                // Called every frame if set_process(true)
                break;

            case NOTIFICATION_PHYSICS_PROCESS:
                // Called every physics frame if set_physics_process(true)
                break;
        }
    }

private:
    void setup_rpc_config() {
        Dictionary opts;
        opts["rpc_mode"] = MultiplayerAPI::RPC_MODE_AUTHORITY;
        opts["transfer_mode"] = MultiplayerPeer::TRANSFER_MODE_RELIABLE;
        opts["call_local"] = true;
        opts["channel"] = 0;
        rpc_config("my_rpc_method", opts);
    }

    void initialize_values() { /* ... */ }
    void cleanup() { /* ... */ }
};
```

---

## Custom Property List

Implement dynamic properties that can change at runtime using _get_property_list, _set, and _get methods.

```cpp
class MyNode : public Node {
    GDCLASS(MyNode, Node);

private:
    Vector3 property_from_list;
    Vector2 dynamic_props[3];

protected:
    static void _bind_methods() {}

    // Define dynamic properties
    void _get_property_list(List<PropertyInfo> *p_list) const {
        p_list->push_back(PropertyInfo(Variant::VECTOR3, "property_from_list"));

        // Add multiple indexed properties
        for (int i = 0; i < 3; i++) {
            p_list->push_back(PropertyInfo(Variant::VECTOR2, "dproperty_" + itos(i)));
        }
    }

    // Handle property setting
    bool _set(const StringName &p_name, const Variant &p_value) {
        String name = p_name;
        if (name.begins_with("dproperty_")) {
            int64_t index = name.get_slicec('_', 1).to_int();
            dynamic_props[index] = p_value;
            return true;
        }
        if (name == "property_from_list") {
            property_from_list = p_value;
            return true;
        }
        return false;
    }

    // Handle property getting
    bool _get(const StringName &p_name, Variant &r_ret) const {
        String name = p_name;
        if (name.begins_with("dproperty_")) {
            int64_t index = name.get_slicec('_', 1).to_int();
            r_ret = dynamic_props[index];
            return true;
        }
        if (name == "property_from_list") {
            r_ret = property_from_list;
            return true;
        }
        return false;
    }

    // Property revert support (reset button in inspector)
    bool _property_can_revert(const StringName &p_name) const {
        if (p_name == StringName("property_from_list") && property_from_list != Vector3(42, 42, 42)) {
            return true;
        }
        return false;
    }

    bool _property_get_revert(const StringName &p_name, Variant &r_property) const {
        if (p_name == StringName("property_from_list")) {
            r_property = Vector3(42, 42, 42);
            return true;
        }
        return false;
    }
};
```

---

## Vararg Methods

Bind methods that accept variable numbers of arguments using bind_vararg_method.

```cpp
class MyNode : public Node {
    GDCLASS(MyNode, Node);

protected:
    static void _bind_methods() {
        // Setup method info with minimum argument spec
        MethodInfo mi;
        mi.arguments.push_back(PropertyInfo(Variant::STRING, "format"));
        mi.name = "varargs_print";
        ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_print", &MyNode::varargs_print, mi);

        // Vararg method returning a value
        MethodInfo mi2;
        mi2.arguments.push_back(PropertyInfo(Variant::STRING, "separator"));
        mi2.name = "varargs_join";
        ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_join", &MyNode::varargs_join, mi2);
    }

public:
    // Vararg method returning Variant
    Variant varargs_print(const Variant **args, GDExtensionInt arg_count, GDExtensionCallError &error) {
        error.error = GDEXTENSION_CALL_OK;

        String result;
        for (int i = 0; i < arg_count; i++) {
            result += String(*args[i]);
            if (i < arg_count - 1) result += " ";
        }
        print_line(result);
        return arg_count;  // Return number of args processed
    }

    // Vararg method returning specific type
    String varargs_join(const Variant **args, GDExtensionInt arg_count, GDExtensionCallError &error) {
        error.error = GDEXTENSION_CALL_OK;

        if (arg_count < 1) return "";

        String separator = *args[0];
        String result;
        for (int i = 1; i < arg_count; i++) {
            if (i > 1) result += separator;
            result += String(*args[i]);
        }
        return result;
    }
};
```

---

## Callable and Signal Connection

Create and use Callable objects for connecting signals and deferred method calls.

```cpp
#include <godot_cpp/variant/callable_method_pointer.hpp>

class MyNode : public Node {
    GDCLASS(MyNode, Node);

public:
    // Get callable from method pointer
    Callable get_method_callable() {
        return callable_mp(this, &MyNode::on_event);
    }

    // Get callable for method with return value
    Callable get_ret_callable() {
        return callable_mp(this, &MyNode::process_data);
    }

    // Get callable for const method
    Callable get_const_callable() const {
        return callable_mp(this, &MyNode::get_info);
    }

    // Static method callable
    Callable get_static_callable() const {
        return callable_mp_static(&MyNode::static_handler);
    }

    // Callable with bound arguments
    void setup_bound_callable() {
        Callable c = Callable(this, "emit_signal").bind("custom_signal", "bound_name", 42);
        c.call();  // Calls emit_signal("custom_signal", "bound_name", 42)
    }

    // Connect signals using callables
    void connect_signals() {
        // Connect to own signal
        connect("custom_signal", callable_mp(this, &MyNode::on_custom_signal));

        // Connect to child node signal
        Button *button = get_node<Button>("Button");
        if (button) {
            button->connect("pressed", callable_mp(this, &MyNode::on_button_pressed));
        }
    }

private:
    void on_event(Object *sender, String message, int value) { /* ... */ }
    String process_data(Object *sender, String input, int count) { return input; }
    String get_info(Object *sender, String query, int id) const { return "info"; }
    static void static_handler(MyNode *node, String msg, int val) { /* ... */ }
    void on_custom_signal(const String &name, int value) { /* ... */ }
    void on_button_pressed() { /* ... */ }
};
```

---

## Class Registration Macros

Use different registration macros depending on whether your class is concrete, abstract, virtual, internal, or runtime-created.

```cpp
void initialize_my_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // Standard class registration - appears in Create dialog and scripting
    GDREGISTER_CLASS(MyNode);
    GDREGISTER_CLASS(MyResource);

    // Virtual class - can be instantiated but has virtual methods for override
    GDREGISTER_VIRTUAL_CLASS(MyVirtualBase);

    // Abstract class - cannot be instantiated directly (has pure virtual methods)
    GDREGISTER_ABSTRACT_CLASS(MyAbstractBase);

    // Internal class - not exposed to editor/scripting, only used internally
    GDREGISTER_INTERNAL_CLASS(MyInternalHelper);

    // Runtime class - can be registered/unregistered at runtime
    GDREGISTER_RUNTIME_CLASS(MyDynamicClass);
}

// Example class declarations
class MyVirtualBase : public Object {
    GDCLASS(MyVirtualBase, Object);
protected:
    static void _bind_methods() {}
};

class MyAbstractBase : public Object {
    GDCLASS(MyAbstractBase, Object);
protected:
    static void _bind_methods() {}
    virtual int compute() = 0;  // Pure virtual makes class abstract
};

class MyInternalHelper : public RefCounted {
    GDCLASS(MyInternalHelper, RefCounted);
protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("get_answer"), &MyInternalHelper::get_answer);
    }
public:
    int get_answer() const { return 42; }
};
```

---

## Working with Typed Arrays and Dictionaries

Use TypedArray<T> and TypedDictionary<K,V> for type-safe collections that integrate with Godot's type system.

```cpp
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>  // Godot 4.4+

class MyNode : public Node {
    GDCLASS(MyNode, Node);

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("test_tarray_arg", "array"), &MyNode::test_tarray_arg);
        ClassDB::bind_method(D_METHOD("test_tarray"), &MyNode::test_tarray);
        ClassDB::bind_method(D_METHOD("test_tdictionary"), &MyNode::test_tdictionary);
    }

public:
    // Process typed array argument
    int test_tarray_arg(const TypedArray<int64_t> &p_array) {
        int sum = 0;
        for (int i = 0; i < p_array.size(); i++) {
            sum += (int)p_array[i];
        }
        return sum;
    }

    // Return typed array
    TypedArray<Vector2> test_tarray() const {
        TypedArray<Vector2> arr;
        arr.resize(2);
        arr[0] = Vector2(1, 2);
        arr[1] = Vector2(2, 3);
        return arr;
    }

    // Nested typed arrays
    TypedArray<PackedInt32Array> test_typed_array_of_packed() const {
        TypedArray<PackedInt32Array> arr;
        PackedInt32Array packed1;
        packed1.push_back(1);
        packed1.push_back(2);
        arr.push_back(packed1);
        return arr;
    }

    // Typed dictionary (Godot 4.4+)
    TypedDictionary<Vector2, Vector2i> test_tdictionary() const {
        TypedDictionary<Vector2, Vector2i> dict;
        dict[Vector2(1, 2)] = Vector2i(2, 3);
        return dict;
    }

    // Standard dictionary
    Dictionary test_dictionary() const {
        Dictionary dict;
        dict["hello"] = "world";
        dict["foo"] = "bar";
        return dict;
    }
};
```

---

## Object Casting

Cast between object types using Object::cast_to<T> for safe type conversion at runtime.

```cpp
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/control.hpp>

class MyNode : public Control {
    GDCLASS(MyNode, Control);

public:
    // Cast Object to specific types
    bool test_object_cast_to_node(Object *p_object) const {
        return Object::cast_to<Node>(p_object) != nullptr;
    }

    bool test_object_cast_to_control(Object *p_object) const {
        return Object::cast_to<Control>(p_object) != nullptr;
    }

    bool test_object_cast_to_my_node(Object *p_object) const {
        return Object::cast_to<MyNode>(p_object) != nullptr;
    }

    // Cast from Variant
    bool test_variant_cast(const Variant &p_variant) const {
        Object *obj = p_variant;
        if (!obj) return false;

        Node *node = Object::cast_to<Node>(obj);
        return node != nullptr;
    }

    // Get typed child node
    void process_children() {
        for (int i = 0; i < get_child_count(); i++) {
            Node *child = get_child(i);

            // Try casting to specific type
            if (MyNode *my_child = Object::cast_to<MyNode>(child)) {
                my_child->do_something();
            } else if (Control *ctrl = Object::cast_to<Control>(child)) {
                ctrl->set_visible(true);
            }
        }
    }

    // Const casting for event handling
    void _input(const Ref<InputEvent> &event) override {
        const InputEventKey *key = Object::cast_to<const InputEventKey>(*event);
        if (key && key->is_pressed()) {
            handle_key(key->get_keycode());
        }
    }

private:
    void do_something() {}
    void handle_key(int keycode) {}
};
```

---

## Summary

godot-cpp provides a comprehensive framework for creating high-performance GDExtensions in C++. The primary use cases include implementing computationally intensive game systems like physics simulations, AI behavior trees, and procedural generation; creating custom rendering effects and shaders; building specialized editor tools and plugins; wrapping third-party C/C++ libraries for use in Godot projects; and developing reusable gameplay components that benefit from native performance. The library's type-safe bindings, automatic memory management through Ref<T>, and seamless integration with Godot's signal system make it ideal for projects requiring both the expressiveness of GDScript and the performance of native code.

Integration patterns typically involve creating a library structure with header files defining classes using GDCLASS macro, source files implementing _bind_methods for exposing functionality to GDScript, a registration module that initializes all custom types, and a .gdextension configuration file pointing to platform-specific compiled binaries. Extensions can target multiple Godot versions through the api_version build option, with backward compatibility ensuring extensions built for earlier versions work in newer engine releases. For complex projects, godot-cpp supports abstract base classes for defining interfaces, internal classes for implementation details hidden from scripts, and runtime class registration for dynamic type systems.
