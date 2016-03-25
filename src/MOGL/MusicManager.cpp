#include "MusicManager.hpp"

namespace mogl
{
sf::Music* MusicManager::loadResource(const std::string& name)
{
    sf::Music* resource = new sf::Music();
    if (not resource->openFromFile(name))
        return nullptr;
    return resource;
}
}
