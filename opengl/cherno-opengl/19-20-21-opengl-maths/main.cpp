#include "src/renderer.hpp"                                         // Load glew before everything (via renderer)
#include "src/vertex_buffer.hpp"
#include "src/index_buffer.hpp"
#include "src/vertex_array.hpp"
#include "src/shader.hpp"
#include "src/texture.hpp"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));      // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLCALL(GLFWwindow *window = glfwCreateWindow(960, 540, "ZR :: Cherno-OpenGL", NULL, NULL));

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

    glClearColor(0.2, 0.2, 0.2, 0.0);

    // Create new vertex buffer
    float vertex_data[] = {
     100.0,  100.0, 0.0, 0.0,
     200.0,  100.0, 1.0, 0.0,
     200.0,  200.0, 1.0, 1.0,
     100.0,  200.0, 0.0, 1.0
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

    // Need to tell the layout of the buffer [Explanation is here: https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800]
    VertexBufferLayout layout;
    layout.push<float>(2); //for x, y
    layout.push<float>(2); //for texture u, v
    va.addBuffer(vb, layout);

    // glm::mat4 proj = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // This seems to be default(?)
    glm::mat4 proj = glm::ortho(0.0, 960.0, 0.0, 540.0, -1.0, 1.0);
    glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(-100.0, 0.0, 0.0));
    // glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(200, 200, 0));

    // glm::mat4 mvp = proj * view * model;

    // Creating ibo
    IndexBuffer ib(index_data, 6);

    // The path of the is with respect to ZR/opengl/build/.
    Shader shader("../res/basic.shader");
    shader.bind();
    shader.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);
    // shader.setUniformMat4f("u_MVP", mvp);

    Texture texture("../../../assets/chess/Chess_qlt45.svg.png");                          //https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    // Utility variables
    static bool exit_flag = false;
    float r = 0.0f;
    float increament = 0.03f;

    glm::vec3 translation(200, 200, 0);

    /* Loop until the user closes the window */
    while (!exit_flag){
        r += increament;
        if (r > 1 || r < 0) increament *= -1;

        exit_flag = glfwWindowShouldClose(window);
        processInput(window);
    
        /* Render here */

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        glm::mat4 model = glm::translate(glm::mat4(1.0), translation);

        glm::mat4 mvp = proj * view * model;




        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);


        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);            // Edit 3 float using a slider from 0.0f to 960f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Following shader binding is actually refactored / solved using Materials
        shader.bind();
        shader.setUniformMat4f("u_MVP", mvp);
        shader.setUniform4f("u_color", r, 0.2, 0.5, 0.0); //if uniform is not used in shader, it gives error / notification

        renderer.draw(va, ib, shader);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate(); // Refer to the notes on README.md of this project   
    return 0;
}
