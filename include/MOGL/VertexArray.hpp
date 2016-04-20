#ifndef MOGL_VERTEX_ARRAY_HPP
#define MOGL_VERTEX_ARRAY_HPP
#include <string>
#include <utility>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "Model.hpp"
#include "hummingbird/hum.hpp"

namespace mogl
{
class VertexArray
{
public:
    VertexArray();
    virtual ~VertexArray();

    unsigned int getNumFaces() const;
    unsigned int getNumVertices() const;
    const std::pair<hum::Vector3f, hum::Vector3f>& getBoundingBox() const;

    bool loadFromFile(const std::string& filename);
    bool loadFromModel(const Model& model);

    unsigned int getNativeHandle() const;

private:
    GLuint p_VAO, p_VBO;
    unsigned int p_num_vertices, p_num_faces;
    std::pair<hum::Vector3f, hum::Vector3f> p_bb;
};
} /* mogl */
#endif /* ifndef MOGL_VERTEX_ARRAY_HPP */
