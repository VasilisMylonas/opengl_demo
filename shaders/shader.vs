#version 400

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_color;
layout(location = 3) in vec2 in_uv;

out vec4 v_color;
out vec2 v_uv;

void main()
{
    gl_Position = vec4(in_position, 1.0);

    // Pass to fragment shader
    v_color = in_color;
    v_uv = in_uv;
}