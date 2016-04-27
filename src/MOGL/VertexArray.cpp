#include "VertexArray.hpp"

namespace mogl
{
VertexArray::VertexArray():
p_VAO(0),
p_VBO(0),
p_num_vertices(0),
p_num_faces(0),
p_bb(std::make_pair(hum::Vector3f(0.f), hum::Vector3f(0.f)))
{}

VertexArray::~VertexArray()
{
    if (p_VBO != 0)
    {
        glDeleteBuffers(1, &p_VBO);
    }
    if (p_VAO != 0)
    {
        glDeleteVertexArrays(1, &p_VAO);
    }
}

unsigned int VertexArray::getNumFaces() const
{
    return p_num_faces;
}

unsigned int VertexArray::getNumVertices() const
{
    return p_num_vertices;
}

const std::pair<hum::Vector3f, hum::Vector3f>& VertexArray::getBoundingBox() const
{
    return p_bb;
}

bool VertexArray::loadFromFile(const std::string& filename)
{
    Model model;
    if (model.loadFromFile(filename))
    {
        return loadFromModel(model);
    }
    return false;
}

bool VertexArray::loadFromModel(const Model& model)
{
    // Each face has (3 vertices + 3 normals) * 3 floats + (3 uv_coords) * 2 floats
    int N = model.getFaces().size() * 24;
    if (N == 0)
    {
        hum::log("Loading VertexArray from empty model, not doing it.");
        return false;
    }
    float info[N];

    for (unsigned int i = 0; i < model.getFaces().size(); ++i) // for face in model
    {
        const Model::Face& face = model.getFaces()[i];
        for (unsigned int j = 0; j < 3; ++j) // for vertex in face
        {
            unsigned int v_pos = 24 * i + 8 * j;

            const hum::Vector3f& position = model.getVertices()[face.vertices[j]];
            hum::Vector3f normal(0.f);
            if (face.normals[j] != -1)
            {
                normal = model.getNormals()[face.normals[j]];
            }

            for (unsigned int k = 0; k < 3; ++k) // floats
            {
                int x = k + v_pos;
                info[x]   = position[k];
                info[x+3] = normal[k];
            }

            hum::Vector2f uv(0.f);
            if (face.uv_coords[j] != -1)
            {
                uv = model.getUVCoords()[face.uv_coords[j]];
            }
            for (unsigned int k = 0; k < 2; ++k) // floats
            {
                info[v_pos + 6 + k] = uv[k];
            }
        }
    }

    p_num_faces = model.getFaces().size();
    p_num_vertices = model.getVertices().size();

    model.getBoundingBox(p_bb.first, p_bb.second);

    glGenVertexArrays(1, &p_VAO);
    glBindVertexArray(p_VAO);
    glGenBuffers(1, &p_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
    glBufferData(GL_ARRAY_BUFFER, N * sizeof(float), info, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

VertexArray::VertexArray_t VertexArray::getNativeHandles() const
{
    return VertexArray_t{p_VAO, p_VBO};
}
} /* mogl */
