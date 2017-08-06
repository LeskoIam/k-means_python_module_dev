cmake_minimum_required(VERSION 3.8)
project(k_means_python_module_dev)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/main.h
        src/utils.c
#        test.c
#        example.c
        )

add_executable(k_means_python_module_dev ${SOURCE_FILES})