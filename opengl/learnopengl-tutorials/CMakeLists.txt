project (opengl-learnopengl)
cmake_minimum_required(VERSION 2.8.12)


add_executable(colors-basic 10-colors-basics/main.cpp)

target_sources(colors-basic PRIVATE 10-colors-basics/main.cpp ../lib/src/glad.c ../lib/src/ZR/core.cpp)
target_link_libraries(colors-basic ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} ${CMAKE_DL_LIBS})
