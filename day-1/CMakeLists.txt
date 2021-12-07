add_executable( day-1 
                    day-1-sonar-sweep.cpp
                )

target_include_directories( day-1 PUBLIC
                                ${CMAKE_SOURCE_DIR}
                            )

target_link_libraries(  day-1
                            utils
                     )