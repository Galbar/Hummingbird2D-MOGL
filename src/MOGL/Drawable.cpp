#include "Drawable.hpp"
#include "MultimediaOGL.hpp"

namespace mogl
{
Drawable::Drawable():
p_is_enabled(true),
p_origin(0.0),
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

void Drawable::onActivate()
{
    enable();
}

void Drawable::onDeactivate()
{
    disable();
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

hum::Transformation& Drawable::transform()
{
    return p_transform;
}

const hum::Transformation& Drawable::transform() const
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

void Drawable::setOrigin(const hum::Vector3f& origin)
{
    p_origin = origin;
}

const hum::Vector3f& Drawable::getOrigin() const
{
    return p_origin;
}

const char* Drawable::behaviorName()
{
    return "mogl::Drawable";
}
}
