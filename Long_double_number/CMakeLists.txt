cmake_minimum_required(VERSION 3.26)
project(Long_double_number)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(SOURCE_EXE class_lib/Double.cpp class_lib/Double.h method.cpp Source.cpp)

add_executable(Source ${SOURCE_EXE})
