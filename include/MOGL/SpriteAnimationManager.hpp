#ifndef H2D_SPRITE_ANIMATION_HPP
#define H2D_SPRITE_ANIMATION_HPP
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "hummingbird/Time.hpp"
#include "hummingbird/ResourceManager.hpp"
#include "AnimatedSprite.hpp"

namespace mogl
{
class SpriteAnimationManager : public hum::ResourceManager<SpriteAnimation, std::string, SpriteAnimation>
{
    SpriteAnimation* loadResource(const SpriteAnimation& animation) override;
};


/*!
  \class mogl::SpriteAnimationManager
  \brief A hum::ResourceManager for mogl::SpriteAnimation%s.

  This Resource manager is different because it uses SpriteAnimation%s as the
  data to "load" and stores a copy of the given SpriteAnimation.

  Example:
  \code
  mogl::SpriteAnimation jump{
    game().getPlugin<mogl::MultimediaOGL>()->textures().get("player"),
    0, 0, 0, 0, 48, 48,
    {5, 6, 7, 8},
    std::vector(4, hum::Time::seconds(0.3f))
  };

  mogl::SpriteAnimationManager sam;
  sam.load("player_jump", jump);

  //...

  actor.addBehavior<mogl::AnimatedSprite>(sam.get("player_jump"));

  //...

  sam.free("player_jump");
  \endcode
*/
}
#endif
