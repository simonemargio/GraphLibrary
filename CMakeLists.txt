cmake_minimum_required(VERSION 3.8)
project(5__Esercizio_5___Grafi)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        L_Coda.c
        L_Coda.h
        L_Grafo.c
        L_Grafo.h
        L_Stack.c
        L_Stack.h
        L_Utility.c
        L_Utility.h
        main.c)

add_executable(5__Esercizio_5___Grafi ${SOURCE_FILES})