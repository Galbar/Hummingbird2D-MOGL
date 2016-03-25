R"(
#version 330

uniform sampler2D tex;
uniform vec4 color;

out vec4 out_color;
in vec2 frag_texture_coord;

void main()
{
    if (texture2D(tex, frag_texture_coord).a < 0.5)
    {
        discard;
    }
    out_color = color * texture2D(tex, frag_texture_coord);
}
)"
