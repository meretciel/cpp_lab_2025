cmake_minimum_required(VERSION 3.22)
project(cpplab LANGUAGES CXX CUDA C)

#set(CMAKE_CXX_COMPILER "/usr/bin/clang++-15")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#include_directories(SYSTEM /usr/include/c++/11)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)


if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED
            PATHS /home/ryan/workspace/cpp_projects/third_party/install
    )
endif()



message("Top level source dir: ${CMAKE_SOURCE_DIR}")
message("Current project dif: ${PROJECT_SOURCE_DIR}")
add_subdirectory(src/build_time_cmd_demo)
add_subdirectory(src/cpp_language)
add_subdirectory(src/demo)
add_subdirectory(src/cuda)
add_subdirectory(src/imgui)

add_executable(graph_dfs src/graph_dfs.cpp)
add_executable(concept-demo src/concept-demo.cpp)



