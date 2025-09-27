#version 400

layout(location = 0) out vec4 out_color;

uniform sampler2D u_textures[2];

in vec4 v_color;
in vec2 v_uv;
flat in uint v_texture;

void main()
{
    out_color = v_color * texture(u_textures[v_texture], v_uv);
}
