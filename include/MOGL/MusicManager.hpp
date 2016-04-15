#ifndef H2B_MUSIC_MANAGER_HPP
#define H2B_MUSIC_MANAGER_HPP
#include <SFML/Audio.hpp>
#include "hummingbird/ResourceManager.hpp"

namespace mogl
{
class MusicManager : public hum::ResourceManager<sf::Music>
{
protected:
    sf::Music* loadResource(const std::string& name) override;
};
}
#endif
