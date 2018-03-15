cmake_minimum_required(VERSION 3.0)
project(765-Algo_s2-classwork)

set(CMAKE_CXX_STANDARD 11)

add_executable(sem2_assignment1_task2 sem2/assignment1/task2/main.cpp)
target_include_directories(sem2_assignment1_task2 PUBLIC sem2/common)

add_executable(sem2_assignment1_task3 sem2/assignment1/task3/main.cpp)
target_include_directories(sem2_assignment1_task3 PUBLIC sem3/common)

add_executable(sem2_assignment1_task4 sem2/assignment1/task4/main.cpp)
target_include_directories(sem2_assignment1_task4 PUBLIC sem3/common)

add_executable(sem2_assignment1_task5 sem2/assignment1/task5/main.cpp)
target_include_directories(sem2_assignment1_task5 PUBLIC sem2/common)

add_executable(sem2_assignment1_task6 sem2/assignment1/task6/main.cpp)
target_include_directories(sem2_assignment1_task6 PUBLIC sem2/common)

add_executable(sem2_assignment2_task1 sem2/assignment2/task1/main.cpp)