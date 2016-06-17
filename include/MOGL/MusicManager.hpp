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

/*!
  \class mogl::MusicManager
  \brief A hum::ResourceManager for sf::Music.

  Example:
  \code
  mogl::MusicManger mm;
  mm.load("music1", "path/to/music1.ogg");
  sf::Music* music = mm.get("music1");
  music->play();
  //...
  music->stop();
  mm.free("music1");
  \endcode
*/
}
#endif
