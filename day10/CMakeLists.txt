cmake_minimum_required(VERSION 3.22)
project(day10)

set(CMAKE_CXX_STANDARD 20)

add_executable(day10 main.cpp)

configure_file(test.txt test.txt COPYONLY)
configure_file(data.txt data.txt COPYONLY)

install(TARGETS day10 RUNTIME DESTINATION bin)