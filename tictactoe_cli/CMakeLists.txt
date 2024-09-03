# CMakeList.txt : CMake project for tictactoe_cli, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)

# Add source to this project's executable.
add_executable (tictactoe_cli "tictactoe_cli.cpp" "tictactoe_cli.h")

set_target_properties(tictactoe_cli PROPERTIES CXX_STANDARD 23)

target_compile_definitions(tictactoe_cli PRIVATE COMMAND="${Clear_Command}")
