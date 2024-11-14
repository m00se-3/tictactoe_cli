# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.25)

project ("tictactoe_cli")

include("cmake/Config.cmake")
include("CPM.cmake")

if(ccache_FOUND)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${ccache_FOUND})
    set(CPM_SOURCE_CACHE ${CMAKE_CURRENT_LIST_DIR}/.cache/CPM)
endif()

cpmaddpackage("gh:hanickadot/compile-time-regular-expressions@3.9.0")

# Include sub-projects.
add_subdirectory ("tictactoe_cli")
