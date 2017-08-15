cmake_minimum_required(VERSION 3.7)
project(1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c L_Utility.c L_Utility.h L_Grafo.c L_Grafo.h)
add_executable(1 ${SOURCE_FILES})