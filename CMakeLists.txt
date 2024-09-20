cmake_minimum_required(VERSION 3.29)
project(Multithread_Multiplication)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Multithread_Multiplication
    Coordinator.cpp
    Coordinator.h
        StatsDAO.h
        StatsDAO.cpp
        Stat.h
        Stat.cpp)
