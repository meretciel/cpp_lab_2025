cmake_minimum_required(VERSION 3.22)
project(build_time_cmd_demo)

message(">>> Enter project dif: ${PROJECT_SOURCE_DIR}")

add_custom_target(generate_header
        COMMAND python3 build-time-script/generate_header.py
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_executable(build_time_cmd_demo build-time-command-demo.cpp)
target_include_directories(build_time_cmd_demo PRIVATE include)
add_dependencies(build_time_cmd_demo generate_header)

message("<<< Exit project dif: ${PROJECT_SOURCE_DIR}")