cmake_minimum_required(VERSION 3.16)
project(Kontra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# ===================================================================
# DEFINING THE LIBRARY TARGET
# ===================================================================

file(GLOB_RECURSE KONTRA_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# The library definition now uses this always-fresh variable.
add_library(kontra ${KONTRA_SOURCES})

target_compile_options(kontra PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

target_include_directories(kontra PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
# ===================================================================
# INSTALLATION RULES
# ===================================================================

include(CMakePackageConfigHelpers)
include(GNUInstallDirs) 

install(TARGETS kontra
    EXPORT KontraTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT KontraTargets
    FILE KontraTargets.cmake
    NAMESPACE kontra::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kontra
)

configure_package_config_file(
    "kontra-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KontraConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/kontra"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KontraConfig.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/kontra"
)


# ===================================================================
# BUILD EXAMPLES (Opt-in for developers)
# By default, users of your library will NOT build these.
# To build them, a developer runs: cmake .. -DKONTRA_BUILD_EXAMPLES=ON
# ===================================================================

option(KONTRA_BUILD_EXAMPLES "Build the example executables" ON)

if(KONTRA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
