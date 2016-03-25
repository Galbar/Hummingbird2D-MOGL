#include "SoundManager.hpp"

namespace mogl
{
SoundManager::SoundManager():
    p_count(1)
{}

SoundManager::~SoundManager()
{
    for (auto& e : p_sounds)
    {
        delete e.second;
    }
}

Sound_t SoundManager::play(const std::string& name, int volume, bool loop, bool relative_to_listener, const sf::Vector3f& position)
{
    SoundId sound_id = p_count++;
    unsigned int pos;
    if (p_free_sounds.empty())
    {
        p_sounds.emplace_back();
        pos = p_sounds.size() -1;
        p_sounds[pos].second = new sf::Sound();
    }
    else
    {
        pos = p_free_sounds.front();
        p_free_sounds.pop();
    }
    p_positions.insert(std::make_pair(sound_id, pos));
    auto it = p_sounds.begin() + pos;
    it->first = sound_id;
    it->second->setBuffer(*ResourceManager<sf::SoundBuffer>::get(name));
    it->second->setPosition(position);
    it->second->setVolume(volume);
    it->second->setLoop(loop);
    it->second->setRelativeToListener(relative_to_listener);
    it->second->play();
    return *it;
}

sf::Sound* SoundManager::get(SoundId sound_id)
{
    auto it = p_positions.find(sound_id);
    if (it == p_positions.end())
    {
        return nullptr;
    }

    unsigned int pos = it->second;
    auto vit = p_sounds.begin() + pos;
    return vit->second;
}

const sf::Sound* SoundManager::get(SoundId sound_id) const
{
    auto it = p_positions.find(sound_id);
    if (it == p_positions.end())
    {
        return nullptr;
    }

    unsigned int pos = it->second;
    auto vit = p_sounds.begin() + pos;
    return vit->second;
}

void SoundManager::clearSounds()
{
    for (unsigned int i = 0; i < p_sounds.size(); ++i)
    {
        sf::Sound* sound = p_sounds[i].second;
        if (sound->getStatus() == sf::Sound::Stopped
                and p_positions.find(p_sounds[i].first) != p_positions.end())
        {
            p_free_sounds.push(i);
            p_positions.erase(p_sounds[i].first);
        }
    }
}

sf::SoundBuffer* SoundManager::loadResource(const std::string& name)
{
    sf::SoundBuffer* resource = new sf::SoundBuffer();
    if (resource->loadFromFile(name))
    {
        return resource;
    }
    delete resource;
    return nullptr;
}
}
