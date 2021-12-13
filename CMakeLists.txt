cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

project(advent-of-code-2021)

# Make Googletest available to the project
include (FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_subdirectory(utils)
add_subdirectory(day-1)
add_subdirectory(day-2)
add_subdirectory(day-3)