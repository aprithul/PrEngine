#vertex

#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec4 _color;
layout(location=2) in vec2 texco;
uniform mat4 u_MVP;

out vec4 out_color;
out vec2 out_texco;
void main()
{
    gl_Position = u_MVP * position;
    out_color = _color;
    out_texco = texco;
}

#fragment
#version 330 core

//uniform float u_red;
uniform sampler2D u_sampler2d;
in vec4 out_color;
in vec2 out_texco;

out vec4 color;
void main()
{
    color = texture(u_sampler2d, out_texco);// vec4(u_red, out_color.gba);//vec4(0.0,1.0,1.0,1.0);
}
