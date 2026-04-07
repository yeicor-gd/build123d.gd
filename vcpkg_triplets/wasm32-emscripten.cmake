include("triplets/community/wasm32-emscripten.cmake")

# CUSTOM:
if(PORT STREQUAL "opencascade")
  set(VCPKG_CMAKE_CONFIGURE_OPTIONS ${VCPKG_CMAKE_CONFIGURE_OPTIONS}
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON  # -fPIC required for wasm32 module
  )
endif()
