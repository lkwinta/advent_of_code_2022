cmake_minimum_required(VERSION 3.23)
project(day6)

set(CMAKE_CXX_STANDARD 20)

add_executable(day6 main.cpp)

configure_file(test.txt test.txt COPYONLY)
configure_file(data.txt data.txt COPYONLY)

install(TARGETS day6 RUNTIME DESTINATION bin)