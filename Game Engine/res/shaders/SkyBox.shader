#vertex

#version 330 core

layout(location=0) in vec4 position;
layout(location=1) in vec4 _color;
layout(location=2) in vec4 _normal;
layout(location=3) in vec2 texco;

uniform mat4 u_MVP;

out vec3 out_texco;

void main()
{
    out_texco = vec3(position);
    gl_Position = u_MVP*position;
}

#fragment
#version 330 core

//uniform float u_red;
uniform samplerCube u_sampler_cube;
in vec3 out_texco;

out vec4 color;
void main()
{
    color = texture(u_sampler_cube, out_texco);    
}
