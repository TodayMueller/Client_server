cmake_minimum_required(VERSION 3.28.1)
project(multithreating LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	src/prog1.h
	src/prog1.cpp
)

add_executable(prog1 ${SOURCES} src/main.cpp)
