# Add source to this project's executable.
add_executable (tictactoe_cli "tictactoe_cli.cpp" "tictactoe_cli.hpp")

target_compile_definitions(tictactoe_cli PRIVATE COMMAND="${Clear_Command}")
