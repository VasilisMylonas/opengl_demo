#version 400

layout(location = 0) out vec4 out_color;

// uniform sampler2D u_textures[2];
// in vec2 v_uv;
// flat in uint v_texture;
// in vec3 v_color;

uniform vec3 u_color;

void main()
{
    out_color = vec4(u_color, 1.0);

    // out_color = v_color * texture(u_textures[v_texture], v_uv);
}
