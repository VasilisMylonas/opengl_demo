#version 400 core

layout(location = 0) in vec3 in_position;

uniform mat4 u_mvp;
uniform vec3 u_color;

void main()
{
    gl_Position = u_mvp * vec4(in_position, 1.0);
}
