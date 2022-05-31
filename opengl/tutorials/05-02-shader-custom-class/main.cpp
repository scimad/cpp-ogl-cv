#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <math.h>
#include <ZR/core.hpp>
#include "shader.hpp"


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

  Shader ourShader ("../shader.vs", "../shader.fs");

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.9, 1.0, 0.7, 0.4);
    glClear(GL_COLOR_BUFFER_BIT);
    ourShader.use();
  
    float timeValue = glfwGetTime();
    ourShader.setFloat("redColor", sin(timeValue/1.111));
    ourShader.setFloat("greenColor", sin(timeValue/2.0));
    ourShader.setFloat("blueColor", sin(timeValue/3.57));
    
    // as we only have a single VAO there's no need to bind it every time
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &vboID);
  glDeleteVertexArrays(1, &eboID);
  // glDeleteBuffers(1, &vaoID);              //Unsure why this is working (maybe because we only have one VAO)

  glfwTerminate();
  zr::log("Exiting gracefully.");
  return 0;
}
