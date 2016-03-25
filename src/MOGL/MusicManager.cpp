#include "MusicManager.hpp"

namespace mogl
{
sf::Music* MusicManager::loadResource(const std::string& name)
{
    sf::Music* resource = new sf::Music();
    if (resource->openFromFile(name))
    {
        return resource;
    }
    delete resource;
    return nullptr;
}
}
