#ifndef MOGL_RECTANGLE_HPP
#define MOGL_RECTANGLE_HPP
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace mogl
{
class Rectangle : public Drawable
{
public:
    /*!
      \brief Class construtor with fill color
     */
    Rectangle (const sf::Color&);

    void init() override;
    void onDestroy() override;

    void setShaderProgram(ShaderProgram* shader_program) override;

    /*!
      \brief Set fill color for the Rectangle
     */
    void setColor(const sf::Color& color);

    /*!
      \brief Get fill color for the Rectangle
     */
    const sf::Color& getColor() const;

    /*!
      \brief Draw the Rectangle
     */
    void draw() override;

    static const char* behaviorName();

private:
    static GLuint s_VAO, s_VBO;
    GLuint p_position_loc;
    sf::Color p_color;
};

/*!
  \class mogl::Rectangle
  \brief A rectangle-shaped 1x1 Drawable.

  For different sizes use the scale in either the hum::Actor hum::Transform of
  the Drawable's hum::Transform.
*/
}
#endif /* ifndef MOGL_RECTANGLE_HPP */
