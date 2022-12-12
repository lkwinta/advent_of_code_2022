cmake_minimum_required(VERSION 3.22)
project(day8)

set(CMAKE_CXX_STANDARD 20)

add_executable(day8 main.cpp)

configure_file(test.txt test.txt COPYONLY)
configure_file(data.txt data.txt COPYONLY)

install(TARGETS day8 RUNTIME DESTINATION bin)