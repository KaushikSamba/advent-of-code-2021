set(TARGET_NAME day-5)
set(TEST_TARGET_NAME ${TARGET_NAME}-test)
set(SOLUTION_LIBRARY_NAME vent-evader)

add_library(${SOLUTION_LIBRARY_NAME}
                vent_evader.cpp            
)

target_include_directories( ${SOLUTION_LIBRARY_NAME} PUBLIC
                            ${CMAKE_SOURCE_DIR}
                            )

target_link_libraries(  ${SOLUTION_LIBRARY_NAME}
                            utils
                     )

add_executable( ${TARGET_NAME}
                    day-5-hydrothermal-venture
                )

target_include_directories( ${TARGET_NAME} PUBLIC
                                ${CMAKE_SOURCE_DIR}
                            )

target_link_libraries(  ${TARGET_NAME}
                            ${SOLUTION_LIBRARY_NAME}
                     )

add_executable(
    ${TEST_TARGET_NAME}
    test.cpp
)
target_link_libraries(
    ${TEST_TARGET_NAME}
    gtest_main
    ${SOLUTION_LIBRARY_NAME}
)
target_include_directories( ${TEST_TARGET_NAME} PUBLIC
                                ${CMAKE_SOURCE_DIR}
                            )
                      
gtest_discover_tests(${TEST_TARGET_NAME})
