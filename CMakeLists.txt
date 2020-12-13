cmake_minimum_required(VERSION 3.17)
project(InterpreterExperiment C)

set(CMAKE_C_STANDARD 99)

add_executable(InterpreterExperiment main.c formal.c stream.c jit.c new.c)