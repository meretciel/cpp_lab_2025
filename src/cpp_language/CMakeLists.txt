cmake_minimum_required(VERSION 3.22)
project(cpp_language)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)


add_executable(shared_pointer src/shared_pointer.cpp)


# Setup Tests
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)


add_executable(hello_test test/test1.cpp)
target_link_libraries(hello_test GTest::gtest_main)
gtest_discover_tests(hello_test)