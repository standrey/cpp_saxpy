cmake_minimum_required(VERSION 3.28)

project(vectorsum VERSION 1.0 LANGUAGES CXX)

set(TARGET_NAME vectorsum)

add_executable(${TARGET_NAME} src/sum_test.cpp src/main.cpp src/vectorsum.cpp src/cpp_allocator_test.cpp)

target_include_directories(${TARGET_NAME} PRIVATE include)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)



