#ifndef H2B_SOUNDBUFFER_MANAGER_HPP
#define H2B_SOUNDBUFFER_MANAGER_HPP
#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "hummingbird/ResourceManager.hpp"

namespace mogl
{
typedef unsigned int SoundId;
typedef std::pair<SoundId, sf::Sound*> SoundPair;
class SoundManager : public hum::ResourceManager<sf::SoundBuffer>
{
public:
    //! Class constructor
    SoundManager();

    //! Class destructor
    ~SoundManager();

    /*!
      \brief Play a sound.

      Starts playing the sf::SoundBuffer identified by <name> with the given
      <volume>. It allows to set the sound to loop, whether the sound is relative
      to the listener and the initial position of the sound.

      To set the position of the listener you may use:
      `sf::Listener::setPosition(x, y, z);`

      For sounds with varying positions, you may do the following:
      \code
      // fixedUpdate
      auto sm = actor().game().getPlugin<mogl::MultimediaOGL>()->sounds();
      sf::Sound* sound = sm->get(sound_id);
      if (sound != nullptr)
      {
        sound->setPosition(actor().transform().x, actor().transform().y, actor().transform().z);
      }
      \endcode

      Note that the validity of a sf::Sound pointer obtained by play() or get()
      is not guaranteed between update cycles of the game. (They might get
      invalidated by clearSounds()).

      \return a std::pair containig a SoundId (unsigned int) and a pointer to
      the sf::Sound that is playing the sf::SoundBuffer.
     */
    SoundPair play(const std::string& name, int volume, bool loop = false,
            bool relative_to_listener = false, const sf::Vector3f& position = sf::Vector3f());

    /*!
      \brief Get a sound resource by id.

      If the sound resource does not exists, as in it has been freed because the
      playback of the SoundBuffer is done, it returns nullptr.
     */
    sf::Sound* get(SoundId sound_id);

    /*!
      \brief Get a sound resource by id.

      If the sound resource does not exists, as in it has been freed because the
      playback of the SoundBuffer is done, it returns nullptr.
     */
    const sf::Sound* get(SoundId sound_id) const;

    /*!
      \brief Clear sound resources that are done playing.

      This is called every preFixedUpdate and cleans all sounds that are done
      playing the sf::SoundBuffer they were required to play.
     */
    void clearSounds();

protected:
    sf::SoundBuffer* loadResource(const std::string& name) override;

private:
    unsigned int p_count;
    std::vector<SoundPair> p_sounds;
    std::queue<unsigned int> p_free_sounds;
    std::unordered_map<SoundId, unsigned int> p_positions;
};


/*!
  \class mogl::SoundManager
  \brief A hum::ResourceManager for sf::SoundBuffer%s.

  This Resource manager is different because it overwrites the get() method and
  has other extra methods.

  The SoundManager not just loads sf::SoundBuffers but also allows to play them
  through the method play(). This method returns a std::pair containing the
  id of the sound resource used (the one that is playing the required
  sf::SoundBuffer) and a pointer to the sf::Sound managing the playback of the
  sf::SoundBuffer. Note that a _sound resource_ is not the same as a sf::SoundBuffer.

  The get() methods are also different. In this manager they are accessed by
  sound ids (which are returned by play) and they return a pointer of the given
  sf::Sound, or nullptr if the sound has been freed.

  Example:
  \code
  mogl::SoundManager sm;
  sm.load("roar", "path/to/roar.ogg");

  //...


  // fixedUpdate()
  if (event)
  {
    roar_id = sm.play("roar", 50).first; // start playing the "roar" sound
  }
  // onDestroy()
  if (sm.get(roar_id) != nullptr) // if the sound is still playing
  {
    sm.get(roar_id)->stop(); // stop it
  }

  //...

  sm.free("roar");
  \endcode

  As shown in the example, when a sf::SoundBuffer playback is done (Stopped),
  then the _sound resource_ is cleared and therefore the sound id invalidated
  (getting its related sound returns nullptr).

  Sound ids start at 1 and always grow, that means that a sound id of 0 will
  always return nullptr.
*/
}
#endif
