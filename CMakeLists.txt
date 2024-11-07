cmake_minimum_required(VERSION 3.6)

project (Path_Finding_Algorithm_For_RTS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)

add_executable(Output src/main.cpp src/Astar.cpp)
