####
# This sets up the build system for the 'ObcProject' project, including
# components and deployments from project.cmake. In addition, it imports the core F Prime components.
####
cmake_minimum_required(VERSION 3.24.2)
project(ObcProject C CXX)
###
# F' Core Setup
# This includes all of the F prime core components, and imports the make-system.
###
include("${CMAKE_CURRENT_LIST_DIR}/lib/fprime/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
fprime_setup_included_code()

# ---- pigpio (cross-compiled from source) ----
include(ExternalProject)

set(PIGPIO_SOURCE_DIR "${FPRIME_PROJECT_ROOT}/lib/pigpio")
set(PIGPIO_INSTALL_DIR "${CMAKE_BINARY_DIR}/pigpio-install")

ExternalProject_Add(
    pigpio_ext
    SOURCE_DIR ${PIGPIO_SOURCE_DIR}
    CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX=${PIGPIO_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        "-DCMAKE_C_FLAGS=-std=gnu11 -Wno-error=incompatible-pointer-types -Wno-error=implicit-function-declaration"
    BUILD_BYPRODUCTS
        "${PIGPIO_INSTALL_DIR}/lib/libpigpio.so"
        "${PIGPIO_INSTALL_DIR}/include"
    INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install
)

file(MAKE_DIRECTORY "${PIGPIO_INSTALL_DIR}/include")

add_library(pigpio::pigpio SHARED IMPORTED GLOBAL)
set_property(TARGET pigpio::pigpio PROPERTY
    IMPORTED_LOCATION "${PIGPIO_INSTALL_DIR}/lib/libpigpio.so")
set_property(TARGET pigpio::pigpio PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES "${PIGPIO_INSTALL_DIR}/include")
add_dependencies(pigpio::pigpio pigpio_ext)
# -----------------------------------------

# This includes project-wide objects
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ObcProject")