cmake_minimum_required(VERSION 3.01)

include_directories(./)

set(Files ./XTest.hpp Test.h Print.h Run.h)

add_executable(test-assert tests/test-assert.cpp ${Files})

add_executable(test-benchmark tests/test-benchmark.cpp ${Files})