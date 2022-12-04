#include "src/renderer.hpp"                                         // Load glew before everything (via renderer)
#include "src/vertex_buffer.hpp"
#include "src/index_buffer.hpp"
#include "src/vertex_array.hpp"
#include "src/shader.hpp"
#include "src/texture.hpp"

#include "GLFW/glfw3.h"

#include <ZR/core.hpp>

#include <signal.h>
#include <string>


static void GLunbindShaderVertexIndexBuffer(){
    GLCALL(glBindVertexArray(0));
    GLCALL(glUseProgram(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};

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
     0.0,  0.0, 0.0, 0.0,
     0.5,  0.0, 1.0, 0.0,
     0.5,  0.5, 1.0, 1.0,
     0.0,  0.5, 0.0, 1.0
    };

    unsigned int index_data[] = {
        0, 1, 2,
        2, 3, 0
    };

    // This gives transparency to transparent regions of pngs
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Creating va, vb, layout using abstraction

    VertexArray va;
    VertexBuffer vb(vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices 

    // ------------------------------GLCALL IS WORKING-----------------------

    // Need to tell the layout of the buffer [Explanation is here: https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800]

    // ------------------------------LAYOUT IS NOT WORKING-----------------------
    VertexBufferLayout layout;
    layout.push<float>(2); //for x, y
    layout.push<float>(2); //for texture u, v
    va.addBuffer(vb, layout);

    // Creating ibo
    IndexBuffer ib(index_data, 6);

    // The path of the is with respect to ZR/opengl/build/.
    Shader shader("../res/basic.shader");
    shader.bind();
    shader.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);

    Texture texture("../res/chess/Chess_qlt45.svg.png");                          //https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces
    texture.bind();
    shader.setUniform1i("u_texture", 0);
 



    //If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered 
    // depending on the program logic
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    Renderer renderer;

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

        // Following shader binding is actually refactored / solved using Materials
        shader.bind();
        shader.setUniform4f("u_color", r, 0.2, 0.5, 0.0); //if uniform is not used in shader, it gives error / notification

        renderer.draw(va, ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate(); // Refer to the notes on README.md of this project   
    return 0;
}
