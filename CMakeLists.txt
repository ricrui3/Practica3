cmake_minimum_required(VERSION 3.2)
project(Practica3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp AFN.hpp AFD.txt AFD.txt Makefile)
add_executable(Practica3 ${SOURCE_FILES})