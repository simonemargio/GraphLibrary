cmake_minimum_required(VERSION 3.7)
project(1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c L_Utility.c L_Utility.h cmake-build-debug/L_Grafo.c cmake-build-debug/L_Grafo.h)
add_executable(1 ${SOURCE_FILES})