project (opengl)
cmake_minimum_required(VERSION 2.8.12)

include_directories(include)

find_package(PkgConfig REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
if(${glfw3_FOUND})
    MESSAGE("[ZR]: PKGCOFIG = " ${PKG_CONFIG_EXECUTABLE})
    MESSAGE("[ZR]: GLFW3 libraries = " ${glfw3_LIBRARIES})
    MESSAGE("[ZR]: GLFW3 link libraries = " ${glfw3_LINK_LIBRARIES})
endif()

include_directories( ./lib/include ${OPENGL_INCLUDE_DIRS}  ${glfw3_INCLUDE_DIRS})

add_subdirectory(cherno-opengl)
add_subdirectory(learnopengl-tutorials)

