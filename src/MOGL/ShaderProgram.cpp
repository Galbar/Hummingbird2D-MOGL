#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.hpp"

namespace mogl
{
ShaderProgram::ShaderProgram():
p_program_id(glCreateProgram()),
p_linked(false)
{}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(p_program_id);
}

ShaderProgram* ShaderProgram::addShader(const Shader& shader)
{
    glAttachShader(p_program_id, shader.getId());
    return this;
}

ShaderProgram* ShaderProgram::bindFragmentOutput(const std::string& output_name)
{
    glBindAttribLocation(p_program_id, 0, output_name.c_str());
    return this;
}

GLint ShaderProgram::bindVertexAttribute(const std::string& attrib_name, GLint size, GLsizei stride, GLvoid* first_pointer)
{
    GLint attrib_pos;

    attrib_pos = glGetAttribLocation(p_program_id, attrib_name.c_str());
    glVertexAttribPointer(attrib_pos, size, GL_FLOAT, GL_FALSE, stride, first_pointer);

    return attrib_pos;
}

ShaderProgram* ShaderProgram::link()
{
    GLint status;
    char buffer[512];

    glLinkProgram(p_program_id);
    glGetProgramiv(p_program_id, GL_LINK_STATUS,& status);
    p_linked = (status == GL_TRUE);
    glGetProgramInfoLog(p_program_id, 512, nullptr, buffer);
    p_error_log.assign(buffer);
    return this;
}

ShaderProgram* ShaderProgram::use()
{
    glUseProgram(p_program_id);
    return this;
}

bool ShaderProgram::isLinked()
{
    return p_linked;
}

const std::string& ShaderProgram::log() const
{
    return p_error_log;
}

ShaderProgram* ShaderProgram::setUniform2f(const std::string& uniform_name, float v0, float v1)
{
    GLint location = glGetUniformLocation(p_program_id, uniform_name.c_str());

    if(location != -1)
    {
        glUniform2f(location, v0, v1);
    }
    return this;
}

ShaderProgram* ShaderProgram::setUniform3f(const std::string& uniform_name, float v0, float v1, float v2)
{
    GLint location = glGetUniformLocation(p_program_id, uniform_name.c_str());

    if(location != -1)
    {
        glUniform3f(location, v0, v1, v2);
    }
    return this;
}

ShaderProgram* ShaderProgram::setUniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3)
{
    GLint location = glGetUniformLocation(p_program_id, uniform_name.c_str());

    if(location != -1)
    {
        glUniform4f(location, v0, v1, v2, v3);
    }
    return this;
}

ShaderProgram* ShaderProgram::setUniformMatrix4f(const std::string& uniform_name, const glm::mat4& mat)
{
    GLint location = glGetUniformLocation(p_program_id, uniform_name.c_str());

    if(location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
    return this;
}
}
