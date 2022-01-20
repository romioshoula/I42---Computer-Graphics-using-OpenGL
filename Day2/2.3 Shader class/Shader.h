
#pragma once
#include <glew.h>
class Shader
{
private:
    static char* readFile(const char* fileName);
    bool compiledStatus(GLint shaderID);
    GLuint makeShader(const char* ShaderSourceCode, GLenum
        SHADER_TYPE);
    GLuint makeShaderProgram(GLuint vertShaderID, GLuint
        fragShaderID);
    void InitShader(const char* vertex_shader_file_name, const
        char* fragment_shader_file_name);
    Shader(const char* vertex_shader_filename, const char*
        fragment_shader_filename);
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;
    GLuint shader_program_id;
public:
    static std::shared_ptr<Shader> create(const char*
        vertex_shader_filename, const char* fragment_shader_filename);
    GLuint get_uniform_loc(std::string uniform);
    void use()
    {
        glUseProgram(shader_program_id);
    }
    ~Shader();
};
