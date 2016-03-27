#ifndef MOGL_SHADER_PROGRAM_INCLUDE_HPP
#define MOGL_SHADER_PROGRAM_INCLUDE_HPP

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "glm.hpp"
#include "Shader.hpp"

namespace mogl
{
class ShaderProgram
{

public:
    ShaderProgram();
    ~ShaderProgram();

    ShaderProgram* addShader(const Shader& shader);
    ShaderProgram* bindFragmentOutput(const std::string& output_name);
    GLint bindVertexAttribute(const std::string& attrib_name, GLint size, GLsizei stride, GLvoid* first_pointer);
    ShaderProgram* link();

    ShaderProgram* use();

    // Pass uniforms to the associated shaders
    ShaderProgram* setUniform2f(const std::string& uniform_name, float v0, float v1);
    ShaderProgram* setUniform3f(const std::string& uniform_name, float v0, float v1, float v2);
    ShaderProgram* setUniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3);
    ShaderProgram* setUniformMatrix4f(const std::string& uniform_name, const glm::mat4& mat);

    bool isLinked();
    const std::string& log() const;

private:
    ShaderProgram(const ShaderProgram&) =delete;
    ShaderProgram& operator=(const ShaderProgram&) =delete;

    GLuint p_program_id;
    bool p_linked;
    std::string p_error_log;

};
}
#endif
