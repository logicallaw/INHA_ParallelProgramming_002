cmake_minimum_required(VERSION 3.13)
project(INHA_ParallelProgramming_002)

set(CMAKE_CXX_FLAGS "-O2 -std=c++11")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    include_directories(/opt/homebrew/opt/libomp/include)
    link_directories(/opt/homebrew/opt/libomp/lib)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xpreprocessor -fopenmp -lomp")
endif()

add_executable(INHA_ParallelProgramming_002 main.cpp)