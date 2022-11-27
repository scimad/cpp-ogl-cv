#ifndef __RENDERER
#define __RENDERER



#include <signal.h>

#include "GL/glew.h"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);

#define GLCALL(x)\
    GLClearError();\
    x;\
    ASSERT(GLIsErrorFree(#x, __FILE__, __LINE__))

void GLClearError();
bool GLIsErrorFree(const char* function, const char* file, int line);


#endif
