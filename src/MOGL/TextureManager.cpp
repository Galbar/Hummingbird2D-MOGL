#include "TextureManager.hpp"

namespace mogl
{
sf::Texture* TextureManager::loadResource(const std::string& name)
{
    sf::Texture* resource = new sf::Texture();
    if (not resource->loadFromFile(name))
        return nullptr;
    return resource;
}
}
