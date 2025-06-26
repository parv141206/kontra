cmake_minimum_required(VERSION 3.16)
project(Kontra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Library Definition ---
file(GLOB_RECURSE KONTRA_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE KONTRA_HEADERS CONFIGURE_DEPENDS include/*.hpp)

add_library(kontra ${KONTRA_SOURCES} ${KONTRA_HEADERS})
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# This is crucial: it makes sure that anyone using your library
# automatically gets the 'include' directory in their include paths.
target_include_directories(kontra PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ───────────────────────────────────────────────────────────────────
# Build Examples (Optional for users)
# This option allows users to disable building your examples if they
# only want to build the library.
option(KONTRA_BUILD_EXAMPLES "Build the example executables" ON)

if(KONTRA_BUILD_EXAMPLES)
    # Helper function to link an executable against the kontra library
    function(link_kontra_test target)
        target_link_libraries(${target} PRIVATE kontra)
    endfunction()

    add_executable(run_main examples/main.cpp)
    link_kontra_test(run_main)

    add_executable(run_border_example examples/border_example.cpp)
    link_kontra_test(run_border_example)

    add_executable(run_button_example examples/button_example.cpp)
    link_kontra_test(run_button_example)

    add_executable(run_flex_example examples/flex_example.cpp)
    link_kontra_test(run_flex_example)

    add_executable(run_input_box_example examples/input_box_example.cpp)
    link_kontra_test(run_input_box_example)

    add_executable(run_list_example examples/list_example.cpp)
    link_kontra_test(run_list_example)

    add_executable(run_todo_showcase examples/showcase/todo_app_showcase.cpp)
    link_kontra_test(run_todo_showcase)
endif()


# ───────────────────────────────────────────────────────────────────
# Installation Rules
# This section defines how to "install" the library.
# ───────────────────────────────────────────────────────────────────

# This helper module is needed for creating the config files.
include(CMakePackageConfigHelpers)

# Install the compiled library target (kontra.lib/kontra.a)
# The EXPORT command saves this target's information for other projects to use.
install(TARGETS kontra
    EXPORT kontra-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install all the public headers from the 'include' directory.
install(DIRECTORY include/
    DESTINATION include
)

# Generate and install the CMake package files. This is what allows
# another CMake project to find and use your library with `find_package(Kontra)`.
install(EXPORT kontra-targets
    FILE KontraTargets.cmake
    NAMESPACE kontra::
    DESTINATION lib/cmake/kontra
)

configure_package_config_file(
    "kontra-config.cmake.in"
    "KontraConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/kontra"
)