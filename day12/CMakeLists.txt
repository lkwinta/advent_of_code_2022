cmake_minimum_required(VERSION 3.22)
project(day9)

set(CMAKE_CXX_STANDARD 20)

add_executable(day12 main.cpp)

configure_file(test.txt test.txt COPYONLY)
configure_file(data.txt data.txt COPYONLY)

install(TARGETS day12 RUNTIME DESTINATION bin)