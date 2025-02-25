cmake_minimum_required(VERSION 3.16)
project(OpenGL-Abstraction LANGUAGES C CXX)

add_executable(abstraction)
find_package(PkgConfig REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)

if(${OpenGL_FOUND})
    MESSAGE("[ZR]: OpenGL included at ${OPENGL_INCLUDE_DIR}")
    MESSAGE("[ZR]: OPENGL libraries = " ${OPENGL_LIBRARIES})
endif()

pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
if(${glfw3_FOUND})
    MESSAGE("[ZR]: PKGCOFIG = " ${PKG_CONFIG_EXECUTABLE})
    MESSAGE("[ZR]: GLFW3 libraries = " ${glfw3_LIBRARIES})
    MESSAGE("[ZR]: GLFW3 link libraries = " ${glfw3_LINK_LIBRARIES})
endif()

include_directories( ../../lib/include ${OPENGL_INCLUDE_DIRS}  ${glfw3_INCLUDE_DIRS})                                 # ${GLEW_INCLUDE_DIRS}
target_sources(abstraction PRIVATE  main.cpp 
    src/renderer.cpp
    src/vertex_buffer.cpp
    src/index_buffer.cpp
    ../../lib/src/glad.c
    ../../lib/src/ZR/core.cpp
    src/vertex_array.cpp
    src/vertex_buffer_layout.cpp
    src/shader.cpp
    src/texture.cpp
)
target_link_libraries(abstraction ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} GLEW ${CMAKE_DL_LIBS})                # ${GLEW_LINK_LIBRARIES}
