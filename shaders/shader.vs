#version 400 core

layout(location = 0) in vec3 in_position;
// layout(location = 1) in vec3 in_normal;
// layout(location = 2) in vec4 in_color;
// layout(location = 3) in vec2 in_uv;
// layout(location = 4) in uint in_texture;

// out vec4 v_color;
// out vec2 v_uv;
// flat out uint v_texture;

// uniform mat4 u_proj;

void main()
{
    gl_Position = vec4(in_position, 1.0);
    //  * u_proj;

    // Pass to fragment shader
    // v_color = in_color;
    // v_uv = in_uv;
    // v_texture = in_texture;
}
