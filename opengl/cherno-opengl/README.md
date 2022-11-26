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

