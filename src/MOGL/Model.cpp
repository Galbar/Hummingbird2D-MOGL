#include "Model.hpp"

namespace mogl
{
Model::Model()
{}

Model::~Model()
{}


const std::vector<hum::Vector3f>& Model::getVertices() const
{
    return p_vertices;
}

const std::vector<hum::Vector3f>& Model::getNormals() const
{
    return p_normals;
}

const std::vector<hum::Vector2f>& Model::getUVCoords() const
{
    return p_uv_coords;
}

const std::vector<Model::Face>& Model::getFaces() const
{
    return p_faces;
}

std::vector<hum::Vector3f>& Model::getVertices()
{
    return p_vertices;
}

std::vector<hum::Vector3f>& Model::getNormals()
{
    return p_normals;
}

std::vector<hum::Vector2f>& Model::getUVCoords()
{
    return p_uv_coords;
}

std::vector<Model::Face>& Model::getFaces()
{
    return p_faces;
}

void Model::getBoundingBox(hum::Vector3f& min, hum::Vector3f& max) const
{
    if (p_vertices.size() == 0)
    {
        min = hum::Vector3f(0.f); max = hum::Vector3f(0.f);
        return;
    }

    min = p_vertices[0]; max = p_vertices[0];

    for (unsigned int i = 1; i < p_vertices.size(); ++i)
    {
        min.x = (min.x < p_vertices[i].x) ? min.x : p_vertices[i].x;
        min.y = (min.y < p_vertices[i].y) ? min.y : p_vertices[i].y;
        min.z = (min.z < p_vertices[i].z) ? min.z : p_vertices[i].z;
        max.x = (max.x > p_vertices[i].x) ? max.x : p_vertices[i].x;
        max.y = (max.y > p_vertices[i].y) ? max.y : p_vertices[i].y;
        max.z = (max.z > p_vertices[i].z) ? max.z : p_vertices[i].z;
    }
}

bool Model::loadFromString(const std::string& source)
{
    std::stringstream ss(source);
    return loadFromStream(ss);
}

bool Model::loadFromFile(const std::string& filename)
{
    std::ifstream file;
    file.open(filename.c_str());
    if (!file.is_open())
    {
        hum::log("Could not open file '" + filename + "'.");
        return false;
    }
    bool success = loadFromStream(file);
    file.close();
    return success;
}

bool Model::loadFromStream(std::istream& stream)
{
    std::regex re_vert("v (-?\\d+(?:\\.\\d+|)) (-?\\d+(?:\\.\\d+|)) (-?\\d+(?:\\.\\d+|))(?: (-?\\d+(?:\\.\\d+|)))?");
    std::regex re_uv("vt (-?\\d+(?:\\.\\d+|)) (-?\\d+(?:\\.\\d+|))(?: (-?\\d+(?:\\.\\d+|)))?");
    std::regex re_normal("vn (-?\\d+(?:\\.\\d+|)) (-?\\d+(?:\\.\\d+|)) (-?\\d+(?:\\.\\d+|))");
    std::regex re_face("f (\\d+)(?:/(\\d+|)(?:/(\\d+|))?)? (\\d+)(?:/(\\d+|)(?:/(\\d+|))?)? (\\d+)(?:/(\\d+|)(?:/(\\d+|))?)?");

    std::smatch sm;
    std::string line;
    bool success = true;
    while (std::getline(stream, line))
    {
        if (line.size() == 0 || line[0] == '#') continue;
        if (std::regex_match(line, sm, re_vert))
        {
            hum::Vector3f vertex(0.f);
            vertex.x = std::stof(sm[1]);
            vertex.y = std::stof(sm[2]);
            vertex.z = std::stof(sm[3]);
            p_vertices.push_back(vertex);
        }
        else if (std::regex_match(line, sm, re_uv))
        {
            hum::Vector2f uv(0.f);
            uv.x = std::stof(sm[1]);
            uv.y = std::stof(sm[2]);
            p_uv_coords.push_back(uv);
        }
        else if (std::regex_match(line, sm, re_normal))
        {
            hum::Vector3f normal(0.f);
            normal.x = std::stof(sm[1]);
            normal.y = std::stof(sm[2]);
            normal.z = std::stof(sm[3]);
            p_normals.push_back(normal);
        }
        else if (std::regex_match(line, sm, re_face))
        {
            hum::Vector3i vertices(-1);
            hum::Vector3i normals(-1);
            hum::Vector3i uv_coords(-1);

            vertices.x = std::stoi(sm[1])-1;
            vertices.y = std::stoi(sm[4])-1;
            vertices.z = std::stoi(sm[7])-1;

            if (sm[2].length() != 0)
            {
                normals.x = std::stoi(sm[2])-1;
            }
            if (sm[5].length() != 0)
            {
                normals.y = std::stoi(sm[5])-1;
            }
            if (sm[8].length() != 0)
            {
                normals.z = std::stoi(sm[8])-1;
            }

            if (sm[3].length() != 0)
            {
                uv_coords.x = std::stoi(sm[3])-1;
            }
            if (sm[6].length() != 0)
            {
                uv_coords.y = std::stoi(sm[6])-1;
            }
            if (sm[9].length() != 0)
            {
                uv_coords.z = std::stoi(sm[9])-1;
            }

            p_faces.push_back(Face{ vertices, normals, uv_coords });
        }
        else
        {
            hum::log("Model format unsupported. Not loading.");
            p_vertices.clear();
            p_faces.clear();
            p_normals.clear();
            p_uv_coords.clear();
            success = false;
            break;
        }
    }
    return success;
}
} /* mogl */
