#vertex

#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec4 _color;

out vec4 out_color;
void main()
{
    gl_Position = position;
    out_color = _color;
}

#fragment
#version 330 core

uniform float u_red;
in vec4 out_color;
out vec4 color;
void main()
{
    color = vec4(u_red, out_color.gba);//vec4(0.0,1.0,1.0,1.0);
}
