#ifndef MOGL_MESH_HPP
#define MOGL_MESH_HPP
#include "hummingbird/hum.hpp"
#include "Drawable.hpp"
#include "VertexArray.hpp"

namespace mogl
{
class Mesh : public Drawable
{
public:
    Mesh(const VertexArray& vertex_array);
    virtual ~Mesh ();

private:
    VertexArray* p_vertex_array;
};
} /* mogl */

#endif /* ifndef MOGL_MESH_HPP */
