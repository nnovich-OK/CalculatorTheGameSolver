cmake_minimum_required(VERSION 3.10)

project(launcher)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES ./*.cpp ./*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ctg_solver)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

