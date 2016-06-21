#ifndef MOGL_ANIMATED_SPRITE_HPP
#define MOGL_ANIMATED_SPRITE_HPP
#include "hummingbird/hum.hpp"
#include "Sprite.hpp"

namespace mogl
{
struct SpriteAnimation
{
    sf::Texture* texture; //!< Texture to be used
    int offset_x, //!< Horizontal offset of the tilesheet
        offset_y, //!< Vertical offset of the tilesheet
        margin_x, //!< Horizontal margin between tiles in the tilesheet
        margin_y, //!< Vertical margin between tiles in the tilesheet
        width,    //!< Width of a tile in the tilesheet
        height;   //!< Height of a tile in the tilesheet
    std::vector<unsigned int> frame_order; //!< Sequence of ids of the tiles in the tilesheet to play
    std::vector<hum::Time> frame_time; //!< Sequence of hum::Time%s for each frame in the animation
};

/*!
  \struct mogl::SpriteAnimation
  \brief A description of the animation to be played by a AnimatedSprite.
*/

class AnimatedSprite : public Sprite
{
public:
    /*!
      \enum Status
      \brief The various statuses in which an AnimatedSprite can be regarding the
      playback of an animation.
     */
    enum class Status { PLAYING, PAUSED, STOPPED };

    /*!
      \brief Class constructor with SpriteAnimation to use.

      The AnimatedSprite doesn't handle the given SpriteAnimation pointer and the pointed animation must
      exists while the AnimatedSprite is using it.

      By default, an AnimatedSprite is playing and looping.
     */
    AnimatedSprite(const SpriteAnimation* animation);

    //! Get the SpriteAnimation being used.
    const SpriteAnimation* spriteAnimation() const;
    /*!
      \brief Get the SpriteAnimation being used.

      The AnimatedSprite doesn't handle the given SpriteAnimation pointer and the pointed animation must
      exists while the AnimatedSprite is using it.
     */
    void setSpriteAnimation(const SpriteAnimation* animation);

    //! Start or continue the animation's playback.
    void play();

    //! Pause the animation's playback.
    void pause();

    //! Stop the animation's playback.
    void stop();

    //! Get the status of the playback.
    Status status() const;

    //! Get the current frame in the animation.
    unsigned int frameIndex() const;
    //! Set the current frame in the animation.
    void frameIndex(unsigned int frame_index);

    //! Set whether the animation should loop or not.
    void setLooping(bool looping);

    //! Get whether the animation is loop or not.
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

/*!
  \class mogl::AnimatedSprite
  \brief A textured rectangle-shaped 1x1 Drawable that changes over time.

  For different sizes use the scale in either the hum::Actor hum::Transform of
  the Drawable's hum::Transform.
*/
}
#endif

