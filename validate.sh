#!/bin/sh

set -e

ERROR_FILE="${1:-}"
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

if [ -z "$GODOT_VERSION" ]; then
    echo "GODOT_VERSION environment variable is not set. Please set it to a valid Godot version (e.g., 3.5.1 or 'system')."
    exit 1
fi

if [ -z "$ERROR_FILE" ]; then
    echo "No error file specified. Errors will be printed to the console."
else
    echo "Errors will be written to: $ERROR_FILE"
fi

export VCPKG_ROOT="$SCRIPT_DIR/vcpkg"
export VCPKG_DISABLE_METRICS=1
#export VCPKG_DEFAULT_TRIPLET=x64-linux
export VCPKG_OVERLAY_TRIPLETS="$SCRIPT_DIR/vcpkg_triplets"
export VCPKG_OVERLAY_PORTS="$SCRIPT_DIR/vcpkg_ports"
export GDEXT_CMAKE_ARGS="-DGODOTCPP_TARGET=template_debug -DGODOTCPP_PRECISION=single -DGODOTCPP_THREADS=on -DENABLE_WERROR=on"
if [ "$GODOT_VERSION" != "system" ]; then
    export GDEXT_CMAKE_ARGS="$GDEXT_CMAKE_ARGS -DENABLE_SANITIZERS=on"
fi

DO_BUILD="${DO_BUILD:-1}"

run_checked() {
    tmp_output=$(mktemp)
    if "$@" >"$tmp_output" 2>&1; then
        rm -f "$tmp_output"
        return 0
    fi

    if [ -n "$ERROR_FILE" ]; then
        cat "$tmp_output" > "$ERROR_FILE"
    fi
    cat "$tmp_output"
    rm -f "$tmp_output"
    exit 1
}

echo "Validating doc_classes/*.xml against scripts/validate-doc_classes.xsd..."
for doc_file in "$SCRIPT_DIR"/doc_classes/*.xml; do
    run_checked xmllint --noout --schema "$SCRIPT_DIR/scripts/validate-doc_classes.xsd" "$doc_file"
done

echo "Validating doc_classes/*.xml against source bindings..."
run_checked python3 "$SCRIPT_DIR/scripts/validate_doc_bindings.py"

if [ "$DO_BUILD" = "1" ] || [ "$DO_BUILD" = "true" ]; then
    # Bootstrap vcpkg if needed
    if [ ! -f "$VCPKG_ROOT/vcpkg" ]; then
        echo "Bootstrapping vcpkg..."
        "$VCPKG_ROOT/bootstrap-vcpkg.sh" --disableMetrics
    fi

    "$VCPKG_ROOT/vcpkg" remove gdext 2>/dev/null || true
    rm -rf "$HOME/.cache/vcpkg/archives/" 2>/dev/null || true

    BUILD_LOG=$(mktemp)
    trap "rm -f '$BUILD_LOG'" EXIT

    echo "Regenerating register_types.cpp and register_types.h..."
    "$SCRIPT_DIR/src/register_types.sh"

    echo "Building extension..."
    "$VCPKG_ROOT/vcpkg" install gdext 2>&1 | tee "$BUILD_LOG"
    BUILD_EXIT=${PIPESTATUS[0]}

    if [ $BUILD_EXIT -ne 0 ]; then
        echo "Build failed!"
        if [ -n "$ERROR_FILE" ]; then
            grep -E "^(ERROR:|error:|fatal error:|CMake Error|FAILED:|ninja: build stopped|collect2: error:|ld: |undefined reference to |clang: error:)" "$BUILD_LOG" > "$ERROR_FILE" || true
        fi
        exit 1
    fi

    echo "Build succeeded! Running runtime validation..."
else
    echo "Skipping build (DO_BUILD=$DO_BUILD). Running runtime validation..."
fi

if [ "$GODOT_VERSION" = "system" ]; then
    # Use system Godot, no sanitizers, no build
    GODOT_BIN="${GODOT_BIN:-godot}"
else
    GODOT_BUILD_DIR="$SCRIPT_DIR/build"
    GODOT_SOURCE_DIR="$GODOT_BUILD_DIR/godot-$GODOT_VERSION"
    GODOT_BIN="$GODOT_BUILD_DIR/bin/godot-$GODOT_VERSION"

    if [ ! -d "$GODOT_SOURCE_DIR" ]; then
        echo "Downloading Godot $GODOT_VERSION sources..."
        mkdir -p "$GODOT_BUILD_DIR"
        cd "$GODOT_BUILD_DIR"
        curl -fsSL "https://github.com/godotengine/godot/archive/refs/tags/$GODOT_VERSION.zip" -o godot.zip
        unzip -qo godot.zip
        rm godot.zip
        cd "$SCRIPT_DIR"
    fi

    if [ ! -f "$GODOT_BIN" ]; then
        cd "$GODOT_SOURCE_DIR"
        GODOT_BUILD_LOG=$(mktemp)
        trap "rm -f '$BUILD_LOG' '$GODOT_BUILD_LOG'" EXIT

        echo "Compiling Godot with ASAN, UBSAN, and LSAN..."
        scons -j$(nproc) \
            platform=linux \
            target=editor \
            dev_build=yes \
            sanitizers=yes \
            use_asan=yes \
            use_lsan=yes \
            2>&1 | tee "$GODOT_BUILD_LOG"

        GODOT_BUILD_EXIT=${PIPESTATUS[0]}

        if [ $GODOT_BUILD_EXIT -ne 0 ]; then
            echo "Godot build failed!"
            if [ -n "$ERROR_FILE" ]; then
                {
                    echo "=== Godot Build Failed ==="
                    echo "See full build log above for details."
                } > "$ERROR_FILE"
            fi
            exit 1
        fi
        mkdir -p "$(dirname $GODOT_BIN)"
        mv "$GODOT_SOURCE_DIR/bin/godot.linuxbsd.editor.dev.x86_64.san" "$GODOT_BIN"
    fi
fi

cd "$SCRIPT_DIR"
MY_LD_PRELOAD=""
if [ "$GODOT_VERSION" != "system" ]; then
    MY_LD_PRELOAD="LD_PRELOAD=$(gcc -print-file-name=libasan.so)"
fi

IMPORT_LOG=$(mktemp)
trap "rm -f '$IMPORT_LOG'" EXIT
RUNTIME_LOG=$(mktemp)
trap "rm -f '$RUNTIME_LOG'" EXIT

eval "$MY_LD_PRELOAD LSAN_OPTIONS=detect_leaks=0 $GODOT_BIN --import --path \"$SCRIPT_DIR/demo\" --headless --quit 2>&1 | tee -a \"$IMPORT_LOG\"; EXIT_CODE=\${PIPESTATUS[0]}; if [ \$EXIT_CODE -ne 0 ]; then exit \$EXIT_CODE; fi"
eval "$MY_LD_PRELOAD $GODOT_BIN --path \"$SCRIPT_DIR/demo\" --headless 2>&1 | tee -a \"$RUNTIME_LOG\"; EXIT_CODE=\${PIPESTATUS[0]}; if [ \$EXIT_CODE -ne 0 ]; then exit \$EXIT_CODE; fi"

_extract_errors() {
    echo "$1" | \
    grep -E -v "(ObjectDB|RID).*leaked|resources still in use at exit" | \
    grep -E "^ERROR:|^SCRIPT ERROR:|^WARNING:|^handle_crash:|Shader compilation error|Script compilation error|Parse error|undefined method|undefined symbol|not found|No such|^TESTS FAILED|^handle_crash:" || return 0
}

ERRORS=$(_extract_errors "$IMPORT_LOG"$'\n'"$RUNTIME_LOG")

if [ -n "$ERRORS" ]; then
    echo "✗ Runtime validation failed - errors detected"
    if [ -n "$ERROR_FILE" ]; then
        echo "$ERRORS" > "$ERROR_FILE"
    else
        echo "$ERRORS"
    fi
    exit 1
fi

echo ""
echo "✓ Runtime validation passed - no errors detected"
[ -n "$ERROR_FILE" ] && >"$ERROR_FILE"
exit 0
