#include "ShaderProgramManager.hpp"

namespace mogl
{
ShaderProgram* ShaderProgramManager::loadResource(const ShaderProgramDef& definition)
{
    ShaderProgram* program = new ShaderProgram();
    program
        ->addShader(definition.vertex_shader)
        ->addShader(definition.fragment_shader)
        ->link()
        ->bindFragmentOutput(definition.fragment_output_name);
    if (program->isLinked())
    {
        return program;
    }
    hum::log_d(program->log());
    delete program;
    return nullptr;
}
}
