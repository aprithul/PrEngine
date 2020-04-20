#include "Material.hpp"

namespace PrEngine
{

    std::unordered_map<std::string, Material*> material_library;
    std::unordered_map<std::string, GLuint> shader_library;

    /*Material::()
    {

    }*/

    Material::Material(const std::string& shader_path, const std::string& diffuse_tex_path,const std::string& name)
    {
        // only create new texture on gpu if texture doesn't exist already
        tiling = Vector2<float>(1,1);
        panning = Vector2<float>(0,0);

        std::unordered_map<std::string, Texture*>::iterator _tex_it = texture_library.find(diffuse_tex_path);
        if(_tex_it == texture_library.end()) // texture not in library, so create
        {
            Texture* _tex =  new Texture(diffuse_tex_path.c_str());
            if(texture_create_status == 0){    // creating texture failed, so assign default
                delete _tex;
                diffuse_texture = texture_library[get_resource_path("default.jpg")];
            }
            else // successfully created texture, store in library and assign that
            {
                texture_library[diffuse_tex_path] = _tex;
                diffuse_texture = _tex;

            }
        }
        else    // texture found in library, so assign that
            diffuse_texture = texture_library[diffuse_tex_path];

        std::unordered_map<std::string, GLuint>::iterator _shader_it = shader_library.find(shader_path);
        if(_shader_it == shader_library.end())
        {
            // create shader, probably can be shared, will check later
            this->source_file_path = std::string(shader_path);
            make_shader_program(this->source_file_path);
            GL_CALL(
                glUseProgram(shader_program))
            
            shader_library[shader_path] = shader_program;
        }
        else
            shader_program = _shader_it->second;

        load_uniform_location("u_sampler2d");
        load_uniform_location("u_MVP");
        load_uniform_location("u_Normal_M");
        load_uniform_location("u_Dir_Light");
        load_uniform_location("u_Tiling");
        load_uniform_location("u_Panning");

    }

    void Material::Delete()
    {
        GL_CALL(
            glDeleteProgram(shader_program))

        for(std::unordered_map<std::string, Texture*>::iterator it=texture_library.begin(); it!=texture_library.end(); it++)
        {
            if( it->second!=nullptr)
            {
                if(it->second->id == diffuse_texture->id)
                {
                    delete it->second;
                    it->second = nullptr;
                    LOG(LOGTYPE_GENERAL, "Deleting texture");

                }
            }
        }
        
        //delete diffuse_texture;
    }

    Material::~Material()
    {
        
    }

    void Material::load_uniform_location(std::string uniform)
    {
        GLint loc = -1;
        GL_CALL(
            loc = glGetUniformLocation(shader_program, uniform.c_str()))
        
        std::cout<<"Location: "<<uniform<<" , "<<loc<<std::endl;
        //if(loc != -1)
        uniform_locations[uniform] = loc;
    }

    bool Material::make_shader_program(const std::string& path)
    {
        std::string _source = read_file(get_resource_path(path).c_str());
        std::stringstream shader_source;
        shader_source << _source;
        
        std::string vert = "";
        std::string frag = "";
        std::string line = "";
        GLenum type = GL_VERTEX_SHADER;
        while(std::getline(shader_source, line))
        {
            //std::cout<<line<<std::endl;
            if(line.find("#vertex") != std::string::npos){
                type = GL_VERTEX_SHADER;

            }
            else if(line.find("#fragment")!= std::string::npos){
                type = GL_FRAGMENT_SHADER;
            }
            else
            {
                if(type == GL_VERTEX_SHADER)
                    vert += line+"\n";
                else if(type == GL_FRAGMENT_SHADER)
                    frag += line+"\n";
            }
        }

        shader_program = glCreateProgram();
        if(shader_program == 0)
        {
            std::cout<<"Couldn't create shader program"<<std::endl;
            return false;
        }

        GLuint v = make_shader( GL_VERTEX_SHADER, vert);
        GLuint f = make_shader( GL_FRAGMENT_SHADER, frag);
        if(v != -1 && f != -1)
        {
            glAttachShader(shader_program, v);
            glAttachShader(shader_program, f);
            glLinkProgram(shader_program);
            GLint program_linked;

            glGetProgramiv(shader_program, GL_LINK_STATUS, &program_linked);
            if (program_linked != GL_TRUE)
            {
                int length;
                glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &length);
                GLchar* log = (GLchar*)alloca(length*sizeof(GLchar));
                glGetProgramInfoLog(shader_program, length, &length, log);
                LOG(LOGTYPE_ERROR, "Shader linking error\n",std::string(log));
                
                glDetachShader(shader_program, v);
                glDeleteShader(v);
                glDetachShader(shader_program, f);
                glDeleteShader(f);       
            }
            else
            {   
                glDetachShader(shader_program, v);
                glDeleteShader(v);
                glDetachShader(shader_program, f);
                glDeleteShader(f);
                return true;
            }
        }
        return false;
    }

    GLuint Material::make_shader( GLenum type,  const std::string& source)
    {
        GLuint shader =  glCreateShader(type);
        if(shader == 0)
            std::cout<<"Couldn't create shader"<<std::endl;
            
        const char* _source = source.c_str();
        glShaderSource(shader,1, &(_source) , NULL);
        glCompileShader(shader);
        
        // check
        GLint compilation_status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_status);
        if(compilation_status != GL_TRUE)
        {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            GLchar* log = (GLchar*)alloca(length*sizeof(GLchar));
            glGetShaderInfoLog(shader, length, &length, log);
            LOG(LOGTYPE_ERROR, "Shader compilation error in ",(type==GL_VERTEX_SHADER?"Vertex":"Fragment"),"shader: \n"+std::string(log)+"\n");
            glDeleteShader(shader);
            shader = -1;
        }
        return shader;
    }
    
}