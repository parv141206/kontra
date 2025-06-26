cmake_minimum_required(VERSION 3.16)
project(Kontra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE KONTRA_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE KONTRA_HEADERS CONFIGURE_DEPENDS include/*.hpp)

add_library(kontra ${KONTRA_SOURCES} ${KONTRA_HEADERS})
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
target_include_directories(kontra PUBLIC include)

# ─────────────────────────────────────────────────────
# Helper function to link an executable against the kontra library
function(link_kontra_test target)
    target_link_libraries(${target} PRIVATE kontra)
    target_include_directories(${target} PRIVATE include)
endfunction()

# ─────────────────────────────────────────────────────
# Examples
# Each example is defined as a separate executable target
# and then linked using helper function.

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