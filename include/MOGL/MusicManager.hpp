#ifndef H2B_MUSIC_MANAGER_HPP
#define H2B_MUSIC_MANAGER_HPP
#include <SFML/Audio.hpp>
#include "Hum2D/ResourceManager.hpp"

namespace mogl
{
class MusicManager : public h2d::ResourceManager<sf::Music>
{
protected:
    sf::Music* loadResource(const std::string& name) override;
};
}
#endif
