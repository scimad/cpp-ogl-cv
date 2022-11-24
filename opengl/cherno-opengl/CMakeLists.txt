project (opengl-cherno)
cmake_minimum_required(VERSION 2.8.12)

# link_directories (../lib/libstatic/)											#TODO: Need to add project lib instead of system library

# For some reason cmake is not taking libraries from our project but taking from system. That needs fix but we will continue like this For
# now.


add_executable(windowing 01-windowing/windowing.cpp)
add_executable(glew-test 02-glew-test/glew-test.cpp)
add_executable(hello_world 03-modern-opengl-basic/hello_world.cpp)
add_executable(vertex-buffer 03-modern-opengl-basic/vertex_buffer_and_triangle.cpp)


target_sources(windowing PRIVATE 01-windowing/windowing.cpp ../lib/src/glad.c ../lib/src/ZR/core.cpp)
target_link_libraries(windowing ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} ${CMAKE_DL_LIBS})

target_sources(glew-test PRIVATE 02-glew-test/glew-test.cpp ../lib/src/glad.c ../lib/src/ZR/core.cpp)
target_link_libraries(glew-test ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} GLEW ${CMAKE_DL_LIBS})                  # ${GLEW_LINK_LIBRARIES}

target_sources(vertex-buffer PRIVATE 03-modern-opengl-basic/vertex_buffer_and_triangle.cpp ../lib/src/glad.c ../lib/src/ZR/core.cpp)
target_link_libraries(vertex-buffer ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} GLEW ${CMAKE_DL_LIBS})                  # ${GLEW_LINK_LIBRARIES}

target_sources(hello_world PRIVATE 03-modern-opengl-basic/hello_world.cpp ../lib/src/glad.c ../lib/src/ZR/core.cpp)
target_link_libraries(hello_world ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} GLEW ${CMAKE_DL_LIBS})                  # ${GLEW_LINK_LIBRARIES}
