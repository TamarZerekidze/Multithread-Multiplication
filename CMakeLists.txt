cmake_minimum_required(VERSION 3.29)
project(Multithread_Multiplication)

set(CMAKE_CXX_STANDARD 23)
include_directories(sqlite)
add_compile_definitions(SQLITE_THREADSAFE=1)

add_executable(Multithread_Multiplication sqlite/sqlite3.h sqlite/sqlite3.c
        src/Coordinator.cpp
        src/Coordinator.h
        src/StatsDAO.h
        src/StatsDAO.cpp
        src/Stat.h
        src/Stat.cpp
        src/DatabaseConnection.cpp
        src/Karatsuba.cpp
        src/Karatsuba.h)
