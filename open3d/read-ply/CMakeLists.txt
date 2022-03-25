cmake_minimum_required(VERSION 3.18)
project(read-ply LANGUAGES C CXX)

# Find installed Open3D, which exports Open3D::Open3D
find_package(Open3D REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(read-ply)
target_sources(read-ply PRIVATE main.cpp)
target_link_libraries(read-ply PRIVATE Open3D::Open3D Eigen3::Eigen)