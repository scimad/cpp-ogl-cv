project (cpp-basic)
cmake_minimum_required(VERSION 2.8.12)

add_executable(lambdas lambdas/lambdas_demo.cpp)
add_executable(overload1 operators/overloading_1.cpp)
add_executable(overload2 operators/overloading_2.cpp)
add_executable(scoped-ptr scoped-ptr/scoped_ptr.cpp)
add_executable(any-size-array static-arrays/loop-anysize-array.cpp)
add_executable(smart-ptr smart-pointers/shared-unique-weak.cpp)
