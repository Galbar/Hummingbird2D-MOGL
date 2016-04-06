#include "Sprite.hpp"
#include "MultimediaOGL.hpp"

namespace mogl
{
Sprite::Sprite(double width, double height, const sf::Texture* texture, const sf::IntRect& rect):
p_width(width),
p_height(height),
p_color(sf::Color::White),
p_texture(texture),
p_rect(rect)
{
    if (p_rect == sf::IntRect())
    {
        p_rect = sf::IntRect(0, 0, p_texture->getSize().x, p_texture->getSize().y);
    }
}

void Sprite::init()
{
    p_shader_program = actor().game().getPlugin<MultimediaOGL>()->shaderPrograms().get("_mogl_texture");
    float vert[18] = {
        0.             , 0.        , 0 ,
        p_width        , 0.        , 1 ,
        p_width        , p_height  , 2 ,
        0.             , 0.        , 0 ,
        p_width        , p_height  , 2 ,
        0.             , p_height  , 3
    };

    glGenVertexArrays(1, &p_VAO);
    glBindVertexArray(p_VAO);
    glGenBuffers(1, &p_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vert, GL_STATIC_DRAW);
    p_position_loc = p_shader_program->bindVertexAttribute("position", 2, 3*sizeof(float), 0);
    p_texture_coord_loc = p_shader_program->bindVertexAttribute("point_id", 1, 3*sizeof(float), (void *)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    Drawable::init();
}

void Sprite::onDestroy()
{
    Drawable::onDestroy();
    glDeleteBuffers(1, &p_VBO);
}

void Sprite::setTexture(const sf::Texture* texture)
{
    p_texture = texture;
}

const sf::Texture* Sprite::getTexture() const
{
    return p_texture;
}

void Sprite::setTextureRect(const sf::IntRect& rect)
{
    p_rect = rect;
}

const sf::IntRect& Sprite::getTextureRect() const
{
    return p_rect;
}

void Sprite::setColor(const sf::Color& color)
{
    p_color = color;
}

const sf::Color& Sprite::getColor() const
{
    return p_color;
}

void Sprite::draw()
{
    sf::Texture::bind(p_texture, sf::Texture::Normalized);
    glBindVertexArray(p_VAO);
    p_shader_program->setUniform4f("texture_coords",
            static_cast<float>(p_rect.left)/static_cast<float>(p_texture->getSize().x),
            static_cast<float>(p_rect.top)/static_cast<float>(p_texture->getSize().y),
            static_cast<float>(p_rect.width)/static_cast<float>(p_texture->getSize().x),
            static_cast<float>(p_rect.height)/static_cast<float>(p_texture->getSize().y));
    p_shader_program->setUniform4f("color",
            static_cast<float>(p_color.r)/255.0f,
            static_cast<float>(p_color.g)/255.0f,
            static_cast<float>(p_color.b)/255.0f,
            static_cast<float>(p_color.a)/255.0f);
    glEnableVertexAttribArray(p_position_loc);
    glEnableVertexAttribArray(p_texture_coord_loc);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    sf::Texture::bind(NULL);
}
const char* Sprite::behaviorName()
{
    return "mogl::Sprite";
}
}
