#include "glad/glad.h"

#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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

  int width, height, nrChannels;
  unsigned char* data = stbi_load("../../../assets/container.jpg", &width, &height, &nrChannels, 0);
  

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  
  
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    zr::log("Texture image couldn't be loaded.", zr::VERBOSITY_LEVEL::ERROR);
  }
  zr::log("Texture loaded successfully.", zr::VERBOSITY_LEVEL::ERROR);

  stbi_image_free(data);

  float vertices[] = {
      0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);

  Shader ourShader ("../texture.vs", "../texture.fs");
  ourShader.use();


  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.9, 1.0, 0.7, 0.4);
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = glfwGetTime();
    ourShader.setFloat("r", sin(timeValue/1.111));
    ourShader.setFloat("g", sin(timeValue/2.0));
    ourShader.setFloat("b", sin(timeValue/3.57));
    
    // as we only have a single VAO there's no need to bind it every time
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &vboID);
  glDeleteBuffers(1, &eboID);
  // glDeleteVertexArrays(1, &vaoID);         //Unsure why this is working (maybe because we only have one VAO)

  glfwTerminate();
  zr::log("Exiting gracefully.");
  return 0;
}
