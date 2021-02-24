#vertex
#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec4 _color;
layout(location=2) in vec4 _normal;
layout(location=3) in vec2 texco;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Normal_M;
uniform mat4 u_Light_MVP;

uniform vec2 u_Tiling;
uniform vec2 u_Panning;

out vec4 out_color;
out vec2 out_texco;
smooth out vec3 out_normal;
out vec3 world_pos;
out vec4 light_proj_pos;
//out float out_light;
out vec2 out_tiling;
out vec2 out_panning;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * position;
    light_proj_pos = u_Light_MVP * position;
    world_pos = vec3(u_Model * position);
    out_color = _color;
    out_texco = texco;
    out_normal = normalize(mat3(transpose(inverse(u_Model))) *_normal.xyz);
    //vec3 n = mat3(transpose(inverse(u_Model))) * _normal.xyz;
    out_tiling = u_Tiling;
    out_panning = u_Panning;
}

#fragment
#version 330 core

//uniform float u_red;
uniform sampler2D u_shadowmap;
uniform sampler2D u_sampler2d;
uniform float u_Ambient_Strength;
uniform float u_Specular_Strength;
uniform vec3 u_Dir_Light;
uniform vec3 u_Pos_Light;
uniform vec3 u_Camera_Position;

in vec4 out_color;
in vec2 out_texco;
smooth in vec3 out_normal;
in vec4 light_proj_pos;
in vec3 world_pos;
//in float out_light;
in vec2 out_tiling;
in vec2 out_panning;

out vec4 color;


float calculate_shadow(vec4 point)
{

    float bias = max(0.005*(1.0-dot(out_normal, u_Dir_Light)),0.001);
    vec3 projected = point.xyz/point.w;
    projected = (projected*0.5)+0.5;
    float nearest_depth = texture(u_shadowmap, projected.xy).r;
    float frag_depth = projected.z;
    if(frag_depth-bias>nearest_depth)
        return 0;
    else
        return 1;

}

void main()
{
    vec3 specular_color = vec3(1,1,1);
    //color = vec4(out_light,out_light,out_light,1);// vec4(out_light,out_light,out_light,1.0);// texture(u_sampler2d, out_texco)*2.0;// * out_light;// * out_light;// vec4(u_red, out_color.gba);//vec4(0.0,1.0,1.0,1.0);
    vec4 tex_col = texture(u_sampler2d, (out_texco.xy+out_panning.xy)*out_tiling.xy);// * out_light;// vec4(u_red, out_color.gba);//vec4(0.0,1.0,1.0,1.0);
    //if(tex_col.a <0.7f)
    //    discard;
    //else
    vec3 n_normal = normalize(out_normal);
    vec3 light_dir = normalize(world_pos-u_Pos_Light);
    float out_light = clamp((1.0 - dot(n_normal.xyz,light_dir)),0,1);
    vec3 spec_dir = reflect( light_dir, n_normal);
    vec3 view_dir = normalize(u_Camera_Position-world_pos);
    float spec = pow(max(dot(spec_dir, view_dir),0),32);
    float shadow_val = calculate_shadow(light_proj_pos);
    color = vec4(tex_col.rgb * shadow_val * (out_light + 0 + ( spec * u_Specular_Strength * specular_color)), tex_col.a);
    //color = vec4( vec3(tex_col.r),1.0);
    //color = vec4(texture(u_shadowmap, vec2(1,1)),1);
    //color =   vec4(spec*u_Specular_Strength,spec*u_Specular_Strength,spec*u_Specular_Strength,1f);//           vec4(spec_dir.x, spec_dir.y, spec_dir.z, tex_col.a);
        //color = vec4(vec3(gl_FragCoord.z), tex_col.a);
}
