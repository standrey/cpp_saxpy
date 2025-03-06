cmake_minimum_required(VERSION 3.28)

project(vectorsum VERSION 1.0 LANGUAGES CXX)

set(TARGET_NAME vectorsum)

add_executable(${TARGET_NAME} src/sse.cpp)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)



