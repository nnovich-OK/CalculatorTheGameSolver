#TODO test with older versions
cmake_minimum_required(VERSION 3.10)

project(solver)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})
