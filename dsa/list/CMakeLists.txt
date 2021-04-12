project (zlist)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(list
    src/zlist.cpp
    testList.cpp
)
