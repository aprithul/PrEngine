#include "Utils.hpp"
#define DEBUG_BASE_PATH

namespace PrEngine{
    // write to file


    void trim(std::string& str)
    {
        str.erase(0, str.find_first_not_of("\t\n\v\f\r ")); // left trim
        str.erase(str.find_last_not_of("\t\n\v\f\r ") + 1); // right trim
    }


	void write_to_file(const std::string& text, const std ::string& file_name, Bool_8 binary, Bool_8 append)
    {
        std::ios_base::openmode mode = std::ios_base::out;
        if(binary)
            mode |= std::ios::binary;
        if(append)
            mode |= std::ios::app;
		std::ofstream _file(file_name, mode);
		if (_file.is_open())
		{
			_file << text;
			_file.close();
		}
    }

    // reads content of file_name, character by character
    // stores in buffer and returns
    // dynamically increases in size if needed
    std::string read_file(const std::string& file_name)
    {

    std::string _file_name(file_name);
    trim(_file_name);
    //Uint_32 st = _file_name.find_last_not_of(" \n\r\t");
    //_file_name.erase(st+1);
/*
    std::ifstream in(_file_name, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    else
    {
        std::cout<<strerror(errno)<<std::endl;
        LOG(LOGTYPE_ERROR, "File opening error");
        return "";
    }
 */   




        //LOG(LOGTYPE_WARNING, "reading: ",file_name);
        std::string data = "";
        std::string line = "";
		std::ifstream _file(_file_name, std::ifstream::in);

        //while(std::getline(_file, line))
        //{
         //   data += line;
        //}

		std::stringstream buffer;
		buffer << _file.rdbuf();
        _file.close();
        //std::cout<<"data read: "<<data<<std::endl;
        //return data;
		return buffer.str();
    }
    

    std::string get_resource_path(const std::string &subDir){
        //We need to choose the path separator properly based on which
        //platform we're running on, since Windows uses a different
        //separator than most systems
    

        static std::string base_path = "res"+PATH_SEP;
        /*if (base_path.empty()){
            //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
            Char_8 *_base_path = SDL_GetBasePath();
            if (_base_path){
                base_path = _base_path;
#ifdef DEBUG_BASE_PATH
				base_path = (std::string(_base_path)+".."+PATH_SEP+".."+PATH_SEP+".."+PATH_SEP).c_str();
#endif // DEBUG_base

                SDL_free(_base_path);
            }
            else {
                LOG(LOGTYPE_ERROR, std::string("Error getting resource path:").append(std::string(SDL_GetError())));
                return "";
                
            }
            //We replace the last bin/ with res/ to get the the resource path
            
            base_path = base_path + "res" + PATH_SEP;
        }*/
        //If we want a specific subdirectory path in the resource directory
        //append it to the base path. This would be something like Lessons/res/Lesson0
        std::string resource_path = subDir.empty() ? base_path : base_path + subDir;
        return resource_path;
    }

    Rect::Rect()
    {
        x = 0;
        y = 0;
        w = 0;
        h = 0;
    }

    Rect::Rect(Float_32 x,Float_32 y,Float_32 w,Float_32 h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
    
    Bool_8 inside(Vector2<Int_32> pos, SDL_Rect& rect, Bool_8 centered)
    {
        if(!centered)
        {
            if(pos.x<=rect.x+rect.w && pos.x>=rect.x &&
                pos.y<=rect.y+rect.h && pos.y>=rect.y)
                    return true;
        }
        else
        {
            if(pos.x<=rect.x+rect.w/2 && pos.x>=rect.x-rect.w/2 &&
                pos.y<=rect.y+rect.h/2 && pos.y>=rect.y-rect.h/2)
                    return true;
        }
        
        return false;
    }

    Bool_8 inside(Vector2<Float_32> pos, SDL_Rect& rect, Bool_8 centered)
    {
        if(!centered)
        {
            if(pos.x<=rect.x+rect.w && pos.x>=rect.x &&
                pos.y<=rect.y+rect.h && pos.y>=rect.y)
                    return true;
        }
        else
        {
            if(pos.x<=rect.x+rect.w/2 && pos.x>=rect.x-rect.w/2 &&
                pos.y<=rect.y+rect.h/2 && pos.y>=rect.y-rect.h/2)
                    return true;
        }
        
        return false;
    }

	Bool_8 inside(Vector2<Float_32> pos, Rect& rect, Bool_8 centered)
	{
		if (!centered)
		{
			if (pos.x <= rect.x + rect.w && pos.x >= rect.x &&
				pos.y <= rect.y + rect.h && pos.y >= rect.y)
				return true;
		}
		else
		{
			if (pos.x <= rect.x + rect.w / 2 && pos.x >= rect.x - rect.w / 2 &&
				pos.y <= rect.y + rect.h / 2 && pos.y >= rect.y - rect.h / 2)
				return true;
		}

		return false;
	}

	Uint_32 str_hash(const std::string& str)
	{
		Uint_32 _hash = 0;
		for (auto& c : str)
		{
			_hash += c;
		}

		return _hash;
	}

/*    Bool_8 inside(Vector2<Float_32> pos, SDL_FRect& rect, Bool_8 centered)
    {
        if(!centered)
        {
            if(pos.x<=rect.x+rect.w && pos.x>=rect.x &&
                pos.y<=rect.y+rect.h && pos.y>=rect.y)
                    return true;
        }
        else
        {
            if(pos.x<=rect.x+rect.w/2 && pos.x>=rect.x-rect.w/2 &&
                pos.y<=rect.y+rect.h/2 && pos.y>=rect.y-rect.h/2)
                    return true;
        }
        
        return false;
    }*/


}
