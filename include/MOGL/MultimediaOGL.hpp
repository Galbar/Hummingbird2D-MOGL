#ifndef MOGL_MULTIMEDIAOGL_HPP
#define MOGL_MULTIMEDIAOGL_HPP

#include <unordered_set>
#include <unordered_map>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "glm.hpp"
#include "Hum2D/Hum2D.hpp"
#include "Drawable.hpp"
#include "ShaderProgramManager.hpp"

namespace mogl
{
class MultimediaOGL : public h2d::Plugin
{
public:
    MultimediaOGL(sf::VideoMode mode, const sf::String& title,
            sf::Uint32 style=sf::Style::Default,
            const sf::ContextSettings& settings=sf::ContextSettings());
    virtual ~MultimediaOGL();
    virtual void gameStart() override;
    virtual void preFixedUpdate() override;
    virtual void postUpdate() override;
    virtual void gameEnd() override;
    virtual sf::Window* window();
    virtual const sf::Window* window() const;

    virtual void addDrawable(Drawable* drawable);
    virtual void removeDrawable(Drawable* drawable);

    virtual void setProjection(const glm::mat4& projection);
    virtual void setView(const glm::mat4& view);

    ShaderProgramManager& shaderPrograms();
    const ShaderProgramManager& shaderPrograms() const;

private:
    sf::Window* p_window;
    std::unordered_set<Drawable*> p_drawable_set;
    std::unordered_map<ShaderProgram*, unsigned int> p_shader_program_usage;
    std::unordered_map<Drawable*, const h2d::Kinematic*> p_drawable_kinematic;
    glm::mat4 p_projection;
    glm::mat4 p_view;
    ShaderProgramManager p_shader_program_manager;
};
}
#endif
