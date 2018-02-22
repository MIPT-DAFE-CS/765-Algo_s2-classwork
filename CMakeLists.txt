cmake_minimum_required(VERSION 3.0)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(sem2_task2 sem2/task2/main.cpp sem2/common/CListGraph.h sem2/common/IGraph.h)
target_include_directories(sem2_task2 PUBLIC sem2/common)