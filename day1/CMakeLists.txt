cmake_minimum_required(VERSION 3.23)
project(day1)

set(CMAKE_CXX_STANDARD 20)

add_executable(day1 main.cpp)

configure_file(test.txt test.txt COPYONLY)
configure_file(data.txt data.txt COPYONLY)

install(TARGETS day1 RUNTIME DESTINATION bin)