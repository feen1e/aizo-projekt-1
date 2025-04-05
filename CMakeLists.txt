cmake_minimum_required(VERSION 3.30)
project(aizo_projekt)

set(CMAKE_CXX_STANDARD 20)

add_executable(aizo_projekt main.cpp
        insertion_sort.h
        heap_sort.h
        shell_sort.h
        quick_sort.h
        utilities.h
        constants.h
        comparison_generator.cpp
        comparison_generator.h
        main.h
        array_loader.h)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()