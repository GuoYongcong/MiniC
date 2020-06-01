cmake_minimum_required(VERSION 3.14)
project(MiniC_ C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(MiniC_
        globals.h
        lex.yy.c
        utils.c
        utils.h
        yacc.tab.c
        yacc.tab.h)
