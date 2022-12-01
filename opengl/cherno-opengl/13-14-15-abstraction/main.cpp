#include "src/renderer.hpp"                                         // Load glew before everything (via renderer)
#include "src/vertex_buffer.hpp"
#include "src/index_buffer.hpp"
#include "src/vertex_array.hpp"

#include "GLFW/glfw3.h"

#include <ZR/core.hpp>

#include <signal.h>
#include <string>
#include <fstream>
#include <sstream>


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
    zr::log_level = zr::VERBOSITY_LEVEL::DEBUG;
    if (!glfwInit()){
        zr::log("GLFW initialization failed.", zr::VERBOSITY_LEVEL::ERROR);
        return -1;
    }
    zr::log("Successfully initialized GLFW.");

    // Choose OpenGL version and setup either compatibility profile or core profile 
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4));
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));      // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLCALL(GLFWwindow *window = glfwCreateWindow(800, 600, "ZR :: Cherno-OpenGL", NULL, NULL));

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

    // Creating va, vb, layout using abstraction

    VertexArray va;
    VertexBuffer vb(vertex_data, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;


    // ------------------------------GLCALL IS WORKING-----------------------

    // Need to tell the layout of the buffer [Explanation is here: https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800]
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0));


    // ------------------------------LAYOUT IS NOT WORKING-----------------------
    // layout.push<float>(2);
    // va.addLayout(layout);
    // va.addBuffer(vb, layout);



    
    // Creating ibo
    IndexBuffer ib(index_data, 6);

    // The path of the is with respect to ZR/opengl/build/.
    ShaderProgramSource source = parseShader("../res/basic.shader");

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
        
        va.bind();
        ib.bind();

        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate(); // Refer to the notes on README.md of this project   
    return 0;
}
