cmake_minimum_required(VERSION 3.10)

project(tests)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES ./*.cpp ./*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

# TODO include project root directory in a more elegant way
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
    ../src
)

target_link_libraries(${PROJECT_NAME} gtest gmock_main ctg_solver)

add_test(NAME ctg_solver_test COMMAND ${PROJECT_NAME})