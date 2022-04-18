cmake_minimum_required(VERSION 3.18)
project(open3d-basics LANGUAGES C CXX)

# Find installed Open3D, which exports Open3D::Open3D
find_package(Open3D REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(getting-started)
target_sources(getting-started PRIVATE main.cpp)
target_link_libraries(getting-started PRIVATE Open3D::Open3D Eigen3::Eigen)
