#include "LoggerComponenet.hpp"

namespace Pringine{


    const char* LogTypeStrings[] = {"ERROR", "WARNING", "LOG"};
    FILE* log_fp; // file pointer to log file
    const char* log_file_path;
    bool log_enabled = true;



    void close_log_fp()
    {
        if(log_fp!=NULL)
            fclose(log_fp);
    }

    void set_log_file_path(const char* log_file_path)
    {
        Pringine::log_file_path = log_file_path;
    }

    void log_to(LogType type, const char* log_text)
    {
        if(!log_enabled)
            return;
            
        // buffer is one greater since it adds a new line character
        char message_buffer[1024];
        char buffer[1025];
        sprintf(message_buffer,"\033[0m\033[1;31m%s\033[0m: %s", LogTypeStrings[type], log_text); 
        sprintf(buffer, "%s\n", message_buffer); 
        
        printf("%s",buffer); 
        if(log_file_path)
            log_fp = write_to_file(buffer, log_file_path, log_fp);
    }

}