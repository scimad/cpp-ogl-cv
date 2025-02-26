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
  zr::log_level = zr::VERBOSITY_LEVEL::DEBUG;
  if (!glfwInit()) {
    zr::log("GLFW initialization failed.", zr::VERBOSITY_LEVEL::ERROR);
    return -1;
  }
  zr::log("Successfully initialized GLFW.", zr::VERBOSITY_LEVEL::DEBUG);

  GLFWwindow *window = glfwCreateWindow(800, 600, "ZR :: OpenGL", NULL, NULL);
  if (window == NULL) {
    zr::log("Failed to create GLFW window.");
    glfwTerminate();
    return -1;
  }
  zr::log("Successfully created GLFW window.", zr::VERBOSITY_LEVEL::DEBUG);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    zr::log("Failed to initialize GLAD");
    return -1;
  }
  zr::log("Successfully initialized GLAD.", zr::VERBOSITY_LEVEL::DEBUG);

  //write the vertex shader in the shader language GLSL (OpenGL Shading Language)
  const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0)\n"
    "in vec3 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\0";

  unsigned int vertexShaderID;
  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShaderID);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE){
    glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
    zr::log ("Vertex shader failed to compile with following error message:", zr::VERBOSITY_LEVEL::ERROR);
    zr::log (infoLog, zr::VERBOSITY_LEVEL::ERROR);
    return -1;
  }
  zr::log ("Vertex shader compiled successfully.", zr::VERBOSITY_LEVEL::DEBUG);

  const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vertexColor;\n"
    "}";

  unsigned int fragmentShaderID;
  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShaderID);

  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE){
    glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
    zr::log ("Fragment shader failed to compile with following error message:", zr::VERBOSITY_LEVEL::ERROR);
    zr::log (infoLog, zr::VERBOSITY_LEVEL::ERROR);
    return -1;
  }
  zr::log ("Fragment shader compiled successfully.", zr::VERBOSITY_LEVEL::DEBUG);

  unsigned int shaderProgramID;
  shaderProgramID = glCreateProgram();

  glAttachShader(shaderProgramID, vertexShaderID);
  glAttachShader(shaderProgramID, fragmentShaderID);
  glLinkProgram(shaderProgramID);
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
      zr::log ("Linking of shaders failed with following error message:", zr::VERBOSITY_LEVEL::ERROR);
      zr::log (infoLog, zr::VERBOSITY_LEVEL::ERROR);
  }
  zr::log ("Shader programs linked successfully.", zr::VERBOSITY_LEVEL::DEBUG);

  float  vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  // Create Vertex Array Object
  // unsigned int vaoID;
  // glGenVertexArrays(1, &vaoID);
  // glBindVertexArray(vaoID);

  // Create Vertex Buffer Object
  unsigned int vboID;
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glUseProgram(shaderProgramID);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.6, 0.7, 0.3, 0.4);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vboID);
  // glDeleteBuffers(1, &vaoID);
  glDeleteProgram(shaderProgramID);

  glfwTerminate();
  return 0;
}
