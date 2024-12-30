cmake_minimum_required(VERSION 3.29)
project(consolecalculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(consolecalculator main.cpp
        Calculator.h
        Calculator.cpp
        CalculatorUtils.h
        CalculatorUtils.cpp
        OperationHandler.cpp
        OperationHandler.h
        ParenthesisHandler.cpp
        ParenthesisHandler.h
)
