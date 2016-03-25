#ifndef MOGL_SHADER_INCLUDE_HPP
#define MOGL_SHADER_INCLUDE_HPP

#include <string>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

namespace mogl
{
class Shader
{
public:
    enum class Type { VERTEX_SHADER, FRAGMENT_SHADER };
    Shader();
    ~Shader();

    // These methods should be called with an active OpenGL context
    void loadFromSource(const Type type, const std::string& source);
    bool loadFromFile(const Type type, const std::string& filename);

    GLuint getId() const;
    bool isCompiled() const;
    const std::string& log() const;

private:
    Shader(const Shader&) =delete;
    Shader& operator=(const Shader&) = delete;

    bool loadShaderSource(const std::string& filename, std::string& shader_source);

private:
    GLuint p_shader_id;
    bool p_compiled;
    std::string p_error_log;

};
}
#endif
