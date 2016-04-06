#include "MultimediaOGL.hpp"

namespace mogl
{
MultimediaOGL::MultimediaOGL(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings):
p_mode(mode),
p_title(title),
p_style(style),
p_settings(settings),
p_window(nullptr),
p_input(new InputHandler()),
p_shader_program_manager(new ShaderProgramManager()),
p_texture_manager(new TextureManager()),
p_sprite_animation_manager(new SpriteAnimationManager()),
p_music_manager(new MusicManager()),
p_sound_manager(new SoundManager())
{}

MultimediaOGL::~MultimediaOGL()
{
    delete p_input;
    delete p_shader_program_manager;
    delete p_texture_manager;
    delete p_sprite_animation_manager;
    delete p_music_manager;
    delete p_sound_manager;
}

void MultimediaOGL::gameStart()
{
    p_window = new sf::Window(p_mode, p_title, p_style, p_settings);
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 1);

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

    p_shader_program_manager->load("_mogl_plain", ShaderProgramDef{*v_shader, *f_shader, "out_color"});

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

    p_shader_program_manager->load("_mogl_texture", ShaderProgramDef{*v_shader, *f_shader, "out_color"});

    delete v_shader;
    delete f_shader;
}

void MultimediaOGL::preFixedUpdate()
{
    p_sound_manager->clearSounds();
    p_input->update();
    sf::Event event;
    while (p_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            game().setRunning(false);
        }
        p_input->handleEvent(event);
    }
}

void MultimediaOGL::postUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (p_camera.projectionChanged())
    {
        for (auto it : p_shader_program_usage)
        {
            it.first->use();
            it.first->setUniformMatrix4f("projection", p_camera.getProjection());
        }
    }
    if (p_camera.viewChanged())
    {
        for (auto it : p_shader_program_usage)
        {
            it.first->use();
            it.first->setUniformMatrix4f("view", p_camera.getView());
        }
    }

    glm::vec3 camera_normal = p_camera.getCenter() - p_camera.getPosition();
    glm::vec4 camera_plane(camera_normal, -(glm::dot(camera_normal, p_camera.getPosition())));

    std::multimap<double, std::pair<Drawable*, h2d::Transformation>> draw_order;
    for (Drawable* drawable : p_drawable_set)
    {
        h2d::Transformation drawable_transform = drawable->transform();
        const h2d::Kinematic* kinematic = p_drawable_kinematic[drawable];
        const h2d::Transformation* actor_transform;
        if (kinematic != nullptr)
        {
            actor_transform = new h2d::Transformation(kinematic->simulate(game().fixedUpdateLag()));
        }
        else
        {
            actor_transform = &drawable->actor().transform();
        }
        drawable_transform.x += actor_transform->x;
        drawable_transform.y += actor_transform->y;
        drawable_transform.z += actor_transform->z;
        drawable_transform.rotation += actor_transform->rotation;
        drawable_transform.scale_x *= actor_transform->scale_x;
        drawable_transform.scale_y *= actor_transform->scale_y;

        if (kinematic != nullptr)
        {
            delete actor_transform;
        }
        draw_order.insert(
                std::make_pair(
                    -glm::dot(
                        camera_plane,
                        glm::vec4(
                            drawable_transform.x,
                            drawable_transform.y,
                            drawable_transform.z,
                            1.f)
                        ),
                    std::make_pair(drawable, drawable_transform)));
    }

    for (auto it : draw_order)
    {
        Drawable* drawable = it.second.first;
        h2d::Transformation& transform = it.second.second;
        h2d_assert(drawable->shaderProgram() != nullptr, "Found a drawable without a shader program");

        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(transform.x, transform.y, transform.z));
        model = glm::rotate(model, glm::radians(static_cast<float>(transform.rotation)), glm::vec3(0., 0., 1.));
        model = glm::scale(model, glm::vec3(transform.scale_x, transform.scale_y, 1.));
        model = glm::translate(model, -drawable->getOrigin());
        drawable->shaderProgram()->use();
        drawable->shaderProgram()->setUniformMatrix4f("model", model);
        drawable->draw();
    }
    glBindVertexArray(0);
    p_window->display();
}

void MultimediaOGL::gameEnd()
{
    p_shader_program_manager->free("_mogl_plain");
    p_shader_program_manager->free("_mogl_texture");
    p_window->close();
    delete p_window;
    p_window = nullptr;
}

sf::Window* MultimediaOGL::window()
{
    return p_window;
}

const sf::Window* MultimediaOGL::window() const
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

void MultimediaOGL::setCamera(const Camera& camera)
{
    p_camera = camera;
}

const Camera& MultimediaOGL::getCamera() const
{
    return p_camera;
}

Camera& MultimediaOGL::getCamera()
{
    return p_camera;
}

ShaderProgramManager& MultimediaOGL::shaderPrograms()
{
    return *p_shader_program_manager;
}

const ShaderProgramManager& MultimediaOGL::shaderPrograms() const
{
    return *p_shader_program_manager;
}

const InputHandler& MultimediaOGL::input() const
{
    return *p_input;
}

InputHandler& MultimediaOGL::input()
{
    return *p_input;
}

TextureManager& MultimediaOGL::textures()
{
    return *p_texture_manager;
}

const TextureManager& MultimediaOGL::textures() const
{
    return *p_texture_manager;
}

SpriteAnimationManager& MultimediaOGL::spriteAnimations()
{
    return *p_sprite_animation_manager;
}

const SpriteAnimationManager& MultimediaOGL::spriteAnimations() const
{
    return *p_sprite_animation_manager;
}

SoundManager& MultimediaOGL::sounds()
{
    return *p_sound_manager;
}

const SoundManager& MultimediaOGL::sounds() const
{
    return *p_sound_manager;
}

MusicManager& MultimediaOGL::music()
{
    return *p_music_manager;
}

const MusicManager& MultimediaOGL::music() const
{
    return *p_music_manager;
}
}
