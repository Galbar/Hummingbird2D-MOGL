#ifndef MOGL_MODEL_HPP
#define MOGL_MODEL_HPP
#include <vector>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <regex>
#include "hummingbird/hum.hpp"

namespace mogl
{
class Model
{
public:
    struct Face {
        hum::Vector3i vertices;
        hum::Vector3i normals;
        hum::Vector3i uv_coords;
    };
    Model();
    virtual ~Model();

    const std::vector<hum::Vector3f>& getVertices() const;
    const std::vector<hum::Vector3f>& getNormals() const;
    const std::vector<hum::Vector2f>& getUVCoords() const;
    const std::vector<Face>& getFaces() const;
    std::vector<hum::Vector3f>& getVertices();
    std::vector<hum::Vector3f>& getNormals();
    std::vector<hum::Vector2f>& getUVCoords();
    std::vector<Face>& getFaces();

    void getBoundingBox(hum::Vector3f& min, hum::Vector3f& max) const;

    bool loadFromString(const std::string& source);
    bool loadFromStream(std::istream& stream);
    bool loadFromFile(const std::string& filename);

private:
    std::vector<hum::Vector3f> p_vertices;
    std::vector<hum::Vector3f> p_normals;
    std::vector<hum::Vector2f> p_uv_coords;
    std::vector<Face> p_faces;
};
} /* mogl */
#endif /* ifndef MOGL_MODEL_HPP */
