project (opengl-cherno)
cmake_minimum_required(VERSION 2.8.12)

add_executable(windowing 01-windowing/windowing.cpp)

target_sources(windowing PRIVATE 01-windowing/windowing.cpp ../lib/src/glad.c ../lib/src/ZR/core.cpp)
target_link_libraries(windowing ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} ${CMAKE_DL_LIBS})
