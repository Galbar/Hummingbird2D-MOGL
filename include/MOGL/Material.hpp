#ifndef MOGL_MATERIAL_HPP
#define MOGL_MATERIAL_HPP
#include "hummingbird/Vector3.hpp"

namespace mogl
{
class Material
{
public:
    Material(const hum::Vector3f& ambient_color, const hum::Vector3f& diffuse_color, const hum::Vector3f& specular_color, float specular_exponent);
    virtual ~Material();

private:
    /* data */
};
} /* mogl */
#endif /* ifndef MOGL_MATERIAL_HPP */
