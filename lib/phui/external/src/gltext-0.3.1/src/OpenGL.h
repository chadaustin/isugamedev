#ifndef GLTEXT_OPENGL_H
#define GLTEXT_OPENGL_H

// Windows requires windows.h
#if defined(WIN32) || defined(_WIN32)
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  ifndef STRICT
#    define STRICT
#  endif
#  include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#endif
