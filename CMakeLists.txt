cmake_minimum_required(VERSION 3.16)
project(Kontra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE KONTRA_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE KONTRA_HEADERS CONFIGURE_DEPENDS include/*.hpp)

add_library(kontra ${KONTRA_SOURCES} ${KONTRA_HEADERS})

target_include_directories(kontra PUBLIC include)

# ─────────────────────────────────────────────────────
# Test executable
function(link_kontra_test target)
    target_link_libraries(${target} PRIVATE kontra)
    target_include_directories(${target} PRIVATE include)
endfunction()

add_executable(test_main test/main.cpp)
add_executable(test_input test/input_box.cpp)

link_kontra_test(test_main)
link_kontra_test(test_input)