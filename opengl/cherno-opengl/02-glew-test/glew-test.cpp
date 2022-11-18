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
  if (!glfwInit()) {
    zr::log("GLFW initialization failed.", zr::VERBOSITY_LEVEL::ERROR);
    return -1;
  }
  zr::log("Successfully initialized GLFW.");

  GLFWwindow *window = glfwCreateWindow(800, 600, "ZR :: Cherno-OpenGL", NULL, NULL);
  GLFWwindow *window2 = glfwCreateWindow(600, 800, "ZR :: OpenGL-Cherno", NULL, NULL);

  if (!window || !window2)
  {
      glfwTerminate();
      return -1;
  }
    /* Make the window's context current */
    // glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    static bool exit_flag = false;
    while (!exit_flag)
    {

  if (window == NULL) {
    zr::log("Failed to create GLFW window.", zr::VERBOSITY_LEVEL::ERROR);
    glfwTerminate();
    return -1;
  }
  zr::log("Successfully created GLFW window.");

  glfwMakeContextCurrent(window);

  // Initialize GLEW
  GLenum err = glewInit();                        //Must do after glfwMakeContextCurrent() or alternatively after properly initializing GLUT
  if (GLEW_OK != err)
  {
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


  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    exit_flag = exit_flag || glfwWindowShouldClose(window) || glfwWindowShouldClose(window2);;
    /* Render here */
    glfwMakeContextCurrent(window2);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 1);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glEnd();
    glfwSwapBuffers(window2);
    /* Swap front and back buffers */

    glfwMakeContextCurrent(window);
    /* Render here */
    glClearColor(1.0, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(0, -1);
    glVertex2f(-1, 0);
    glVertex2f(0, 0);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

}
