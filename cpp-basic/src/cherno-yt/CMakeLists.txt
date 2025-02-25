project (cpp-basic)
cmake_minimum_required(VERSION 2.8.12)

add_executable(lambdas lambdas/lambdas_demo.cpp)
add_executable(overload1 operators/overloading_1.cpp)
add_executable(overload2 operators/overloading_2.cpp)
add_executable(scoped-ptr scoped-ptr/scoped_ptr.cpp)
add_executable(any-size-array static-arrays/loop-anysize-array.cpp)
add_executable(smart-ptr smart-pointers/shared-unique-weak.cpp)
add_executable(static-cast casting/casting-example.cpp)
add_executable(dynamic-cast casting/dynamic-casting.cpp)
add_executable(dynamic-cast-2 casting/dynamic-another.cpp)
add_executable(new-delete custom-alloc/new-delete.cpp)
add_executable(custom-string custom-strings/basic.cpp)


# set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(multithreading multithreading/file-copy.cpp)
target_link_libraries(multithreading Threads::Threads )
target_compile_features(multithreading PRIVATE cxx_std_17)          #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(string-view string_view/string_view.cpp)
target_compile_features(string-view PRIVATE cxx_std_17)          #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(custom-array custom-arrays/arrays.cpp)
add_executable(dynamic-array dynamic-arrays/basic.cpp)
target_compile_features(dynamic-array PRIVATE cxx_std_17)

add_executable(iterators iterators/basic.cpp)
target_compile_features(iterators PRIVATE cxx_std_17)

add_executable(custom-iterators iterators/custom-iterators.cpp)
