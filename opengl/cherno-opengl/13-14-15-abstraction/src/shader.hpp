#ifndef __SHADER
#define __SHADER

#include <string>

struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader{
private:
    unsigned int rendererID;
    GLuint shader;
    std::string shader_filename;

    //caching for uniforms;
public:
    Shader(const std::string& filename);
    ~Shader();

    unsigned int getRendererID(){return rendererID;}

    void bind();
    void unbind();

    //Set uniforms
    void setUniform4f(const std::string& uni_name, float v1, float v2, float v3, float v4);

    ShaderProgramSource parseShader(const std::string& file);

private:
    int getUniformLocation(const std::string& uni_name);
    GLuint createShader(const std::string& vert_shader, const std::string& frag_shader);
    unsigned int compileShader(GLenum shader_type, const std::string& shader_program);


};


// int compileShader(GLenum shader_type, const std::string& shader_program);



#endif //__SHADER
