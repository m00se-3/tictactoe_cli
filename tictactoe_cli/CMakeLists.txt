# Add source to this project's executable.
add_executable (tictactoe_cli "tictactoe_cli.cpp" "tictactoe_cli.hpp")

target_compile_features(tictactoe_cli PUBLIC cxx_std_23)
target_compile_options(tictactoe_cli PRIVATE ${CompilerFlags})
target_link_options(tictactoe_cli PRIVATE ${LinkerFlags})

if(clang_tidy_FOUND)
    set_target_properties(tictactoe_cli PROPERTIES CXX_CLANG_TIDY ${clang_tidy_FOUND})
endif()

target_compile_definitions(tictactoe_cli PRIVATE HOST_OS="${CMAKE_HOST_SYSTEM_NAME}")
