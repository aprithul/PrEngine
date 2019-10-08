//
//  FrameRateRegulatorComponent.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef LOGGER_COMPONENT_HPP
#define LOGGER_COMPONENT_HPP

#include <unistd.h>
#include <stdio.h>
#include "Utils.hpp"
#include <string>

namespace Pringine{

    typedef enum
    {
        LOGTYPE_ERROR,
        LOGTYPE_WARNING,    
        LOGTYPE_GENERAL

    }LogType;


    // Logging functions
    extern FILE* log_fp;
    extern const char* log_file_path;
    extern bool log_enabled;
    void log_to(LogType type, const char* log_text);
    void close_log_fp();
    void set_log_file_path(const char* log_file_path);
    
        
}


#endif