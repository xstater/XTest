cmake_minimum_required(VERSION 3.01)

include_directories(./)

set(Files ./XTest.hpp)

add_executable(test ./test.cpp ${Files})