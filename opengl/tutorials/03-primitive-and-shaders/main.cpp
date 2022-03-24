#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <ZR/core.hpp>


void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  if (!glfwInit()) {
    zr::log("GLFW initialization failed.");
    return -1;
  }
  zr::log("Successfully initialized GLFW.");

  GLFWwindow *window = glfwCreateWindow(800, 600, "ZR :: OpenGL", NULL, NULL);
  if (window == NULL) {
    zr::log("Failed to create GLFW window.");
    glfwTerminate();
    return -1;
  }
  zr::log("Successfully created GLFW window.");

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    zr::log("Failed to initialize GLAD");
    return -1;
  }
  zr::log("Successfully initialized GLAD window.");

  float  vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  // Create Vertex Buffer Object
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  //write the vertex shader in the shader language GLSL (OpenGL Shading Language)
  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
