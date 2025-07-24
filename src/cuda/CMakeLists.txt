cmake_minimum_required(VERSION 3.18)
project(first_cuda LANGUAGES CXX CUDA C)
set(CMAKE_CUDA_ARCHITECTURES 75)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)

#find_package(CUDA REQUIRED)

add_executable(hello_world src/hello_world.cu)
set_target_properties(hello_world PROPERTIES
        CUDA_STANDARD 17
        CUDA_STANDARD_REQUIRED ON
)



add_executable(sum_vector src/sum_vector.cu)
set_target_properties(sum_vector PROPERTIES
        CUDA_STANDARD 17
        CUDA_STANDARD_REQUIRED ON
)

