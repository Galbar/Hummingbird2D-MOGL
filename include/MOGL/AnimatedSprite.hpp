#ifndef MOGL_ANIMATED_SPRITE_HPP
#define MOGL_ANIMATED_SPRITE_HPP
#include "hummingbird/hum.hpp"
#include "Sprite.hpp"

namespace mogl
{
struct SpriteAnimation
{
    sf::Texture* texture;
    int offset_x, offset_y, margin_x, margin_y, width, height;
    std::vector<unsigned int> frame_order;
    std::vector<hum::Time> frame_time;
};

class AnimatedSprite : public Sprite
{
public:
    enum class Status { PLAYING, PAUSED, STOPPED };
    AnimatedSprite(const SpriteAnimation* animation);
    const SpriteAnimation* spriteAnimation() const;
    void setSpriteAnimation(const SpriteAnimation* animation);

    void play();
    void pause();
    void stop();
    Status status() const;
    unsigned int frameIndex() const;
    void frameIndex(unsigned int frame_index);

    void setLooping(bool looping);
    bool isLooping() const;

    void draw() override;

    static const char* behaviorName();

private:
    Status p_status;
    bool p_loop;
    unsigned int p_frame_index;
    const SpriteAnimation* p_animation;
    hum::Time p_time;
};
}
#endif

