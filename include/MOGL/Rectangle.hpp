#ifndef MOGL_RECTANGLE_HPP
#define MOGL_RECTANGLE_HPP
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace mogl
{
class Rectangle : public Drawable
{
public:
    Rectangle (const sf::Color&);

    void init() override;
    void onDestroy() override;

    void setShaderProgram(ShaderProgram* shader_program) override;

    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;

    void draw() override;

    static const char* behaviorName();

private:
    static GLuint s_VAO, s_VBO;
    GLuint p_position_loc;
    sf::Color p_color;
};
}
#endif /* ifndef MOGL_RECTANGLE_HPP */
