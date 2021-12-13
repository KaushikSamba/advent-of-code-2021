set(TARGET_NAME day-3)
set(TEST_TARGET_NAME ${TARGET_NAME}-test)

add_library(power-consumption-calc
                power_consumption_calculator.cpp            
)

add_executable( ${TARGET_NAME}
                    day-3-binary-diagnostic.cpp
                )

target_include_directories( ${TARGET_NAME} PUBLIC
                                ${CMAKE_SOURCE_DIR}
                            )

target_link_libraries(  ${TARGET_NAME}
                            utils
                     )

add_executable(
    ${TEST_TARGET_NAME}
    test.cpp
)
target_link_libraries(
    ${TEST_TARGET_NAME}
    gtest_main
    power-consumption-calc
)
                      
gtest_discover_tests(${TEST_TARGET_NAME})
