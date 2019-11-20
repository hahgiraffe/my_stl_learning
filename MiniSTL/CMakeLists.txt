cmake_minimum_required(VERSION 2.7)
project(MINISTL)

#设置版本号，编译器，可执行文件路径
set(MINISTL_VERSION 0.1)
set(CMAKE_C_COMPILER g++)
set(EXECUTABLE_OUTPUT_PATH ../build/bin)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -g -ggdb -Wall -std=c++11)

# 设置jemalloc
set(JEMALLOC_INCLUDE_DIR /usr/local/jemalloc/include/jemalloc)
set(JEMALLOC_LIB /usr/local/jemalloc/lib)
include_directories(${JEMALLOC_INCLUDE_DIR})
link_directories(${JEMALLOC_LIB})

add_executable(runUnitTests ./test/AllocatorTest.cpp)
target_link_libraries(runUnitTests gtest pthread jemalloc)