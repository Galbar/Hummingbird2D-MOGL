#include "Sprite.hpp"
#include "MultimediaOGL.hpp"

namespace mogl
{
GLuint Sprite::s_VAO = 0;
GLuint Sprite::s_VBO = 0;

Sprite::Sprite(const sf::Texture* texture, const sf::IntRect& rect):
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
    if (s_VAO == 0)
    {
        float vert[18] = { 0. , 0. , 0 ,
                           1. , 0. , 1 ,
                           1. , 1. , 2 ,
                           0. , 0. , 0 ,
                           1. , 1. , 2 ,
                           0. , 1. , 3 };

        glGenVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO);
        glGenBuffers(1, &s_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vert, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    setShaderProgram(actor().game().getPlugin<MultimediaOGL>()->shaderPrograms().get("_mogl_texture"));
    Drawable::init();
}

void Sprite::onDestroy()
{
    Drawable::onDestroy();
}

void Sprite::setShaderProgram(ShaderProgram* shader_program)
{
    Drawable::setShaderProgram(shader_program);
    glBindVertexArray(s_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    p_position_loc = shaderProgram()->bindVertexAttribute("position", 2, 3*sizeof(float), 0);
    p_texture_coord_loc = shaderProgram()->bindVertexAttribute("point_id", 1, 3*sizeof(float), (void *)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    glBindVertexArray(s_VAO);
    shaderProgram()->setUniform4f("texture_coords",
            static_cast<float>(p_rect.left)/static_cast<float>(p_texture->getSize().x),
            static_cast<float>(p_rect.top)/static_cast<float>(p_texture->getSize().y),
            static_cast<float>(p_rect.width)/static_cast<float>(p_texture->getSize().x),
            static_cast<float>(p_rect.height)/static_cast<float>(p_texture->getSize().y));
    shaderProgram()->setUniform4f("color",
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
