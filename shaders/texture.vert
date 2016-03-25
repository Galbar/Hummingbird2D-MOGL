R"(
#version 330

uniform mat4 projection, view, model;
uniform vec4 texture_coords;

in vec3 position;
in float point_id;
out vec2 frag_texture_coord;

void main()
{
    vec4 coords = texture_coords;
    coords.zw = texture_coords.xy + texture_coords.zw;
    if (point_id == 0)
    {
        frag_texture_coord = coords.xy;
    }
    else if (point_id == 1)
    {
        frag_texture_coord = coords.zy;
    }
    else if (point_id == 2)
    {
        frag_texture_coord = coords.zw;
    }
    else if (point_id == 3)
    {
        frag_texture_coord = coords.xw;
    }
    gl_Position = projection * view * model * vec4(position, 1.0);
}
)"
