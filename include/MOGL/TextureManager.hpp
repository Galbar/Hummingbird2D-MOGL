#ifndef H2B_TEXTURE_MANAGER_HPP
#define H2B_TEXTURE_MANAGER_HPP
#include <SFML/Graphics.hpp>
#include "hummingbird/ResourceManager.hpp"

namespace mogl
{
class TextureManager : public hum::ResourceManager<sf::Texture>
{
protected:
    sf::Texture* loadResource(const std::string& name) override;
};
}
#endif
