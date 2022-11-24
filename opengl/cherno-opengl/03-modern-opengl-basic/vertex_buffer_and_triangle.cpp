#include "GL/glew.h"
// #include <glad/glad.h>                                         // Looks like GLAD is not required when GLEW is used! (Needs Verification)
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

#include <ZR/core.hpp>

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  zr::log_level = zr::VERBOSITY_LEVEL::INFO;
  if (!glfwInit()){
    zr::log("GLFW initialization failed.", zr::VERBOSITY_LEVEL::ERROR);
    return -1;
  }
  zr::log("Successfully initialized GLFW.");

  GLFWwindow *window = glfwCreateWindow(800, 600, "ZR :: Cherno-OpenGL", NULL, NULL);

  if (!window){
      zr::log("Failed to create GLFW window.", zr::VERBOSITY_LEVEL::ERROR);
      glfwTerminate();
      return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);


  zr::log("Successfully created GLFW window.");

  // Initialize GLEW
  GLenum err = glewInit();                      //Must do after glfwMakeContextCurrent() or alternatively after properly initializing GLUT
  if (GLEW_OK != err){
    zr::log("Failed to initialize GLEW. Err: " + std::string((const char*)(glewGetErrorString(err))), zr::VERBOSITY_LEVEL::WARNING);
    glfwTerminate();
    return -1;
  }
  zr::log("Successfully initialized GLEW.");
  zr::log("OpenGL Version: " + std::string((const char*) glGetString(GL_VERSION)));

  // Loading GLAD                                                 // Looks like GLAD is not required when GLEW is used! (Needs Verification)
  // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
  //   zr::log("Failed to initialize GLAD", zr::VERBOSITY_LEVEL::ERROR);
  //   return -1;
  // }
  // zr::log("Successfully initialized GLAD window.");

  glfwMakeContextCurrent(window);
  glClearColor(0.2, 0.2, 0.2, 0.0);

  /* Loop until the user closes the window */
  static bool exit_flag = false;
  while (!exit_flag){
    exit_flag = glfwWindowShouldClose(window);
    processInput(window);
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(0, -1);
    glVertex2f(-1, 0);
    glVertex2f(0, 0);
    glEnd();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    glfwPollEvents();

  }
  glfwTerminate();
  return 0;
}
