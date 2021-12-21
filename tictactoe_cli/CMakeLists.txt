# CMakeList.txt : CMake project for tictactoe_cli, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)

# Add source to this project's executable.
add_executable (tictactoe_cli "tictactoe_cli.cpp" "tictactoe_cli.h")

target_compile_definitions(tictactoe_cli PRIVATE COMMAND="${Clear_Command}")
