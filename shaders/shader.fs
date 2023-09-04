#version 400

layout(location = 0) out vec4 color_out;

in vec4 interp_color;

void main() { color_out = interp_color; }