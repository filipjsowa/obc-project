####
# F Prime CMakeLists.txt:
#
# SOURCES: list of source files (to be compiled)
# AUTOCODER_INPUTS: list of files to be passed to the autocoders
# DEPENDS: list of libraries that this module depends on
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/docs/reference/api/cmake/API/
#
####

# Module names are derived from the path from the nearest project/library/framework
# root when not specifically overridden by the developer, i.e. the module defined by
# `MyProj/Some/Path/CMakeLists.txt` will be named `MyProj_Some_Path`.

set(SERVO_DEPS "")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Use the pigpio baked into the cross-compile image
    add_library(pigpio::pigpio STATIC IMPORTED GLOBAL)
    set_target_properties(pigpio::pigpio PROPERTIES
        IMPORTED_LOCATION "$ENV{PIGPIO_ROOT}/lib/libpigpio.a"
        INTERFACE_INCLUDE_DIRECTORIES "$ENV{PIGPIO_ROOT}/include"
        INTERFACE_COMPILE_DEFINITIONS HAVE_PIGPIO
    )
    list(APPEND SERVO_DEPS pigpio::pigpio)
endif()

register_fprime_library(
    SOURCES "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.cpp"
    AUTOCODER_INPUTS "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.fpp"
    DEPENDS 
    ${SERVO_DEPS}
)
### Unit Tests ###
# register_fprime_ut(
#     AUTOCODER_INPUTS
#         "${CMAKE_CURRENT_LIST_DIR}/ServoComponent.fpp"
#     SOURCES
#         "${CMAKE_CURRENT_LIST_DIR}/test/ut/ServoComponentTestMain.cpp"
#         "${CMAKE_CURRENT_LIST_DIR}/test/ut/ServoComponentTester.cpp"
#     DEPENDS
#         STest # For rules-based testing
#     UT_AUTO_HELPERS
# )
