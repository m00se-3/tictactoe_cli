# Add source to this project's executable.
add_executable (tictactoe_cli)

target_compile_features(tictactoe_cli PUBLIC cxx_std_23)
target_compile_options(tictactoe_cli PRIVATE ${CompilerFlags})
target_link_options(tictactoe_cli PRIVATE ${LinkerFlags})

if(clang_tidy_FOUND)
    message("--- Using Clang Tidy")
    set_target_properties(tictactoe_cli PROPERTIES CXX_CLANG_TIDY ${clang_tidy_FOUND})
endif()

if(cppcheck_FOUND)
    message("--- Using CppCheck")
    set_target_properties(tictactoe_cli PROPERTIES CXX_CPPCHECK "${cppckeck_FOUND}")
endif()

target_link_libraries(
    tictactoe_cli

    PRIVATE 

    ctre
)

target_sources(
    tictactoe_cli

    PUBLIC 

    FILE_SET HEADERS 
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}

    FILES 
    ${CMAKE_CURRENT_LIST_DIR}/tictactoe_cli.hpp

    PRIVATE

    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tictactoe_cli.cpp
)
