cmake_minimum_required(VERSION 3.10)


project(bitset)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c bitset/src/bit_array.c bitset/tests/test.c)
target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(${PROJECT_NAME} PRIVATE -lgcov)