#include "Mesh.hpp"

namespace mogl
{
Mesh::Mesh(const VertexArray& vertex_array):
p_vertex_array(&vertex_array)
{}

Mesh::~Mesh()
{}

void Mesh::setShaderProgram(ShaderProgram* shader_program)
{
    Drawable::setShaderProgram(shader_program);
    glBindVertexArray(p_vertex_array->getNativeHandles().vao);
    glBindBuffer(GL_ARRAY_BUFFER, p_vertex_array->getNativeHandles().vbo);
    p_position_loc = shaderProgram()->bindVertexAttribute("position", 3, 8*sizeof(float), 0);
    //p_normal_loc = shaderProgram()->bindVertexAttribute("normal", 3, 8*sizeof(float), (void*)(3*sizeof(float)));
    //p_uv_loc = shaderProgram()->bindVertexAttribute("uv", 2, 8*sizeof(float), (void*)(6*sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::draw()
{
    hum::log("bitch slap 1");
    glBindVertexArray(p_vertex_array->getNativeHandles().vao);
    hum::log("bitch slap 2");
    shaderProgram()->setUniform4f("color",
            static_cast<float>(0.f)/255.0f,
            static_cast<float>(255.f)/255.0f,
            static_cast<float>(255.f)/255.0f,
            static_cast<float>(0.f)/255.0f);
    hum::log("bitch slap 3");
    glEnableVertexAttribArray(p_position_loc);
    //glEnableVertexAttribArray(p_normal_loc);
    //glEnableVertexAttribArray(p_uv_loc);
    hum::log("bitch slap 4");
    hum::log(std::to_string(p_vertex_array->getNumFaces() * 3));
    hum::log("bitch slap 5");
    glDrawArrays(GL_TRIANGLES, 0, p_vertex_array->getNumFaces() * 3);
    hum::log("bitch slap 6");
}
} /* mogl */
