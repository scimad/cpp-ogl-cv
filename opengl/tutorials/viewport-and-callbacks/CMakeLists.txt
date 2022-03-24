cmake_minimum_required(VERSION 3.18)
project(opengl-practice LANGUAGES C CXX)

add_executable(viewport)
include_directories(include)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
if(${glfw3_FOUND})
    MESSAGE("[ZR]: PKGCOFIG = " ${PKG_CONFIG_EXECUTABLE})
    MESSAGE("[ZR]: GLFW3 libraries = " ${glfw3_LIBRARIES})
    MESSAGE("[ZR]: GLFW3 link libraries = " ${glfw3_LINK_LIBRARIES})
endif()

find_package(fmt )
set(fmt_FOUND TRUE)
# MESSAGE("[ZR]: fmt libraries = " ${fmt_LINK_LIBRARIES})
# MESSAGE("[ZR]: fmt libraries = " ${fmt_INCLUDE_DIRS})

include_directories( ${OPENGL_INCLUDE_DIRS}  ${glfw3_INCLUDE_DIRS} ${fmt_INCLUDE_DIRS})
target_sources(viewport PRIVATE main.cpp src/glad.c)
target_link_libraries(viewport ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} ${CMAKE_DL_LIBS} fmt::fmt)

