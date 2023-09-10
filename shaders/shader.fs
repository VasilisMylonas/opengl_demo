#version 400

layout(location = 0) out vec4 color_out;

uniform sampler2D u_texture;

in vec4 interp_color;
in vec2 texture_coords;

void main() 
{ 
    color_out = interp_color * texture(u_texture, texture_coords);
}