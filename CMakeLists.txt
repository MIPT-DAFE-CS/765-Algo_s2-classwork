cmake_minimum_required(VERSION 3.0)
project(765-Algo_s2-classwork)

set(CMAKE_CXX_STANDARD 11)

add_executable(sem2_task2 sem2/task2/main.cpp)
target_include_directories(sem2_task2 PUBLIC sem2/common)

add_executable(sem2_task5 sem2/task5/main.cpp)
target_include_directories(sem2_task5 PUBLIC sem2/common)

add_executable(sem2_task6 sem2/task6/main.cpp)
target_include_directories(sem2_task6 PUBLIC sem2/common)