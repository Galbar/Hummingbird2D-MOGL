#include "SpriteAnimationManager.hpp"

namespace mogl
{
SpriteAnimation* SpriteAnimationManager::loadResource(const SpriteAnimation& animation)
{
    SpriteAnimation* resource = new SpriteAnimation;
    resource->texture     = animation.texture;
    resource->offset_x    = animation.offset_x;
    resource->offset_y    = animation.offset_y;
    resource->margin_x    = animation.margin_x;
    resource->margin_y    = animation.margin_y;
    resource->width       = animation.width;
    resource->height      = animation.height;
    resource->frame_order = animation.frame_order;
    resource->frame_time  = animation.frame_time;
    return resource;
}
}
