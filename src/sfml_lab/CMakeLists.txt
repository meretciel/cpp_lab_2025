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
add_executable(sfml_example_2 sfml_example_2_window_and_keypress.cpp)

#target_link_libraries(sfml_example_1 PRIVATE SFML::Graphics SFML::Audio SFML::Network)
#target_include_directories(sfml_example_1 PRIVATE ${INCLUDE_DIRECTORIES})
#
#target_link_libraries(sfml_example_2 PRIVATE SFML::Graphics SFML::Audio SFML::Network)
#target_include_directories(sfml_example_2 PRIVATE ${INCLUDE_DIRECTORIES})


set(_SFML_LAB_EXEC_LIST
    sfml_example_1
    sfml_example_2
)

foreach(element IN LISTS _SFML_LAB_EXEC_LIST)
    target_link_libraries(${element} PRIVATE SFML::Graphics SFML::Audio SFML::Network)
    target_include_directories(${element} PRIVATE ${INCLUDE_DIRECTORIES})
endforeach()






