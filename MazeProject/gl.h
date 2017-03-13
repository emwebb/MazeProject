// This file exists just to make imports cleaner.
#ifndef gl_h
#define gl_h

#ifdef __linux__
#include <GL/gl.h>
#elif __APPLE__
#include <OpenGL/gl3.h>
#endif

#endif /* gl_h */
