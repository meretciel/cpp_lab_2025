cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(NOT TARGET SFML)
    set(SFML_STATIC_LIBRARIES TRUE)

    find_package(SFML 3 COMPONENTS Graphics Audio Network REQUIRED
            PATHS /home/ryan/workspace/cpp_projects/third_party/install)
endif()


set(INCLUDE_DIRECTORIES "/home/ryan/workspace/cpp_projects/third_party/install/include")


add_executable(sfml_example_1 sfml_example_1.cpp)
target_link_libraries(sfml_example_1 PRIVATE SFML::Graphics SFML::Audio SFML::Network)
target_include_directories(sfml_example_1 PRIVATE ${INCLUDE_DIRECTORIES})
