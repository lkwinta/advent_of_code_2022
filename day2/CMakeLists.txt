cmake_minimum_required(VERSION 3.23)
project(day2)

set(CMAKE_CXX_STANDARD 20)

add_executable(day2 main.cpp)

configure_file(test.txt test.txt COPYONLY)
configure_file(data.txt data.txt COPYONLY)

install(TARGETS day2 RUNTIME DESTINATION bin)