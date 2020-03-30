cmake_minimum_required(VERSION 3.15)
project(CSVPrinter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(CSVPrinter main.cpp) 
