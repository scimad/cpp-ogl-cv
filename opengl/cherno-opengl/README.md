# OpenGL-Cherno Youtube Series

* GLFW : GLFW is a lightweight utility library for use with OpenGL. It provides programmers with the ability to create and manage windows and OpenGL contexts, as well as handle joystick, keyboard and mouse input. (Credit to Wikipedia)

* GLEW :

## Modern OpenGL

* Modern OpenGL uses Vertex Buffer and Shaders to work
* Vertex Buffer: Is simply memory space / buffer, array of bytes. (Inside GPU i.e. Video RAM (VRAM))
* Shader is a program that runs on the GPU.
* OpenGL runs as a state machine and hence the meaning of any command / function might depend on the context (because of the current state.)


## Shaders
* A program that runs on GPU
* Vertex shader is run for each vertices (where, each vertex may contain its position, color, normal and other attributes.)
* Fragment shader is run for each pixels.

## Uniforms
* Ways to move data from CPU to GPU.
* Uniforms are set 'per draw call'.

# Using Vertex Array
* The information about the layout (or attributes) of currently bind vertex data/buffer (via vertex buffer object) is stored using a vertex 
array mechanism. So, if we need to use a different layout, then we need to specify a different vertex buffer object.
* Binding the vertex array is equivalent to *binding the vertex buffer + setting out the layout*.
* Usually one VAO is used for one piece of geometry.
* Updating the vertex array is done 'per draw call' in general.
* Typical workflow without using vertex array and vaos:
    * Bind the shaders
    * Bind the vertex buffers
    * Specify the layouts of vertex buffers
    * Bind the index buffers
    * Issue the draw call
* Typical workflow using vertex array looks like:
    * Bind the shaders
    * Bind the vertex arrays
    * Bind the index buffers
    * Issue the draw call
* A vertex array object is created by default (so, a default VAO is bind to the current state.)in compatibility profile in OpenGL but not in
 core profile.
 