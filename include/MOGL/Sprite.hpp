#ifndef MOGL_SPRITE_HPP
#define MOGL_SPRITE_HPP
#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace mogl
{
class Sprite : public Drawable
{
public:
    Sprite(double width, double height, const sf::Texture* texture, const sf::IntRect& rect = sf::IntRect());

    void init() override;
    void onDestroy() override;

    void setTexture(const sf::Texture* texture);
    const sf::Texture* getTexture() const;
    void setTextureRect(const sf::IntRect& rect);
    const sf::IntRect& getTextureRect() const;
    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;

    void draw() override;

    static const char* behaviorName();

protected:
    GLuint p_VAO, p_VBO, p_position_loc, p_texture_coord_loc;
    float p_width, p_height;
    sf::Color p_color;
    const sf::Texture* p_texture;
    sf::IntRect p_rect;
};
}
#endif /* ifndef MOGL_RECTANGLE_HPP */

