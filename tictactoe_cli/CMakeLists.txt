add_library(tictactoe_lib)
add_executable(tictactoe_cli)

target_compile_features(tictactoe_lib PUBLIC cxx_std_23)
target_compile_options(tictactoe_lib PRIVATE ${CompilerFlags})
target_link_options(tictactoe_lib PRIVATE ${LinkerFlags})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND TICTACTOE_FUZZING MATCHES ON)
    target_compile_definitions(tictactoe_lib PRIVATE FUZZING)
endif()

target_compile_features(tictactoe_cli PUBLIC cxx_std_23)
target_compile_options(tictactoe_cli PRIVATE ${CompilerFlags})
target_link_options(tictactoe_cli PRIVATE ${LinkerFlags})

if(clang_tidy_FOUND)
    message("-- Using clang-tidy")
    set_target_properties(tictactoe_cli PROPERTIES CXX_CLANG_TIDY "${clang_tidy_FOUND}")
    set_target_properties(tictactoe_lib PROPERTIES CXX_CLANG_TIDY "${clang_tidy_FOUND}")
endif()

if(cppcheck_FOUND)
    message("-- Using cppcheck")
    set_target_properties(tictactoe_cli PROPERTIES CXX_CPPCHECK "${cppckeck_FOUND}")
    set_target_properties(tictactoe_lib PROPERTIES CXX_CPPCHECK "${cppckeck_FOUND}")
endif()

target_link_libraries(
    tictactoe_lib

    PRIVATE 

    ctre
)

target_link_libraries(
    tictactoe_cli

    PRIVATE 

    tictactoe_lib
)

target_sources(
    tictactoe_lib

    PUBLIC 

    FILE_SET HEADERS 
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/src

    FILES 
    ${CMAKE_CURRENT_LIST_DIR}/src/tictactoe_cli.hpp

    PRIVATE

    ${CMAKE_CURRENT_LIST_DIR}/src/tictactoe_cli.cpp
)

target_sources(
    tictactoe_cli

    PUBLIC 

    FILE_SET HEADERS 
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/src

    PRIVATE 

    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)
