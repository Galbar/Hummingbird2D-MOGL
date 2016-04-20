#ifndef MOGL_DRAWABLE_HPP
#define MOGL_DRAWABLE_HPP

#include "hummingbird/hum.hpp"
#include "ShaderProgram.hpp"
#include <SFML/OpenGL.hpp>

namespace mogl
{
class Drawable : public hum::Behavior
{
public:
    Drawable();
    virtual ~Drawable();

    virtual void init() override;
    virtual void onActivate() override;
    virtual void onDeactivate() override;
    virtual void onDestroy() override;

    void enable();
    void disable();
    bool isEnabled() const;

    hum::Transformation& transform();
    const hum::Transformation& transform() const;
    virtual void setShaderProgram(ShaderProgram* shader_program);
    const ShaderProgram* shaderProgram() const;
    ShaderProgram* shaderProgram();
    virtual void draw() =0;

    void setOrigin(const hum::Vector3f& origin);
    const hum::Vector3f& getOrigin() const;

    static const char* behaviorName();

private:
    bool p_is_enabled;
    hum::Transformation p_transform;
    hum::Vector3f p_origin;
    ShaderProgram* p_shader_program;
};
} /* mogl */
#endif
