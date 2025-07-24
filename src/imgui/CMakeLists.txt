cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(imgui
  imgui.cpp
  imgui_draw.cpp
  imgui_tables.cpp
  imgui_widgets.cpp
  imgui_demo.cpp
  backends/imgui_impl_glfw.cpp
  backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)


add_executable(example_sdl3_opengl3 examples/example_glfw_opengl3/main.cpp)
target_link_libraries(example_sdl3_opengl3 imgui)
