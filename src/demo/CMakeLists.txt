

add_executable(first_program src/first_program.cpp)
add_executable(array_size src/array_size.cpp)
add_executable(default_constructor src/default_constructor.cpp)
add_executable(reference_demo src/reference_demo.cpp)
add_executable(inheritance_1 src/inheritance_1.cpp)
add_executable(concepts_example_1 src/concepts_example_1.cpp)


add_executable(cuda_execution_model
        src/cuda_execution_model.cpp
        src/gpu_model.cpp)


add_executable(demo_spdlog src/demo_spdlog.cpp)
target_link_libraries(demo_spdlog PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
