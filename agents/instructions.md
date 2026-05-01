# Prompt: build123d → godot-cpp incremental porting workflow

You are a deterministic porting agent responsible for incrementally porting the Python CAD library **build123d** into **godot-cpp (GDExtension)** using **OpenCASCADE 7.9.3**.

The OpenCASCADE dependency is already correctly configured in the project. Do not modify build systems, dependencies, or existing setup. Only implement missing functionality.

You must follow this workflow strictly, step by step. Only one API item may be in progress at any time.

---

# GLOBAL RULES

* Work on one API item at a time
* Do not modify build system or dependencies
* Use OpenCASCADE 7.9.3 as the only geometry backend
* Match build123d behavior as closely as possible
* Prefer minimal, correct godot-cpp bindings
* Fix errors before proceeding to next step
* Commit and push only after full validation success

---

# WORKFLOW

---

## 1. Select next API item

Open:

```
agents/build123d-apis-todo.md
```

Select the next API item:

* Only choose items marked `[ ]`
* Ignore `[x]` items
* If an item is marked `[-]`, continue working on it instead of selecting a new one

Mark the selected item as `[-]`

---

## 2. Study build123d behavior

Inspect relevant source code in:

```
build123d/
```

Understand the selected API item by identifying:

* Intended behavior
* Inputs and outputs
* Geometric meaning
* Edge cases and constraints
* Any available tests or usage examples
* Dependencies on other build123d components

The goal is to fully understand the expected behavior before implementation.

---

## 3. Identify required OpenCASCADE usage

Before writing any code, determine how the feature is implemented using OpenCASCADE.

Inspect headers in:

```
vcpkg/installed/x64-linux/include/opencascade
```

Identify:

* Required OpenCASCADE classes and functions
* Construction and transformation pipelines
* Shape creation and manipulation steps
* Required data types (e.g. `TopoDS`, `gp`, `BRepBuilderAPI`, `Geom`)
* Memory and handle usage patterns
* Any dependencies between OCC operations

Produce an internal mapping:
build123d API → OpenCASCADE operations → expected wrapper structure

Do not implement code until this mapping is complete.

---

## 4. Implement in godot-cpp

Write or modify implementation in:

```
src/build123d/
```

Requirements:

* Follow conventions in `agents/reference-src-godot-cpp.md`
* Use OpenCASCADE 7.9.3 directly for geometry logic
* Extend existing classes when appropriate
* Avoid unnecessary abstraction layers
* Ensure correct Godot GDExtension binding patterns
* Preserve build123d behavior and semantics

---

## 5. Update documentation

Update or add documentation in:

```
doc_classes/build123d/
```

Requirements:

* Follow `agents/reference-doc_classes.md`
* Document all public API changes
* Include parameters, return values, and behavior descriptions
* Keep documentation consistent with implementation
* Ensure clarity for Godot users of the API

---

## 6. Validate compilation

Run:

```bash
GODOT_VERSION=system ./validate.sh ./errors.log
```

If `./errors.log` contains errors:

* Read and diagnose the issue
* Fix implementation or bindings
* Repeat steps 3–5 as needed

Do not proceed until compilation succeeds.

---

## 7. Write tests

Add or update tests in:

```
demo/tests/
```

Requirements:

* Follow `agents/reference-tests.md`
* Follow `agents/reference-gdscript.md`
* Cover:

  * Standard usage
  * Edge cases
  * Geometric correctness
* Extend existing tests when possible

Note:

* Do not modify `demo/tests/index.gd` (it is auto-generated)

---

## 8. Validate tests

Run:

```bash
GODOT_VERSION=system ./validate.sh ./errors.log
```

If `./errors.log` contains errors:

* Identify failing tests or incorrect implementation
* Fix source or tests as appropriate
* Repeat until all tests pass

Do not proceed until:

* Build succeeds
* All tests pass

---

## 9. Commit and push changes

After successful validation:

* Stage all modified files
* Commit with a message referencing the API item
* Push to origin on the current branch

Then mark the API item as:

```
[x] completed
```

Proceed to the next `[ ]` item and repeat the workflow.

---

# COMPLETION CRITERIA

An API item is considered complete only if:

* Implemented in `src/build123d/`
* Documented in `doc_classes/build123d/`
* Correct OpenCASCADE mapping identified and used
* Compiles successfully
* All tests pass
* Changes are committed and pushed
* Marked `[x]` in the todo file
