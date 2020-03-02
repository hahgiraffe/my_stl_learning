cmake_minimum_required(VERSION 2.7)
project(MINISTL)

#设置版本号，编译器，可执行文件路径
set(MINISTL_VERSION 0.1)
set(CMAKE_C_COMPILER g++)
set(EXECUTABLE_OUTPUT_PATH ../build/bin)
set(LIBRARY_OUTPUT_PATH ../lib)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -g -ggdb -Wall -std=c++11)

# 设置jemalloc
set(JEMALLOC_INCLUDE_DIR /usr/local/jemalloc/include/jemalloc)
set(JEMALLOC_LIB /usr/local/jemalloc/lib)
include_directories(${JEMALLOC_INCLUDE_DIR})
link_directories(${JEMALLOC_LIB})

# 添加静态库和动态库
set(libhahatest ./hahatest/hahatest.cc)
add_library(hahatest_shared SHARED ${libhahatest})
add_library(hahatest_static STATIC ${libhahatest})

# Allocator测试
add_executable(Allocatortest ./hahatest/hahatest.cc ./test/AllocatorTest.cpp)
target_link_libraries(Allocatortest pthread jemalloc)

# SequnceContainer测试
add_executable(SequenceContainertest ./hahatest/hahatest.cc ./test/SequenceContainerTest.cpp)
target_link_libraries(SequenceContainertest pthread)

# AssociativeContainer测试
add_executable(AssociativeContainertest ./hahatest/hahatest.cc ./test/AssociativeContainerTest.cpp)
target_link_libraries(AssociativeContainertest pthread)

# Algorithm测试
add_executable(Algorithmtest ./hahatest/hahatest.cc ./test/AlgorithmTest.cpp)
target_link_libraries(Algorithmtest pthread)

# ThreadSafe测试
add_executable(ThreadSafeTest ./hahatest/hahatest.cc ./test/ThreadSafeTest.cpp)
target_link_libraries(ThreadSafeTest pthread)