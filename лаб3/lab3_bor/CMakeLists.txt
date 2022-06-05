cmake_minimum_required(VERSION 3.20)
project(lab3_bor C)

set(CMAKE_C_STANDARD 99)

add_executable(lab3_bor
        main.c
        Bor.h
        header.h
        get_line.c CreateBor.c BorFunctions.c DeleteSpaces.c GetLine.c WorkWithLine.c)
