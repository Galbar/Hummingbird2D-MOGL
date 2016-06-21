#ifndef MOGL_SPRITE_HPP
#define MOGL_SPRITE_HPP
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace mogl
{
class Sprite : public Drawable
{
public:
    /*!
      \brief Class constructor with the texture to use and the area of the texture to use.

      If the area is empty or not given the hole texture will be used.

      The Sprite doesn't handle the given texture pointer and the pointed texture must
      exists while the Sprite is using it.
     */
    Sprite(const sf::Texture* texture, const sf::IntRect& rect = sf::IntRect());

    void init() override;
    void onDestroy() override;

    void setShaderProgram(ShaderProgram* shader_program) override;

    //! Set the texture to use for the sprite
    void setTexture(const sf::Texture* texture);
    //! Get the texture to use for the sprite
    const sf::Texture* getTexture() const;
    /*!
      \brief Set the texture area to use for the sprite

      If the area is empty or not given the hole texture will be used.

      The Sprite doesn't handle the given texture pointer and the pointed texture must
      exists while the Sprite is using it.
     */
    void setTextureRect(const sf::IntRect& rect);
    //! Get the texture area to use for the sprite
    const sf::IntRect& getTextureRect() const;
    //! Set the color to use for the sprite
    void setColor(const sf::Color& color);
    //! Get the color to use for the sprite
    const sf::Color& getColor() const;

    void draw() override;

    static const char* behaviorName();

protected:
    static GLuint s_VAO, s_VBO;
    GLuint p_position_loc, p_texture_coord_loc;
    sf::Color p_color;
    const sf::Texture* p_texture;
    sf::IntRect p_rect;
};

/*!
  \class mogl::Sprite
  \brief A textured rectangle-shaped 1x1 Drawable

  For different sizes use the scale in either the hum::Actor hum::Transform of
  the Drawable's hum::Transform.
*/
}
#endif /* ifndef MOGL_RECTANGLE_HPP */

