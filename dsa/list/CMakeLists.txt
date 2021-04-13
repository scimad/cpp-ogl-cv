project (zlist)
cmake_minimum_required(VERSION 3.0)

include_directories("include")
add_subdirectory("src")

add_executable(testlist testList.cpp)
target_link_libraries(testlist zlist)
