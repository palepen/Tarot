add_executable(tests
    test_main.cpp
    test_lexer.cpp
    test_parser.cpp
    test_helper.cpp
    test_sema.cpp
    test_codegen.cpp
    test_operators.cpp
    test_control_flow.cpp
)

target_include_directories(tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tests
    PRIVATE
        libtarot
        Catch2::Catch2WithMain
)

target_compile_options(tests PRIVATE -frtti)

set(TEST_EXAMPLE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(TEST_EXAMPLE_DST_DIR ${CMAKE_BINARY_DIR}/test/example)

add_custom_command(
    TARGET tests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${TEST_EXAMPLE_SRC_DIR}
            ${TEST_EXAMPLE_DST_DIR}
    COMMENT "Copying test inputs from example/ to build/test/example/"
)

target_compile_definitions(tests
    PRIVATE EXAMPLE_DIR="${TEST_EXAMPLE_DST_DIR}"
)

include(Catch)
catch_discover_tests(tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test
    PROPERTIES ENVIRONMENT "TEST_EXAMPLE_DIR=${TEST_EXAMPLE_DST_DIR}"
)
