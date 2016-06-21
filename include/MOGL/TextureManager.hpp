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

/*!
  \class mogl::TextureManager
  \brief A hum::ResourceManager for sf::Texture.

  Example:
  \code
  mogl::TextureManager tm;
  tm.load("cat", "path/to/cat.jpg");
  sf::Texture* cat = tm.get("cat");

  //...

  actor.addBehavior<mogl::Sprite>(cat);

  //...

  tm.free("cat");
  \endcode
*/
}
#endif
