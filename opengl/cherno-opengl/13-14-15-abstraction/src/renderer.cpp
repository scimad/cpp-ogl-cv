#include <ZR/core.hpp>
#include "renderer.hpp"


void GLClearError(){
    while (glGetError() != GL_NO_ERROR){};
}

bool GLIsErrorFree(const char* function, const char* file, int line){
    bool is_error_free = true;
    while (GLenum error = glGetError()){
        zr::log("OpenGL Error (code "
        + std::to_string(error) +  ") from: " + function + " " + file + ":" + std::to_string(line), zr::VERBOSITY_LEVEL::ERROR);
        is_error_free = false;
    }
    return is_error_free;
}
