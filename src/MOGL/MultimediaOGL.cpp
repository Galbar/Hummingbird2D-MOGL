#include "MultimediaOGL.hpp"

namespace mogl
{
MultimediaOGL::MultimediaOGL(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings):
p_window(mode, title, style, settings)
{
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0, 0, 0, 1);
}

MultimediaOGL::~MultimediaOGL()
{}

void MultimediaOGL::gameStart()
{
    Shader *v_shader, *f_shader;
    v_shader = new Shader();
    v_shader->loadFromSource(Shader::Type::VERTEX_SHADER,
#include "../../shaders/plain.vert"
    );
    h2d_assert(v_shader->isCompiled(), "Error compiling plain.vert"
            << std::endl << v_shader->log());

    f_shader = new Shader();
    f_shader->loadFromSource(Shader::Type::FRAGMENT_SHADER,
#include "../../shaders/plain.frag"
    );
    h2d_assert(f_shader->isCompiled(), "Error compiling plain.frag"
            << std::endl << f_shader->log());

    p_shader_program_manager.load("_mogl_plain", ShaderProgramDef{*v_shader, *f_shader, "out_color"});

    delete v_shader;
    delete f_shader;

    v_shader = new Shader();
    v_shader->loadFromSource(Shader::Type::VERTEX_SHADER,
#include "../../shaders/texture.vert"
    );
    h2d_assert(v_shader->isCompiled(), "Error compiling plain.vert"
            << std::endl << v_shader->log());


    f_shader = new Shader();
    f_shader->loadFromSource(Shader::Type::FRAGMENT_SHADER,
#include "../../shaders/texture.frag"
    );
    h2d_assert(f_shader->isCompiled(), "Error compiling plain.frag"
            << std::endl << f_shader->log());

    p_shader_program_manager.load("_mogl_texture", ShaderProgramDef{*v_shader, *f_shader, "out_color"});

    delete v_shader;
    delete f_shader;
}

void MultimediaOGL::preFixedUpdate()
{
    p_sound_manager.clearSounds();
    p_input.update();
    sf::Event event;
    while (p_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            game().setRunning(false);
        }
        p_input.handleEvent(event);
    }
}

void MultimediaOGL::postUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto it : p_shader_program_usage)
    {
        it.first->use();
        it.first->setUniformMatrix4f("projection", p_projection);
        it.first->setUniformMatrix4f("view", p_view);
    }

    for (Drawable* drawable : p_drawable_set)
    {
        h2d_assert(drawable->shaderProgram() != nullptr, "Found a drawable without a shader program");

        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(
                    drawable->transform().x + drawable->actor().transform().x,
                    drawable->transform().y + drawable->actor().transform().y,
                    drawable->transform().z + drawable->actor().transform().z));
        model = glm::rotate(model,
                glm::radians(static_cast<float>(
                        drawable->transform().rotation + drawable->actor().transform().rotation
                        )),
                glm::vec3(0., 0., 1.));
        model = glm::scale(model, glm::vec3(
                    drawable->transform().scale_x * drawable->actor().transform().scale_x,
                    drawable->transform().scale_y * drawable->actor().transform().scale_y,
                    1.));
        drawable->shaderProgram()->use();
        drawable->shaderProgram()->setUniformMatrix4f("model", model);
        drawable->draw();
    }
    glBindVertexArray(0);
    p_window.display();
}

void MultimediaOGL::gameEnd()
{
    p_shader_program_manager.free("_mogl_plain");
    p_shader_program_manager.free("_mogl_texture");
    p_window.close();
}

sf::Window& MultimediaOGL::window()
{
    return p_window;
}

const sf::Window& MultimediaOGL::window() const
{
    return p_window;
}

void MultimediaOGL::addDrawable(Drawable* drawable)
{
    p_drawable_set.insert(drawable);
    try
    {
        p_drawable_kinematic[drawable] = drawable->actor().getBehavior<h2d::Kinematic>();
    }
    catch (h2d::exception::BehaviorNotFound e)
    {
        p_drawable_kinematic[drawable] = nullptr;
    }

    if (drawable->shaderProgram())
    {
        if (p_shader_program_usage.find(drawable->shaderProgram()) == p_shader_program_usage.end())
        {
            p_shader_program_usage.insert(std::make_pair(drawable->shaderProgram(), 0));
        }

        p_shader_program_usage[drawable->shaderProgram()] += 1;
    }
}

void MultimediaOGL::removeDrawable(Drawable* drawable)
{
    p_drawable_set.erase(drawable);
    p_drawable_kinematic.erase(drawable);

    if (drawable->shaderProgram())
    {
        p_shader_program_usage[drawable->shaderProgram()] -= 1;

        if (p_shader_program_usage[drawable->shaderProgram()] == 0)
        {
            p_shader_program_usage.erase(drawable->shaderProgram());
        }
    }
}

void MultimediaOGL::setProjection(const glm::mat4& projection)
{
    p_projection = projection;
}

void MultimediaOGL::setView(const glm::mat4& view)
{
    p_view = view;
}

ShaderProgramManager& MultimediaOGL::shaderPrograms()
{
    return p_shader_program_manager;
}

const ShaderProgramManager& MultimediaOGL::shaderPrograms() const
{
    return p_shader_program_manager;
}

const InputHandler& MultimediaOGL::input() const
{
    return p_input;
}

InputHandler& MultimediaOGL::input()
{
    return p_input;
}

TextureManager& MultimediaOGL::textures()
{
    return p_texture_manager;
}

const TextureManager& MultimediaOGL::textures() const
{
    return p_texture_manager;
}

SpriteAnimationManager& MultimediaOGL::spriteAnimations()
{
    return p_sprite_animation_manager;
}

const SpriteAnimationManager& MultimediaOGL::spriteAnimations() const
{
    return p_sprite_animation_manager;
}

SoundManager& MultimediaOGL::sounds()
{
    return p_sound_manager;
}

const SoundManager& MultimediaOGL::sounds() const
{
    return p_sound_manager;
}

MusicManager& MultimediaOGL::music()
{
    return p_music_manager;
}

const MusicManager& MultimediaOGL::music() const
{
    return p_music_manager;
}
}
