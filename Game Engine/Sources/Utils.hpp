#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <SDL2/SDL.h>


extern char* read_file(char* file_name);
extern FILE* write_to_file(const char* text, const char* file_name, FILE *fp);
extern std::string get_resource_path(const std::string &subDir); 

#endif