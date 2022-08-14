#ifndef SHADER_H
#define SHADER_H


#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <ZR/core.hpp>

class Shader
{
private:
  /* data */
public:
unsigned int shaderProgramID;
Shader(const char* vertexPath, const char* fragmentPath);
  void use();
  void setBool(const std::string &uniform_name, bool value) const;
  void setInt(const std::string &uniform_name, int value) const;
  void setFloat(const std::string &uniform_name, float value) const;
};

void Shader::setBool(const std::string &uniform_name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgramID, uniform_name.c_str()), (int)value);
}
void Shader::setInt(const std::string &uniform_name, int value) const{
    glUniform1i(glGetUniformLocation(shaderProgramID, uniform_name.c_str()), value);
}
void Shader::setFloat(const std::string &uniform_name, float value) const{
    // glUniform1f(glGetUniformLocation(shaderProgramID, uniform_name.c_str()), value);
    int vertexColorLocation = glGetUniformLocation(shaderProgramID, uniform_name.c_str());
    glUniform1f(vertexColorLocation, value);
}

void Shader::use(){
    glUseProgram(shaderProgramID);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath){
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }catch(std::ifstream::failure e){
    zr::log("Shader not successfully read.",zr::VERBOSITY_LEVEL::ERROR);
    return;
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  int success;
  char infoLog[512];

  unsigned int vertexShaderID;
  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderID, 1, &vShaderCode, NULL);
  glCompileShader(vertexShaderID);

  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE){
    glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
    zr::log ("Vertex shader failed to compile with following error message:", zr::VERBOSITY_LEVEL::ERROR);
    zr::log (infoLog, zr::VERBOSITY_LEVEL::ERROR);
    return;
  }
  zr::log ("Vertex shader compiled successfully.", zr::VERBOSITY_LEVEL::DEBUG);

  unsigned int fragmentShaderID;
  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderID, 1, &fShaderCode, NULL);
  glCompileShader(fragmentShaderID);

  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE){
    glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
    zr::log ("Fragment shader failed to compile with following error message:", zr::VERBOSITY_LEVEL::ERROR);
    zr::log (infoLog, zr::VERBOSITY_LEVEL::ERROR);
    return;
  }
  zr::log ("Fragment shader compiled successfully.", zr::VERBOSITY_LEVEL::DEBUG);

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
      return;
  }
  zr::log ("Shader programs linked successfully.", zr::VERBOSITY_LEVEL::DEBUG);
}
#endif