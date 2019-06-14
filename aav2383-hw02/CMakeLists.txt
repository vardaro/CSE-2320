cmake_minimum_required(VERSION 3.14)
project(aav2383_hw02 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS "-no-pie")



add_executable(aav2383_hw02 hw02.c hw02-lib.h hw02-lib.o)