#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;

out vec4 interp_color;

void main() {
  gl_Position = vec4(position, 1.0);
  interp_color = color;
}