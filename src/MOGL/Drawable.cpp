#include "Drawable.hpp"
#include "MultimediaOGL.hpp"

namespace mogl
{
Drawable::Drawable():
p_is_enabled(true),
p_shader_program(nullptr)
{}

Drawable::~Drawable()
{}

void Drawable::init()
{
    if (p_is_enabled)
    {
        actor().game().getPlugin<MultimediaOGL>()->addDrawable(this);
    }
}

void Drawable::onDestroy()
{
    disable();
}

void Drawable::enable()
{
    if (!p_is_enabled)
    {
        actor().game().getPlugin<MultimediaOGL>()->addDrawable(this);
        p_is_enabled = true;
    }
}

void Drawable::disable()
{
    if (p_is_enabled)
    {
        actor().game().getPlugin<MultimediaOGL>()->removeDrawable(this);
        p_is_enabled = false;
    }
}

bool Drawable::isEnabled() const
{
    return p_is_enabled;
}

h2d::Transformation& Drawable::transform()
{
    return p_transform;
}

const h2d::Transformation& Drawable::transform() const
{
    return p_transform;
}

void Drawable::setShaderProgram(ShaderProgram* shader_program)
{
    p_shader_program = shader_program;
}

ShaderProgram* Drawable::shaderProgram()
{
    return p_shader_program;
}

const ShaderProgram* Drawable::shaderProgram() const
{
    return p_shader_program;
}

const char* Drawable::behaviourName()
{
    return "mogl::Drawable";
}
}
