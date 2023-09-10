#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 uv;

out vec4 interp_color;
out vec2 texture_coords;

void main()
{
  gl_Position = vec4(position, 1.0);

  // Pass to fragment shader
  interp_color = color;
  texture_coords = uv;
}