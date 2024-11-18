# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.25)

project ("tictactoe_cli")

include(CTest)
include("cmake/Config.cmake")
include("CPM.cmake")

if(ccache_FOUND)
    message("-- Using ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${ccache_FOUND}")
    set(CPM_SOURCE_CACHE ${CMAKE_CURRENT_LIST_DIR}/.cache/CPM)
endif()

cpmaddpackage("gh:hanickadot/compile-time-regular-expressions@3.9.0")

add_subdirectory ("tictactoe_cli")

# Fuzz testing requires a Linux-based operating system.

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND TICTACTOE_FUZZING MATCHES ON)

    set(FUZZTEST_FUZZING_MODE ON)

    cpmaddpackage("gh:google/fuzztest#2024-10-28")
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/UnitTests.cmake)

endif()
