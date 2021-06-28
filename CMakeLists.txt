cmake_minimum_required(VERSION 3.19)
project(WorkerManager)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)
include_directories(my_tools)

add_executable(WorkerManager
        my_tools/my_tools.cpp
        my_tools/my_tools.h
        Employee.cpp
        Employee.h
        main.cpp
        MainUi.cpp
        MainUi.h
        Worker.cpp
        Worker.h)
