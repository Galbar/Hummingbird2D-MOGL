#ifndef H2B_SOUNDBUFFER_MANAGER_HPP
#define H2B_SOUNDBUFFER_MANAGER_HPP
#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "Hum2D/ResourceManager.hpp"

namespace mogl
{
typedef unsigned int SoundId;
typedef std::pair<SoundId, sf::Sound*> Sound_t;
class SoundManager : public h2d::ResourceManager<sf::SoundBuffer>
{
public:
    SoundManager();
    ~SoundManager();
    Sound_t play(const std::string& name, int volume, bool loop = false, bool relative_to_listener = false, const sf::Vector3f& position = sf::Vector3f());
    sf::Sound* get(SoundId sound_id);
    const sf::Sound* get(SoundId sound_id) const;
    void clearSounds();

protected:
    sf::SoundBuffer* loadResource(const std::string& name) override;

private:
    unsigned int p_count;
    std::vector<Sound_t> p_sounds;
    std::queue<unsigned int> p_free_sounds;
    std::unordered_map<SoundId, unsigned int> p_positions;
};
}
#endif
