set(TARGET_NAME day-2)

add_executable( ${TARGET_NAME}
                    day-2-dive.cpp
                )

target_include_directories( ${TARGET_NAME} PUBLIC
                                ${CMAKE_SOURCE_DIR}
                            )

target_link_libraries(  ${TARGET_NAME}
                            utils
                     )