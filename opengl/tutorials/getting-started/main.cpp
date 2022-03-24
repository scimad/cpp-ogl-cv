#include <glad/glad.h>

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

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
