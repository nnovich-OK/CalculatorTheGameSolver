#TODO test with older versions
#TODO test under linux
cmake_minimum_required(VERSION 3.10)

# unit test library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(3rd_party/googletest)

# main project
add_subdirectory(src)

# launcher
add_subdirectory(launcher)

# unit test project
add_subdirectory(tests)

