enable_testing()
include(GoogleTest)
fuzztest_setup_fuzzing_flags()

add_executable(fuzz_test_exec)

target_compile_features(fuzz_test_exec PUBLIC cxx_std_23)
target_compile_options(fuzz_test_exec PRIVATE ${CompilerFlags} "-DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION" "-UNDEBUG")
target_link_options(fuzz_test_exec PRIVATE ${LinkerFlags})


if(clang_tidy_FOUND)
    set_target_properties(fuzz_test_exec PROPERTIES CXX_CLANG_TIDY "${clang_tidy_FOUND}")
endif()

if(cppcheck_FOUND)
    set_target_properties(fuzz_test_exec PROPERTIES CXX_CPPCHECK "${cppckeck_FOUND}")
endif()

target_link_libraries(
    fuzz_test_exec

    PRIVATE 

    tictactoe_lib
)

target_sources(
    fuzz_test_exec

    PUBLIC 

    FILE_SET HEADERS 
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/../tictactoe_cli/src 

    PRIVATE 

    ${CMAKE_CURRENT_LIST_DIR}/../tictactoe_cli/tests/fuzz_test.cpp
)

link_fuzztest(fuzz_test_exec)
gtest_discover_tests(fuzz_test_exec)