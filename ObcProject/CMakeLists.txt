# This CMake file is intended to register project-wide objects.
# This allows for reuse between deployments, or other projects.

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components")

include(FetchContent)

FetchContent_Declare(
    pigpio
    GIT_REPOSITORY https://github.com/joan2937/pigpio.git
    GIT_TAG master
)
