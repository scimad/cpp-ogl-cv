#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <fmt/core.h>
#include <iostream>

#include <ZR/core.hpp>

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width, height);
    zr::log("Succesfully changed viewport.");
    zr::log(fmt::format("New viewport size is {}X{}", width, height));
};

int main(){
    if(!glfwInit()){
        zr::log("GLFW initialization failed.");
        return -1;
    }
    zr::log("Successfully initialized GLFW.");


    GLFWwindow* window = glfwCreateWindow(800, 600, "ZR :: OpenGL", NULL, NULL);
    if (window == NULL){
        zr::log("Failed to create GLFW window.");
        glfwTerminate();
        return -1;
    }
    zr::log("Successfully created GLFW window.");

    glfwMakeContextCurrent( window );
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        zr::log("Failed to initialize GLAD");
        return -1;
    }
    zr::log("Successfully initialized GLAD window.");

    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    while (!glfwWindowShouldClose(window)){
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
