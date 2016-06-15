#include "MultimediaOGL.hpp"
#include "glm.hpp"

namespace mogl
{
void defaultSpaceTransform(hum::Transformation& r)
{}

MultimediaOGL::MultimediaOGL(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings):
p_mode(mode),
p_title(title),
p_style(style),
p_settings(settings),
p_clear_color(sf::Color::Black),
p_space_transform(defaultSpaceTransform),
p_window(nullptr),
p_input(new InputHandler()),
p_shader_program_manager(new ShaderProgramManager()),
p_texture_manager(new TextureManager()),
p_sprite_animation_manager(new SpriteAnimationManager()),
p_music_manager(new MusicManager()),
p_sound_manager(new SoundManager())
{
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 1);
}

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

    Shader *v_shader, *f_shader;
    v_shader = new Shader();
    v_shader->loadFromSource(Shader::Type::VERTEX_SHADER,
#include "../../shaders/plain.vert"
    );
    hum::assert_msg(v_shader->isCompiled(), "Error compiling plain.vert\n" + v_shader->log());

    f_shader = new Shader();
    f_shader->loadFromSource(Shader::Type::FRAGMENT_SHADER,
#include "../../shaders/plain.frag"
    );
    hum::assert_msg(f_shader->isCompiled(), "Error compiling plain.frag\n" + f_shader->log());

    p_shader_program_manager->load("_mogl_plain", ShaderProgramDef{*v_shader, *f_shader, "out_color"});

    delete v_shader;
    delete f_shader;

    v_shader = new Shader();
    v_shader->loadFromSource(Shader::Type::VERTEX_SHADER,
#include "../../shaders/texture.vert"
    );
    hum::assert_msg(v_shader->isCompiled(), "Error compiling plain.vert\n" + v_shader->log());


    f_shader = new Shader();
    f_shader->loadFromSource(Shader::Type::FRAGMENT_SHADER,
#include "../../shaders/texture.frag"
    );
    hum::assert_msg(f_shader->isCompiled(), "Error compiling plain.frag\n" + f_shader->log());

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

    glm::vec3 camera_position = humToGlm(p_camera.getPosition());
    glm::vec3 camera_normal = humToGlm(p_camera.getCenter()) - camera_position;
    glm::vec4 camera_plane(camera_normal, -(glm::dot(camera_normal, camera_position)));

    std::vector<DrawOrder_t> draw_order;
    for (Drawable* drawable : p_drawable_set)
    {
        hum::Transformation drawable_transform = drawable->transform();
        const hum::Kinematic* kinematic = p_drawable_kinematic[drawable];
        const hum::Transformation* actor_transform;
        if (kinematic != nullptr)
        {
            actor_transform = new hum::Transformation(kinematic->simulate(game().fixedUpdateLag()));
        }
        else
        {
            actor_transform = &drawable->actor().transform();
        }
        drawable_transform = drawable_transform.transform(*actor_transform);

        if (kinematic != nullptr)
        {
            delete actor_transform;
        }

        p_space_transform(drawable_transform);

        double distance_from_camera = glm::dot(
                camera_plane,
                glm::vec4(
                    drawable_transform.position.x,
                    drawable_transform.position.y,
                    drawable_transform.position.z,
                    1.f)
                );
        if (distance_from_camera <= p_camera.getZFar() && distance_from_camera >= p_camera.getZNear())
        {
            draw_order.push_back(DrawOrder_t{distance_from_camera, drawable_transform, drawable});
        }
    }

    std::sort(draw_order.begin(), draw_order.end(), [](const DrawOrder_t& left, const DrawOrder_t& right) { return left.order > right.order; });

    for (DrawOrder_t& value : draw_order)
    {
        Drawable* drawable = value.drawable;
        hum::assert_msg(drawable != nullptr, "Found a drawable nullptr");
        hum::Transformation& transform = value.transform;
        hum::assert_msg(drawable->shaderProgram() != nullptr, "Found a drawable without a shader program");

        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(transform.position.x, transform.position.y, transform.position.z));
        model = glm::rotate(model, glm::radians(static_cast<float>(transform.rotation.x)), glm::vec3(1., 0., 0.));
        model = glm::rotate(model, glm::radians(static_cast<float>(transform.rotation.y)), glm::vec3(0., 1., 0.));
        model = glm::rotate(model, glm::radians(static_cast<float>(transform.rotation.z)), glm::vec3(0., 0., 1.));
        model = glm::scale(model, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));
        glm::vec3 origin(drawable->getOrigin().x, drawable->getOrigin().y, drawable->getOrigin().z);
        model = glm::translate(model, -origin);
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
        p_drawable_kinematic[drawable] = drawable->actor().getBehavior<hum::Kinematic>();
    }
    catch (hum::exception::BehaviorNotFound e)
    {
        p_drawable_kinematic[drawable] = nullptr;
    }

    if (drawable->shaderProgram())
    {
        if (p_shader_program_usage.find(drawable->shaderProgram()) == p_shader_program_usage.end())
        {
            p_shader_program_usage.insert(std::make_pair(drawable->shaderProgram(), 0));
            drawable->shaderProgram()->use();
            drawable->shaderProgram()->setUniformMatrix4f("projection", p_camera.getProjection());
            drawable->shaderProgram()->setUniformMatrix4f("view", p_camera.getView());
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

void MultimediaOGL::setClearColor(const sf::Color& color)
{
    p_clear_color = color;
    glClearColor(
            static_cast<float>(color.r)/255.f,
            static_cast<float>(color.g)/255.f,
            static_cast<float>(color.b)/255.f,
            1);
}
const sf::Color& MultimediaOGL::getClearColor() const
{
    return p_clear_color;
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

void MultimediaOGL::setDrawSpaceTransform(const SpaceTransformation& space_transform)
{
    p_space_transform = space_transform;
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
