#include "TextureManager.hpp"

namespace mogl
{
sf::Texture* TextureManager::loadResource(const std::string& name)
{
    sf::Texture* resource = new sf::Texture();
    if (resource->loadFromFile(name))
    {
        return resource;
    }
    delete resource;
    return nullptr;
}
}
