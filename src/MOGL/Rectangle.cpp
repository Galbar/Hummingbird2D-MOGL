#include "Rectangle.hpp"
#include "MultimediaOGL.hpp"

namespace mogl
{
GLuint Rectangle::s_VAO = 0;
GLuint Rectangle::s_VBO = 0;

Rectangle::Rectangle (const sf::Color& color):
p_color(color)
{}

void Rectangle::init()
{
    if (s_VAO == 0)
    {
        float vert[12] = { 0. , 0. ,
                           1. , 0. ,
                           1. , 1. ,
                           0. , 0. ,
                           1. , 1. ,
                           0. , 1. };

        glGenVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO);
        glGenBuffers(1, &s_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vert, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    setShaderProgram(actor().game().getPlugin<MultimediaOGL>()->shaderPrograms().get("_mogl_plain"));
    Drawable::init();
}
void Rectangle::onDestroy()
{
    Drawable::onDestroy();
}

void Rectangle::setShaderProgram(ShaderProgram* shader_program)
{
    Drawable::setShaderProgram(shader_program);
    glBindVertexArray(s_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    p_position_loc = shaderProgram()->bindVertexAttribute("position", 2, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    glBindVertexArray(s_VAO);
    shaderProgram()->setUniform4f("color",
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
