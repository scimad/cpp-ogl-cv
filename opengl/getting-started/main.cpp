#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main(){
    if(!glfwInit()){
        std::cout << "GLFW initialization failed." << std::endl;
        return -1;
    }
    std::cout << "Successfully initialized GLFW." << std::endl;


    GLFWwindow* window = glfwCreateWindow(800, 600, "ZR :: OpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Successfully created GLFW window." << std::endl;

    glfwMakeContextCurrent( window );
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "Successfully initialized GLAD window." << std::endl;

    while (!glfwWindowShouldClose(window)){
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    return 0;
}
