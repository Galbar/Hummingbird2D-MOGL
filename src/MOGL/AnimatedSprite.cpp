#include "Hum2D/Log.hpp"
#include "AnimatedSprite.hpp"

namespace mogl
{
AnimatedSprite::AnimatedSprite(int width, int height, const SpriteAnimation* animation):
Sprite(width, height, animation->texture),
p_loop(true)
{
    setSpriteAnimation(animation);
    p_status = Status::PLAYING;
}

void AnimatedSprite::setSpriteAnimation(const SpriteAnimation* animation)
{
    p_animation = animation;
    setTexture(animation->texture);
    p_time = h2d::Time::nanoseconds(0);
    p_frame_index = 0;
    int top, left, idx, sheet_width;
    sheet_width = p_animation->texture->getSize().x - p_animation->offset_x;
    idx = p_animation->frame_order[p_frame_index];
    left = idx * (p_animation->margin_x + p_animation->width);
    top = p_animation->offset_y + (p_animation->margin_y + p_animation->height) * (left / sheet_width);
    left = (left % sheet_width) + p_animation->offset_x;

    setTextureRect(sf::IntRect(left, top, p_animation->width, p_animation->height));
}

const SpriteAnimation* AnimatedSprite::spriteAnimation() const
{
    return p_animation;
}

void AnimatedSprite::draw()
{
    if (p_status == Status::PLAYING)
    {
        p_time += actor().game().deltaTime();
        while (p_time > p_animation->frame_time[p_frame_index])
        {
            p_time -= p_animation->frame_time[p_frame_index];
            ++p_frame_index;
            if (p_frame_index == p_animation->frame_time.size())
            {
                if (p_loop)
                {
                    p_frame_index %= p_animation->frame_time.size();
                }
                else
                {
                    --p_frame_index;
                    p_status = Status::STOPPED;
                }
            }
        }
        int top, left, idx, sheet_width;
        sheet_width = p_animation->texture->getSize().x - p_animation->offset_x;
        idx = p_animation->frame_order[p_frame_index];
        left = idx * (p_animation->margin_x + p_animation->width);
        top = p_animation->offset_y + (p_animation->margin_y + p_animation->height) * (left / sheet_width);
        left = (left % sheet_width) + p_animation->offset_x;

        setTextureRect(sf::IntRect(left, top, p_animation->width, p_animation->height));
    }
    Sprite::draw();
}

void AnimatedSprite::play()
{
    p_status = Status::PLAYING;
}

void AnimatedSprite::pause()
{
    p_status = Status::PAUSED;
}

void AnimatedSprite::stop()
{
    p_status = Status::STOPPED;
    p_frame_index = 0;
}

AnimatedSprite::Status AnimatedSprite::status() const
{
    return p_status;
}

unsigned int AnimatedSprite::frameIndex() const
{
    return p_frame_index;
}

void AnimatedSprite::frameIndex(unsigned int frame_index)
{
    p_frame_index = frame_index % p_animation->frame_time.size();
    p_time -= p_time;
}

void AnimatedSprite::setLooping(bool looping)
{
    p_loop = looping;
}

bool AnimatedSprite::isLooping() const
{
    return p_loop;
}

const char* AnimatedSprite::behaviorName()
{
    return "mogl::AnimatedSprite";
}
}
