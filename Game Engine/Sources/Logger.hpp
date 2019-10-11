//
//  FrameRateRegulatorComponent.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef LOGGER
#define LOGGER

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.hpp"

namespace Pringine{

    typedef enum
    {
        LOGTYPE_ERROR,
        LOGTYPE_WARNING,    
        LOGTYPE_GENERAL

    }LogType;


    typedef enum
    {
        LOGLEVEL_MAX,
        LOGLEVEL_MODERATE,
        LOGLEVEL_MIN
    }LogLevel;


    // Logging functions
    extern const char* log_file_path;
    extern bool log_enabled;
    extern LogLevel log_level;
    extern void LOG(LogType type = LOGTYPE_GENERAL, std::string log_text="", bool log_to_file = false);
    extern void close_log_file();
    extern void set_log_file_path(const char* log_file_path);
    
}


#endif