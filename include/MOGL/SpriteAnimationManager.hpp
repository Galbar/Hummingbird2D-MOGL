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
}
#endif
