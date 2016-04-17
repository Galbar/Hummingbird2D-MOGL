#include "Rectangle.hpp"
#include "MultimediaOGL.hpp"

namespace mogl
{
Rectangle::Rectangle (double width, double height, const sf::Color& color):
p_width(width),
p_height(height),
p_color(color)
{}

void Rectangle::init()
{
    p_shader_program = actor().game().getPlugin<MultimediaOGL>()->shaderPrograms().get("_mogl_plain");
    float vert[12] = {
        0.             , 0.       ,
        p_width        , 0.       ,
        p_width        , p_height ,
        0.             , 0.       ,
        p_width        , p_height ,
        0.             , p_height
    };

    glGenVertexArrays(1, &p_VAO);
    glBindVertexArray(p_VAO);
    glGenBuffers(1, &p_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vert, GL_STATIC_DRAW);
    p_position_loc = p_shader_program->bindVertexAttribute("position", 2, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    Drawable::init();
}
void Rectangle::onDestroy()
{
    Drawable::onDestroy();
    glDeleteBuffers(1, &p_VBO);
    glDeleteVertexArrays(1, &p_VAO);
}

void Rectangle::setColor(const sf::Color& color)
{
    p_color = color;
}

const sf::Color& Rectangle::getColor() const
{
    return p_color;
}

void Rectangle::draw()
{
    glBindVertexArray(p_VAO);
    p_shader_program->setUniform4f("color",
            static_cast<float>(p_color.r)/255.0f,
            static_cast<float>(p_color.g)/255.0f,
            static_cast<float>(p_color.b)/255.0f,
            static_cast<float>(p_color.a)/255.0f);
    glEnableVertexAttribArray(p_position_loc);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

const char* Rectangle::behaviorName()
{
    return "mogl::Rectangle";
}
}
