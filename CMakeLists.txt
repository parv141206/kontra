cmake_minimum_required(VERSION 3.16)
project(Kontra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE KONTRA_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE KONTRA_HEADERS CONFIGURE_DEPENDS include/*.hpp)

add_library(kontra ${KONTRA_SOURCES} ${KONTRA_HEADERS})

target_include_directories(kontra PUBLIC include)

# ─────────────────────────────────────────────────────
# Only for testing
add_executable(kontra_test test/main.cpp)
target_link_libraries(kontra_test PRIVATE kontra)
target_include_directories(kontra_test PRIVATE include)
