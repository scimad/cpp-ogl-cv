cmake_minimum_required(VERSION 3.18)
project(getting-started-opengl LANGUAGES C CXX)

add_executable(getting-started)
include_directories(include)

find_package(PkgConfig REQUIRED)

find_package(OpenGL REQUIRED)
pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
if(${glfw3_FOUND})
    MESSAGE("[ZR]: PKGCOFIG = " ${PKG_CONFIG_EXECUTABLE})
    MESSAGE("[ZR]: GLFW3 libraries = " ${glfw3_LIBRARIES})
    MESSAGE("[ZR]: GLFW3 link libraries = " ${glfw3_LINK_LIBRARIES})
endif()

include_directories( ${OPENGL_INCLUDE_DIRS}  ${glfw3_INCLUDE_DIRS})
target_sources(getting-started PRIVATE main.cpp src/glad.c)
target_link_libraries(getting-started ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} ${CMAKE_DL_LIBS})
