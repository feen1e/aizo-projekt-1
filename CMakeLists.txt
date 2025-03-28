cmake_minimum_required(VERSION 3.30)
project(aizo_projekt)

set(CMAKE_CXX_STANDARD 20)

add_executable(aizo_projekt main.cpp
        insertion_sort.cpp
        insertion_sort.h
        heap_sort.cpp
        heap_sort.h
        shell_sort.cpp
        shell_sort.h
        quick_sort.cpp
        quick_sort.h
        utilities.cpp
        utilities.h
        constants.h
        comparison_generator.cpp
        comparison_generator.h
        main.h
        array_loader.cpp
        array_loader.h)
