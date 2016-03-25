#ifndef MOGL_RECTANGLE_HPP
#define MOGL_RECTANGLE_HPP
#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace mogl
{
class Rectangle : public Drawable
{
public:
    Rectangle (double width, double height, const sf::Color&);

    void init() override;
    void onDestroy() override;

    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;

    void draw() override;

    static const char* behaviourName();

private:
    GLuint p_VAO, p_VBO, p_position_loc;
    float p_width, p_height;
    sf::Color p_color;
};
}
#endif /* ifndef MOGL_RECTANGLE_HPP */
