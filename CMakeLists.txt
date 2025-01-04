cmake_minimum_required(VERSION 3.29)
project(consolecalculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(consolecalculator main.cpp
        Calculator.h
        Calculator.cpp
        calculator_utils.h
        calculator_utils.cpp
        operation_handler.cpp
        operation_handler.h
        parenthesis_handler.cpp
        parenthesis_handler.h
)
