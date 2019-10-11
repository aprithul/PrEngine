#include "Logger.hpp"

namespace Pringine{


    const char* LogTypeStrings[] = {"ERROR", "WARNING", "LOG"};
    std::ofstream log_file;
    const char* log_file_path;
    bool log_enabled = true;
    LogLevel log_level = LOGLEVEL_MIN;



    void close_log_file()
    {
        log_file.close();
    }

    void set_log_file_path(const char* log_file_path)
    {
        Pringine::log_file_path = log_file_path;
    }

  

    void LOG(LogType type, std::string log_text, bool log_to_file)
    {

        if(!log_enabled)
            return;
        
        std::string log_extra_info = "";    // depending on log level, this string may or may not contain progressively more text

        switch (log_level)
        {
        case LOGLEVEL_MAX:
            break;
        case LOGLEVEL_MODERATE:
            break;
        case LOGLEVEL_MIN:
            break;        
        }

        switch (type)
        {
        case LOGTYPE_GENERAL:
            std::cout<<log_extra_info<<log_text<<std::endl;
            break;
        case LOGTYPE_WARNING:
            std::cout<< "\033[1;33m" << "Warning:"<<"\033[0m"<<log_extra_info<<log_text<<std::endl;
            break;
        case LOGTYPE_ERROR:
            std::cout<< "\033[1;31m" << "Error:"<<"\033[0m"<<log_extra_info<<log_text<<std::endl;
            break;
        }

        if(log_to_file)
        {    
            if(log_file.is_open())
                log_file<<LogTypeStrings[type]<<": "<<log_text;
        }
    }

}