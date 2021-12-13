set(TARGET_NAME utils)

add_library(${TARGET_NAME}
                filehandler.cpp
                input_parser.cpp
)

set(TEST_TARGET_NAME ${TARGET_NAME}-test)

add_executable(
    ${TEST_TARGET_NAME}
    test.cpp
)
target_link_libraries(
    ${TEST_TARGET_NAME}
    gtest_main
    ${TARGET_NAME}
)
                      
gtest_discover_tests(${TEST_TARGET_NAME})
