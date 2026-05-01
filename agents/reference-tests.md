# 🧪 GDScript TestRunner — Reference Guide

This test runner is **minimal, fast, and convention-based**:

* Test files are auto-discovered
* Test methods are auto-executed
* A test **passes if it returns `""` (empty string)**
* A test **fails if it returns a non-empty error message**

---

# 📁 1. File Structure & Discovery

## Where tests live

Inside the `demo/` project folder, in `res://tests/`

## Naming rules

* File must start with: `test_`
* File must end with: `.gd`

✅ Valid:

```
test_player.gd
test_inventory.gd
```

❌ Ignored:

```
player_test.gd
inventory_tests.gd
```

---

# 🧱 2. Basic Test File Structure

A test file is just a script with functions:

```gdscript
# res://tests/test_math.gd

func test_addition() -> String:
	if 2 + 2 != 4:
		return "Expected 2 + 2 to equal 4"
	return ""
```

### Key rules

* Every test method must start with: `test_`
* Must return a `String`
* `""` = pass
* `"error message"` = fail

---

# ✅ 3. Writing Good Tests

## 3.1 Use clear assertions

Prefer explicit checks:

```gdscript
func test_health_reduction() -> String:
	var health := 100
	health -= 20

	if health != 80:
		return "Health should be 80 after damage"

	return ""
```

---

## 3.2 Keep tests small and focused

Each test should verify **one behavior only**.

❌ Bad:

```gdscript
func test_player_everything() -> String:
	# movement + damage + inventory...
```

✅ Good:

```gdscript
func test_player_takes_damage() -> String:
func test_player_moves_right() -> String:
func test_player_inventory_add() -> String:
```

---

## 3.3 Use descriptive names

Names are your documentation:

```gdscript
func test_inventory_adds_item() -> String:
func test_inventory_rejects_duplicates() -> String:
```

---

# 🧰 4. Logging (Highly Recommended)

Use the built-in context logger:

```gdscript
TestRunner.ctx.log_info("Creating player")
TestRunner.ctx.log_debug("Health = %d" % health)
TestRunner.ctx.log_error("Unexpected state")
```

### When to log

* Debugging complex logic
* Tracking intermediate values
* Explaining failures

---

# 🧪 5. Testing Patterns

## 5.1 Arrange → Act → Assert

```gdscript
func test_score_increases() -> String:
	# Arrange
	var score := 0

	# Act
	score += 10

	# Assert
	if score != 10:
		return "Score should increase by 10"

	return ""
```

---

## 5.2 Testing expected failures

```gdscript
func test_divide_by_zero() -> String:
	var result = divide(10, 0)

	if result != null:
		return "Expected null when dividing by zero"

	return ""
```

---

## 5.3 Multiple checks (carefully)

You can include multiple assertions, but fail fast:

```gdscript
func test_player_defaults() -> String:
	var player = Player.new()

	if player.health != 100:
		return "Default health should be 100"

	if player.speed <= 0:
		return "Speed should be positive"

	return ""
```

---

# ⚙️ 6. Suite Behavior

Each file is a **test suite**.

The runner:

1. Loads the script
2. Finds all `test_` methods
3. Runs them in alphabetical order
4. Reports:

   * pass/fail
   * execution time

---

# 🚨 7. Failure Messages (Important)

Your failure message is the **only output explaining the issue**.

Make it count:

❌ Bad:

```gdscript
return "failed"
```

✅ Good:

```gdscript
return "Expected health=80, got %d" % health
```

---

# ⏱️ 8. Performance Awareness

Each test reports execution time.

Use this to:

* Detect slow logic
* Catch unintended heavy operations

---

# 🧼 9. Test Isolation

Each test should be independent.

❌ Bad:

```gdscript
var shared_player = Player.new()

func test_a():
	shared_player.health = 0

func test_b():
	# Depends on previous test!
```

✅ Good:

```gdscript
func test_a():
	var player = Player.new()

func test_b():
	var player = Player.new()
```

---

# 🧱 10. When to Write Tests

## ✅ Recommended

* Game logic (combat, scoring, rules)
* Data transformations
* Utility functions
* Systems with edge cases

## ⚠️ Less useful

* Pure UI layout
* Visual-only behavior
* Engine-dependent rendering

---

# 🧪 11. Example Full Test File

```gdscript
# res://tests/test_player.gd

func test_player_starts_with_full_health() -> String:
	var player = Player.new()

	if player.health != 100:
		return "Expected 100 health, got %d" % player.health

	return ""


func test_player_takes_damage() -> String:
	var player = Player.new()
	player.take_damage(25)

	if player.health != 75:
		return "Expected 75 health after damage, got %d" % player.health

	return ""


func test_player_cannot_go_below_zero() -> String:
	var player = Player.new()
	player.take_damage(999)

	if player.health < 0:
		return "Health should not go below zero"

	return ""
```

---

# 🧠 12. Mental Model

Think of this runner as:

> “A lightweight assertion system where **return value = result**”

No macros, no frameworks—just:

* Functions
* Strings
* Clear intent

---

# 🏁 13. Best Practices Summary

* ✔ One behavior per test
* ✔ Use clear, descriptive names
* ✔ Return meaningful error messages
* ✔ Keep tests isolated
* ✔ Log when debugging
* ✔ Prefer simple logic over cleverness
