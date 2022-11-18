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
