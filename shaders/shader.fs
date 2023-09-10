#version 400

layout(location = 0) out vec4 out_color;

uniform sampler2D u_texture;

in vec4 v_color;
in vec2 v_uv;

void main() 
{ 
    out_color = v_color * texture(u_texture, v_uv);
}