#ifndef MOGL_MULTIMEDIAOGL_HPP
#define MOGL_MULTIMEDIAOGL_HPP

#include <unordered_set>
#include <unordered_map>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "hummingbird/hum.hpp"
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
/*!
  \brief Signature for a space transformation method. (see MultimediaOGL::setDrawSpaceTransform()).

  The first parameter is the instance of the hum::Game and the second is the
  hum::Transformation of the Drawable to be drawn, not the one relative to its
  hum::Actor, but the accumulated one.
 */
typedef std::function<void(const hum::Game&, hum::Transformation&)> SpaceTransformation;
void defaultSpaceTransform(const hum::Game&, hum::Transformation&);
class MultimediaOGL : public hum::Plugin
{
public:
    /*!
      \brief Class constructor

      Initializes all resource managers and the OpenGL context. but doesn't create
      the window yet.
     */
    MultimediaOGL(sf::VideoMode mode, const sf::String& title,
            sf::Uint32 style=sf::Style::Default,
            const sf::ContextSettings& settings=sf::ContextSettings());

    //! Class destructor
    virtual ~MultimediaOGL();
    virtual void gameStart() override;
    virtual void preFixedUpdate() override;
    virtual void postUpdate() override;
    virtual void gameEnd() override;

    //! Get a pointer to the window
    virtual sf::Window* window();

    //! Get a pointer to the window
    virtual const sf::Window* window() const;

    //! Register a Drawable to be drawn (Internal use only).
    virtual void addDrawable(Drawable* drawable);

    //! Register a Drawable to be drawn (Internal use only).
    virtual void removeDrawable(Drawable* drawable);

    //! Set the clear color for OpenGL
    virtual void setClearColor(const sf::Color& color);

    //! Get the clear color for OpenGL
    virtual const sf::Color& getClearColor() const;

    /*!
      \brief Set a new Camera to use.

      Usage disencouraged. Better use getCamera() and set the desired configuration
      using its setters.
     */
    virtual void setCamera(const Camera& camera);

    //! Get the Camera being used
    virtual const Camera& getCamera() const;

    //! Get the Camera being used
    virtual Camera& getCamera();

    /*!
      \brief Set the space transformation between the game logic space and the
      draw space.

      This is useful when, for example you have a game with 2D logic but you want
      to render it on a irregular terrain (height map). You can use this method
      for decoupling the 2D logic from the 3D representation.

      Another example is to draw a 2D tile based (position is always aligned with
      the tiles) game as a 2D isometric game.

      Example:
      \code

      // Supose we have a hum::Plugin for managing terrains.
      void setTerrainHeight(const hum::Game& game, hum::Transformation& r)
      {
        r.position.z = game.getPlugin<Terrains>()->getCurrent().height(r.position.x, r.position.y);
      }

      //...

      game().getPlugin<mogl::MultimediaOGL>()->setDrawSpaceTransform(setTerrainHeight);
      \endcode
     */
    virtual void setDrawSpaceTransform(const SpaceTransformation& space_transform);

    /*!
      @{
      \name Resource Managers
     */

    //! Get the ShaderProgramManager
    ShaderProgramManager& shaderPrograms();

    //! Get the ShaderProgramManager
    const ShaderProgramManager& shaderPrograms() const;

    //! Get the InputHandler
    InputHandler& input();

    //! Get the InputHandler
    const InputHandler& input() const;

    //! Get the SpriteAnimationManager
    SpriteAnimationManager& spriteAnimations();

    //! Get the SpriteAnimationManager
    const SpriteAnimationManager& spriteAnimations() const;

    //! Get the TextureManager
    TextureManager& textures();

    //! Get the TextureManager
    const TextureManager& textures() const;

    //! Get the SoundManager
    SoundManager& sounds();

    //! Get the SoundManager
    const SoundManager& sounds() const;

    //! Get the MusicManager
    MusicManager& music();

    //! Get the MusicManager
    const MusicManager& music() const;

    //! @}

private:
    struct DrawOrder_t {
        double order;
        hum::Transformation transform;
        Drawable* drawable;
    };

    sf::VideoMode p_mode;
    sf::String p_title;
    sf::Uint32 p_style;
    sf::ContextSettings p_settings;
    sf::Color p_clear_color;
    Camera p_camera;
    SpaceTransformation p_space_transform;
    sf::Context p_context;
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

/*!
  \class mogl::MultimediaOGL
  \brief Plugin that handles all the rendering pipeline, input and resource
  managment.

  The MultimediaOGL plugin is the class that groups all the functionalities
  included in MOGL and makes them accessible in the hum::Game.

  Rendering
  =========

  The plugin handles the creation of the sf::Window and the OpenGL context.
  The window is made accessible through window().

  The plugin also handles the camera, that is accessible by calling getCamera().
  To set and get the clear color setClearColor() and getClearColor() can be
  called.

  The rendering of all active and enabled Drawables happens at every postUpdate.
  This may seem anti-intuitive because the position of the Actors is only updated
  every fixedUpdate (we'd be drawing the same frame multiple times), but
  MultimediaOGL does something smart: for all Drawables whose Actors have a
  hum::Kinematic behavior, the position of the Drawable will be interpolated using
  the kinematic information and the fixedUpdateLag. Also, AnimatedSprites's animation
  is also updated when drawn. This way we can have a smooth as posible view of the
  game world and a fixedUpdate for the game logic.

  Finally, a game space -> draw space transformation can be set by using
  setDrawSpaceTransform(), for more details see the mehtod's details.

  Resource Management
  ===================

  The MultimediaOGL plugin owns an instance of each of the resource managers
  included with MOGL. This way one can access any of them at any point inside the
  game.

  Example:
  \code
  class Player : public hum::Behavior
  {
  private:
    hum::Kinematic* k;
    mogl::AnimatedSprite* spr;
    mogl::SoundId sound_id;
    mogl::MultimediaOGL* mogl;
  public:
    void init() override
    {
      sound_id = 0;
      mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
      k = actor().getBehavior<hum::Kinematic>();
      spr = actor().getBehavior<mogl::AnimatedSprite>();
      spr->setSpriteAnimation(mogl->spriteAnimations().get("player_idle"));
    }

    void fixedUpdate() override
    {
      ...
      if (k->velocity().x != 0 || k->velocity().y != 0)
      {
        auto anim = mogl->spriteAnimations().get("player_walking");
        if (anim != spr->spriteAnimation())
            spr->setSpriteAnimation(anim);
        if (mogl->sounds().get(sound_id) == nullptr)
        {
          sound_id = mogl->sounds()->play("steps", 75, true);
        }
      }
      else
      {
        auto anim = mogl->spriteAnimations().get("player_idle");
        if (anim != spr->spriteAnimation())
            spr->setSpriteAnimation(anim);
        if (mogl->sounds().get(sound_id) != nullptr)
        {
          mogl->sounds()->get(sound_id)->stop();
        }
      }
    }
  }
  \endcode
 */
}
#endif
