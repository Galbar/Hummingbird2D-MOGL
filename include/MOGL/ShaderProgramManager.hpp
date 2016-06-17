#ifndef MOGL_SHADER_PROGRAM_MANAGER_HPP
#define MOGL_SHADER_PROGRAM_MANAGER_HPP
#include <utility>
#include "hummingbird/Log.hpp"
#include "hummingbird/ResourceManager.hpp"
#include "ShaderProgram.hpp"

namespace mogl
{
/*!
  \struct ShaderProgramDef
  \brief A ShaderProgram definition to use with ShaderProgramManager.
*/
struct ShaderProgramDef
{
    Shader& vertex_shader;            //!< Vertex Shader
    Shader& fragment_shader;          //!< Fragment Shader
    std::string fragment_output_name; //!< Name of the output of the fragment shader
};

class ShaderProgramManager : public hum::ResourceManager<ShaderProgram, std::string, ShaderProgramDef>
{
private:
    ShaderProgram* loadResource(const ShaderProgramDef& definition) override;
};

/*!
  \class mogl::ShaderProgramManager
  \brief A hum::ResourceManager for mogl::ShaderProgram.

  This Resource manager is different because it uses ShaderProgramDef%s to load
  the resource (ShaderProgram) instead of the usual `std::string`.

  Example:
  \code
  // Create shaders
  mogl::Shader vs, fs;

  // Load vertex shader from file
  vs.loadFromFile(Shader::Type::VERTEX_SHADER, "shader.vert");
  if(!vs.isCompiled())
  {
    hum::log_e("Vertex shader failed to compile:");
    hum::log_e(vs.log());
    return 1;
  }

  // Load fragment shader from file
  fs.loadFromFile(Shader::Type::FRAGMENT_SHADER, "shader.frag");
  if(!fs.isCompiled())
  {
    hum::log_e("Fragment shader failed to compile:");
    hum::log_e(fs.log());
    return 1;
  }

  mogl::ShaderProgramDef def{vs, fs, "out_color"};

  mogl::ShaderProgramManager spm;
  spm.load("plain_shader", def);

  mogl::ShaderProgram* sp = spm.get("plain_shader");
  sp->use()->setUniform4f("color", 0, 1, 1, 1);

  // ...

  spm.free("plain_shader");
  \endcode
*/
}
#endif /* ifndef SHADER_PROGRAM_MANAGER_HPP */
