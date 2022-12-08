cmake_minimum_required(VERSION 3.23)
project(day9)

set(CMAKE_CXX_STANDARD 20)

add_executable(day9 main.cpp)

configure_file(test.txt test.txt COPYONLY)
configure_file(data.txt data.txt COPYONLY)

install(TARGETS day9 RUNTIME DESTINATION bin)