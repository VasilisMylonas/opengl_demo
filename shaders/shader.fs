#version 400 core

layout(location = 0) out vec4 out_color;

in vec4 v_color;
in vec2 v_texture_coords;

uniform mat4 u_mvp;
uniform vec3 u_color;
uniform sampler2D u_texture;
uniform bool u_use_texture;

void main()
{
    if (!u_use_texture)
    {
        out_color = vec4(u_color, 1.0);
    }
    else
    {
        out_color = texture(u_texture, v_texture_coords) * vec4(u_color, 1.0);
    }
}
