cmake_minimum_required(VERSION 3.10)

project(ctg_solver)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES ./*.cpp ./*.h)

add_library(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

