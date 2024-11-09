# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.25)

project ("tictactoe_cli")

include("cmake/Config.cmake")

# Include sub-projects.
add_subdirectory ("tictactoe_cli")
