#version 400 core

layout(location = 0) in vec3 in_position;
// layout(location = 1) in vec4 in_color;
// layout(location = 2) in vec3 in_normal;
// layout(location = 3) in vec2 in_uv;
// layout(location = 4) in uint in_texture;

uniform mat4 u_proj;
uniform vec3 u_color;

// out vec3 v_color;
// out vec2 v_uv;
// flat out uint v_texture;


void main()
{
    gl_Position = vec4(in_position, 1.0);
    //  * u_proj;

    // Pass to fragment shader
    // v_uv = in_uv;
    // v_texture = in_texture;
}
