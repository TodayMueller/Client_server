cmake_minimum_required(VERSION 3.28.1)
project(multithreating LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	src/prog2.h
	src/prog2.cpp
)

add_executable(prog2 ${SOURCES} src/main.cpp)
