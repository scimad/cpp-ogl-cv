#include "glad/glad.h"

#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <math.h>
#include <ZR/core.hpp>
#include "shader.hpp"


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 projection = glm::mat4(1.0f);

glm::vec3 direction;
float yaw, pitch, roll;
float fov;

//Mouse stuffs
float lastX = 400, lastY = 300;
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
  lastX = xpos;
  lastY = ypos;

  const float sensitivity = 0.05f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw   += xoffset;
  pitch += yoffset;

  if(pitch > 89.0f)
    pitch =  89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;

  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
  // zr::log("Updated viewing direction.");
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  fov -= (float)yoffset;
  if (fov < 1.0f)
      fov = 1.0f;
  if (fov > 45.0f)
      fov = 45.0f;
  // zr::log("Updated fov to " + std::to_string(fov) + ".");
}

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrameTime = 0.0f; // Time of last frame

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

const float cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      cameraPos += cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      cameraPos -= cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
      yaw = -90;
      pitch = 0;
      cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
      cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
      cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  }
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

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hide the cursor and capture it.
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);


  int width, height, nrChannels;
  unsigned char* data = stbi_load("../assets/container.jpg", &width, &height, &nrChannels, 0);

  unsigned int texture1, texture2;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    zr::log("Texture 1 image couldn't be loaded.", zr::VERBOSITY_LEVEL::ERROR);
  }
  zr::log("Texture 1 loaded successfully.", zr::VERBOSITY_LEVEL::ERROR);

  stbi_image_free(data);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

      // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(true);
  data = stbi_load("../assets/awesomeface.png", &width, &height, &nrChannels, 4);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    zr::log("Texture 2 image couldn't be loaded.", zr::VERBOSITY_LEVEL::ERROR);
  }
  zr::log("Texture 2 loaded successfully.", zr::VERBOSITY_LEVEL::ERROR);

  stbi_image_free(data);

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };
  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  yaw = -90.0f;
  fov = 45.0f;

  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, 0.1f, 100.0f);

  // projection = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 100.0f);

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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(2);

  Shader ourShader ("../learnopengl-tutorials/10-colors-basics/texture.vs", "../learnopengl-tutorials/10-colors-basics/texture.fs");
  ourShader.use();
  glUniform1i(glGetUniformLocation(ourShader.shaderProgramID, "texture1"), 0); // set it manually
  ourShader.setInt("texture2", 1); // or with shader class

  unsigned int modelLoc = glGetUniformLocation(ourShader.shaderProgramID, "model");
  unsigned int viewLoc = glGetUniformLocation(ourShader.shaderProgramID, "view");
  unsigned int projLoc = glGetUniformLocation(ourShader.shaderProgramID, "projection");
  unsigned int transformLoc = glGetUniformLocation(ourShader.shaderProgramID, "transform"); //transform matrix is to move the object itself in the world coordinate

  trans = glm::mat4(1.0f);
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

  float anglular_velocity = 2*3.1415; //Complete one complete rotation in one second.

  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(window)) {
    float currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
    processInput(window);

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, 0.1f, 100.0f); // fov changes inside scroll_callback
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glClearColor(0.9, 1.0, 0.7, 0.4);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    ourShader.setFloat("r", sin(0.09f * anglular_velocity * currentFrameTime));
    ourShader.setFloat("g", sin(0.05f * anglular_velocity * currentFrameTime));
    ourShader.setFloat("b", sin(0.03f * anglular_velocity * currentFrameTime));

    // glBindVertexArray(VAO);
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model,  glm::radians( i * anglular_velocity * currentFrameTime), glm::vec3(sin(anglular_velocity * currentFrameTime), 0.3f, 0.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));        // ourShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // as we only have a single VAO there's no need to bind it every time
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
