cmake_minimum_required(VERSION 3.13)
project(INHA_ParallelProgramming_002)

set(CMAKE_CXX_FLAGS "-O2 -std=c++11")

add_executable(INHA_ParallelProgramming_002
        HW1/matmul_avx.cpp)