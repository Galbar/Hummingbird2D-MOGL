#ifndef MOGL_MESH_HPP
#define MOGL_MESH_HPP
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
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

    void setShaderProgram(ShaderProgram* shader_program) override;
    void draw() override;

private:
    const VertexArray* p_vertex_array;
    GLuint p_position_loc, p_normal_loc, p_uv_loc;
};
} /* mogl */

#endif /* ifndef MOGL_MESH_HPP */
