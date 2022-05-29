#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <math.h>
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

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  zr::log("Max. nr of vertex attributes supported: " + std::to_string(nrAttributes));


  //write the vertex shader in the shader language GLSL (OpenGL Shading Language)
  const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
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
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(ourColor, 1.0);\n"
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

  float vertices[] = {
      0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
      -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f   // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };

  // Create Vertex Array Object
  // unsigned int vaoID;
  // glGenVertexArrays(1, &vaoID);
  // glBindVertexArray(vaoID);

  //Create Vertex Buffer Object
  unsigned int vboID;
  glGenBuffers(1, &vboID);

  // Create Element Buffer Object
  unsigned int eboID;
  glGenBuffers(1, &eboID);

  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glUseProgram(shaderProgramID);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.9, 1.0, 0.7, 0.4);
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue)/2.0f) + 0.5;
    int vertexColorLocation = glGetUniformLocation(shaderProgramID, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // as we only have a single VAO there's no need to bind it every time
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &eboID);
  // glDeleteBuffers(1, &vaoID);
  glDeleteProgram(shaderProgramID);

  glfwTerminate();
  zr::log("Exiting gracefully.");
  return 0;
}
