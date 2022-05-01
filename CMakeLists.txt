cmake_minimum_required(VERSION 3.10)
set (CMAKE_C_COMPILER "/usr/bin/gcc")
set (CMAKE_CXX_COMPILER "/usr/bin/g++")
add_compile_options( -fpermissive -g -std=c++17)
project(OUTPUT VERSION 1.0)
aux_source_directory(${PROJECT_SOURCE_DIR}/ DIR_SRCS)
add_executable(run ${DIR_SRCS})
target_include_directories(run PUBLIC 
                "${PROJECT_SOURCE_DIR}"
                            )

