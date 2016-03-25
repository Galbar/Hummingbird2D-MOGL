#ifndef H2D_SPRITE_ANIMATION_HPP
#define H2D_SPRITE_ANIMATION_HPP
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Hum2D/Time.hpp"
#include "Hum2D/ResourceManager.hpp"
#include "AnimatedSprite.hpp"

namespace mogl
{
class SpriteAnimationManager : public h2d::ResourceManager<SpriteAnimation, std::string, SpriteAnimation>
{
    SpriteAnimation* loadResource(const SpriteAnimation& animation) override;
};
}
#endif
