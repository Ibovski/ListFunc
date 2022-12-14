cmake_minimum_required(VERSION 3.20)
project(ListFunc)

set(CMAKE_CXX_STANDARD 14)

add_executable(ListFunc main.cpp mainFunctions.h parameter.h customFunction.h mainFunctions.cpp parameter.cpp customFunction.cpp functionExecute.h functionExecute.cpp mathFunctions.h mathFunctions.cpp)
