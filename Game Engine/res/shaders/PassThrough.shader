#vertex

#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec4 _color;
layout(location=2) in vec4 _normal;
layout(location=3) in vec2 texco;
uniform mat4 u_MVP;
uniform mat4 u_Normal_M;
uniform vec3 u_Dir_Light;
uniform vec2 u_Tiling;
uniform vec2 u_Panning;

out vec4 out_color;
out vec2 out_texco;
out float out_light;
out vec2 out_tiling;
out vec2 out_panning;

void main()
{
    gl_Position = u_MVP * position;
    out_color = _color;
    out_texco = texco;
    vec4 n = normalize(u_Normal_M *_normal);
    out_light = clamp((1.0 - dot(n.xyz,u_Dir_Light)),0,1);
    out_tiling = u_Tiling;
    out_panning = u_Panning;
}

#fragment
#version 330 core

//uniform float u_red;
uniform sampler2D u_sampler2d;
in vec4 out_color;
in vec2 out_texco;
in float out_light;
in vec2 out_tiling;
in vec2 out_panning;

out vec4 color;
void main()
{
    u_sampler2d;
    //color = vec4(out_light,out_light,out_light,1);// vec4(out_light,out_light,out_light,1.0);// texture(u_sampler2d, out_texco)*2.0;// * out_light;// * out_light;// vec4(u_red, out_color.gba);//vec4(0.0,1.0,1.0,1.0);
    vec4 tex_col = texture(u_sampler2d, (out_texco.xy+out_panning.xy)*out_tiling.xy);// * out_light;// vec4(u_red, out_color.gba);//vec4(0.0,1.0,1.0,1.0);
    color = vec4(tex_col.rgb* out_light, tex_col.a);
}
