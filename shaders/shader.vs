#version 400 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_texture_coords;

out vec4 v_color;
out vec2 v_texture_coords;

uniform mat4 u_mvp;
uniform vec3 u_color;
uniform sampler2D u_texture;
uniform bool u_use_texture;

void main()
{
    gl_Position = u_mvp * vec4(in_position, 1.0);

    v_texture_coords = in_texture_coords;
    v_color = in_color;
}
