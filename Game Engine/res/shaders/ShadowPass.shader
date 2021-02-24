#vertex
#version 330 core
layout(location=0) in vec4 position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * position;
    //gl_Position = u_Model * position;
}

#fragment
#version 330 core

out vec4 color;
void main()
{
    //color = vec4(1,1,0,1);
    gl_FragDepth = gl_FragCoord.z;
    //color = vec4(gl_Position.z,gl_Position.z,gl_Position.z,1);
}
