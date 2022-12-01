#include "GL/glew.h"
// #include <glad/glad.h>                                         // Looks like GLAD is not required when GLEW is used! (Needs Verification)
#include "GLFW/glfw3.h"

#include "signal.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <ZR/core.hpp>

#define ASSERT(x) if (!(x)) raise(SIGTRAP);

#define GLCALL(x)\
    GLClearError();\
    x;\
    ASSERT(GLIsErrorFree(#x, __FILE__, __LINE__))

static void GLClearError(){
    while (glGetError() != GL_NO_ERROR){};
}

static bool GLIsErrorFree(const char* function, const char* file, int line){
    bool is_error_free = true;
    while (GLenum error = glGetError()){
        zr::log("OpenGL Error (code "
        + std::to_string(error) +  ") from: " + function + " " + file + ":" + std::to_string(line), zr::VERBOSITY_LEVEL::ERROR);
        is_error_free = false;
    }
    return is_error_free;
}

struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;
};

enum class ShaderType{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

static void GLunbindShaderVertexIndexBuffer(){
    GLCALL(glBindVertexArray(0));
    GLCALL(glUseProgram(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};

static ShaderProgramSource parseShader(const std::string& file){
    std::ifstream stream(file);
    std::string line;
    std::stringstream ss[2];
    ShaderType shader_type = ShaderType::NONE;
    while (getline(stream, line)){
        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                shader_type = ShaderType::VERTEX;
            }else if (line.find("fragment") != std::string::npos){
                shader_type = ShaderType::FRAGMENT;
            }
        }else{
            ss[(int) shader_type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

static int compileShader(GLenum shader_type, const std::string& shader_program){
    GLuint shader_handle = glCreateShader(shader_type);
    const char* shader_src = shader_program.c_str();
    glShaderSource(shader_handle, 1, &shader_src, NULL);
    glCompileShader(shader_handle);

    GLint result;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE){
        zr::log(std::string("Failed to compile ") + (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader.", zr::VERBOSITY_LEVEL::ERROR);
        int length;
        glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &length);
        char* err_msg = (char*) alloca(length * sizeof(char));    //Dynamic size char array allocation on stack using alloca()
        glGetShaderInfoLog(shader_handle, length, &length, err_msg);
        zr::log(std::string(err_msg), zr::VERBOSITY_LEVEL::ERROR);
    }
    return shader_handle;
}

static int createShader(const std::string& vert_shader, const std::string& frag_shader){
    GLuint program_handle = glCreateProgram();
    GLuint vs_handle = compileShader(GL_VERTEX_SHADER, vert_shader);
    GLuint fs_handle = compileShader(GL_FRAGMENT_SHADER, frag_shader);

    glAttachShader(program_handle, vs_handle);
    glAttachShader(program_handle, fs_handle);
    glLinkProgram(program_handle);
    glValidateProgram(program_handle);

    glDeleteShader(vs_handle);
    glDeleteShader(fs_handle);
    return program_handle;
}

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

    // Choose OpenGL version and setup either compatibility profile or core profile 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "ZR :: Cherno-OpenGL", NULL, NULL);

    if (!window){
        zr::log("Failed to create GLFW window.", zr::VERBOSITY_LEVEL::ERROR);
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    zr::log("Successfully created GLFW window.");

    // glfwSwapInterval(1);

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

    // glfwMakeContextCurrent(window);
    glClearColor(0.2, 0.2, 0.2, 0.0);

    // Create new vertex buffer
    float vertex_data[] = {
     0.0,  0.0,
     0.5,  0.0,
     0.5,  0.5,
     0.0,  0.5
    };

    unsigned int index_data[] = {
        0, 1, 2,
        2, 3, 0
    };

    //Generating at least one VAO is compulsory in core profile but a default one is available in compatibility profile
    GLuint int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // creating vertex buffer object (handle for the vertex buffer)
    GLuint vbo;
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertex_data, GL_STATIC_DRAW));

    // Need to tell the layout of the buffer [Explanation is here: https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800]
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0));

    // Creating index buffer object (handle for the vertex buffer)
    GLuint ibo;
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), index_data, GL_STATIC_DRAW));

    // The path of the is with respect to ZR/opengl/build/.
    ShaderProgramSource source = parseShader("../cherno-opengl/12-vertex-arrays/res/basic.shader");

    GLuint shader = createShader(source.vertexSource, source.fragmentSource);
    //Binding a shader
    GLCALL(glUseProgram(shader));

    int location = glGetUniformLocation(shader, "u_Color");
    ASSERT(location != -1);
    GLCALL(glUniform4f(location, 0.0, 0.2, 0.5, 0.0));

    //If we have multiple vertex buffer objects and layouts to be bind within the loop, then:

    // Unbind everything
    GLunbindShaderVertexIndexBuffer();

    // Utility variables
    static bool exit_flag = false;
    float r = 0.0f;
    float increament = 0.03f;

    /* Loop until the user closes the window */
    while (!exit_flag){
        r += increament;
        if (r > 1 || r < 0) increament *= -1;

        exit_flag = glfwWindowShouldClose(window);
        processInput(window);
    
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLCALL(glUseProgram(shader));
        GLCALL(glUniform4f(location, r, 0.2, 0.5, 0.0));
        
        GLCALL(glBindVertexArray(vao));

        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
