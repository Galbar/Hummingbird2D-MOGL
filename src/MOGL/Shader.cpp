#include <fstream>
#include "Shader.hpp"

namespace mogl
{
Shader::Shader():
p_shader_id(0),
p_compiled(false)
{}

Shader::~Shader()
{
    glDeleteShader(p_shader_id);
}

void Shader::loadFromSource(const Shader::Type type, const std::string& source)
{
    const char *source_ptr = source.c_str();
    GLint status;
    char buffer[512];

    if (type == Type::VERTEX_SHADER)
    {
        p_shader_id = glCreateShader(GL_VERTEX_SHADER);
    }
    else
    {
        p_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    }

    if(p_shader_id == 0)
    {
        return;
    }
    glShaderSource(p_shader_id, 1, &source_ptr, nullptr);
    glCompileShader(p_shader_id);
    glGetShaderiv(p_shader_id, GL_COMPILE_STATUS, &status);
    p_compiled = (status == GL_TRUE);
    glGetShaderInfoLog(p_shader_id, 512, nullptr, buffer);
    p_error_log.assign(buffer);
}

bool Shader::loadFromFile(const Shader::Type type, const std::string& filename)
{
    std::string shader_source;
    if(!loadShaderSource(filename, shader_source))
    {
        return false;
    }
    loadFromSource(type, shader_source);
    return true;
}

GLuint Shader::getId() const
{
    return p_shader_id;
}

bool Shader::isCompiled() const
{
    return p_compiled;
}

const std::string& Shader::log() const
{
    return p_error_log;
}

bool Shader::loadShaderSource(const std::string& filename, std::string& shader_source)
{
    std::ifstream file;
    file.open(filename.c_str());
    if(!file.is_open())
    {
        return false;
    }
    shader_source.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    return true;
}
}
