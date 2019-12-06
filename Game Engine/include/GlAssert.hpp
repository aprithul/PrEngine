#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <iostream>

#define DEBUG true

#define Assert(x) if(!x) __builtin_trap();

#ifdef DEBUG
    #define GL_CALL(x) gl_clear_error(); x; Assert(gl_get_error(#x, __FILE__, __LINE__))
#else
    #define GL_CALL(x) x
#endif

void gl_clear_error();
bool gl_get_error(char* func_name, char* file_name, int line_no);