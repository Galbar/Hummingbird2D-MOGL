#ifndef MOGL_MULTIMEDIAOGL_HPP
#define MOGL_MULTIMEDIAOGL_HPP

#include <unordered_set>
#include <unordered_map>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "glm.hpp"
#include "hummingbird/hum.hpp"
#include "hummingbird/Plugin.hpp"
#include "TextureManager.hpp"
#include "SpriteAnimationManager.hpp"
#include "SoundManager.hpp"
#include "MusicManager.hpp"
#include "InputHandler.hpp"
#include "ShaderProgramManager.hpp"
#include "Drawable.hpp"
#include "Camera.hpp"

namespace mogl
{
typedef std::function<void(hum::Transformation&)> SpaceTransformation;
void defaultSpaceTransform(hum::Transformation& r);
class MultimediaOGL : public hum::Plugin
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

    virtual void setClearColor(const sf::Color& color);
    virtual const sf::Color& getClearColor() const;

    virtual void setCamera(const Camera& camera);
    virtual const Camera& getCamera() const;
    virtual Camera& getCamera();

    // Requires the instance to exist as it only takes the pointer
    virtual void setDrawSpaceTransform(const SpaceTransformation& space_transform);

    ShaderProgramManager& shaderPrograms();
    const ShaderProgramManager& shaderPrograms() const;
    InputHandler& input();
    const InputHandler& input() const;
    SpriteAnimationManager& spriteAnimations();
    const SpriteAnimationManager& spriteAnimations() const;
    TextureManager& textures();
    const TextureManager& textures() const;
    SoundManager& sounds();
    const SoundManager& sounds() const;
    MusicManager& music();
    const MusicManager& music() const;

private:
    sf::VideoMode p_mode;
    sf::String p_title;
    sf::Uint32 p_style;
    sf::ContextSettings p_settings;
    sf::Color p_clear_color;
    Camera p_camera;
    SpaceTransformation p_space_transform;
    sf::Window* p_window;
    std::unordered_set<Drawable*> p_drawable_set;
    std::unordered_map<ShaderProgram*, unsigned int> p_shader_program_usage;
    std::unordered_map<Drawable*, const hum::Kinematic*> p_drawable_kinematic;
    InputHandler* p_input;
    ShaderProgramManager* p_shader_program_manager;
    TextureManager* p_texture_manager;
    SpriteAnimationManager* p_sprite_animation_manager;
    MusicManager* p_music_manager;
    SoundManager* p_sound_manager;
};
}
#endif
