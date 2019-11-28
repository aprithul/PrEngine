#include "Material.hpp"

namespace Pringine
{

    Material::Material()
    {

    }

    void Material::Generate(const std::string& shader_path, const std::string& diffuse_tex_path)
    {
        // only create new texture on gpu if texture doesn't exist already
        std::unordered_map<std::string, Texture*>::iterator _tex_it = texture_library.find(diffuse_tex_path);
        if(_tex_it == texture_library.end()) // texture not in library, so create
        {
            Texture* _tex =  new Texture(diffuse_tex_path.c_str());
            if(Texture::texture_create_status == 0){    // creating texture failed, so assign default
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
    
        // create shader, probably can be shared, will check later
        this->source_file_path = std::string(shader_path);
        make_shader_program(this->source_file_path);
        GL_CALL(
            glUseProgram(shader_program))
    }

    void Material::Delete()
    {
        GL_CALL(
            glDeleteProgram(shader_program))
        delete diffuse_texture;
    }

    Material::~Material()
    {

    }

    void Material::load_uniform_location(const char* uniform)
    {
        GLint loc = -1;
        GL_CALL(
            loc = glGetUniformLocation(shader_program, uniform))
        
        std::cout<<"Location: "<<loc<<std::endl;
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