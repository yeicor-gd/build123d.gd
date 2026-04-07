include("triplets/community/wasm32-emscripten.cmake")

# CUSTOM:
set(VCPKG_CMAKE_CONFIGURE_OPTIONS ${VCPKG_CMAKE_CONFIGURE_OPTIONS}
  -DCMAKE_POSITION_INDEPENDENT_CODE=ON  # -fPIC required for wasm32 module
)

if(GODOTCPP_THREADS)
  set(VCPKG_CMAKE_CONFIGURE_OPTIONS ${VCPKG_CMAKE_CONFIGURE_OPTIONS}
    -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -matomics -mbulk-memory"  # Required for threads support in wasm32
    -DCMAKE_C_FLAGS="${CMAKE_C_FLAGS} -matomics -mbulk-memory"  # Required for threads support in wasm32
  )
endif()
