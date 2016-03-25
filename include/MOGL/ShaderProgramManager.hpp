#ifndef MOGL_SHADER_PROGRAM_MANAGER_HPP
#define MOGL_SHADER_PROGRAM_MANAGER_HPP
#include <utility>
#include "Hum2D/Log.hpp"
#include "Hum2D/ResourceManager.hpp"
#include "ShaderProgram.hpp"

namespace mogl
{
struct ShaderProgramDef
{
    Shader& vertex_shader;
    Shader& fragment_shader;
    std::string fragment_output_name;
};

class ShaderProgramManager : public h2d::ResourceManager<ShaderProgram, std::string, ShaderProgramDef>
{
private:
    ShaderProgram* loadResource(const ShaderProgramDef& definition) override;
};
}
#endif /* ifndef SHADER_PROGRAM_MANAGER_HPP */
