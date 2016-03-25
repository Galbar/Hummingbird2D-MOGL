#ifndef MOGL_DRAWABLE_HPP
#define MOGL_DRAWABLE_HPP

#include "Hum2D/Hum2D.hpp"
#include "ShaderProgram.hpp"
#include <SFML/OpenGL.hpp>

namespace mogl
{
class Drawable : public h2d::Behavior
{
public:
    Drawable();
    virtual ~Drawable();

    virtual void init() override;
    virtual void onDestroy() override;

    void enable();
    void disable();
    bool isEnabled() const;

    h2d::Transformation& transform();
    const h2d::Transformation& transform() const;
    void setShaderProgram(ShaderProgram* shader_program);
    const ShaderProgram* shaderProgram() const;
    ShaderProgram* shaderProgram();
    virtual void draw() =0;

    static const char* behaviourName();

private:
    bool p_is_enabled;
    h2d::Transformation p_transform;

protected:
    ShaderProgram* p_shader_program;
};
} /* mogl */
#endif
