//#include <GL/glaux.h>
#ifndef TEXTURE
#define TEXTURE

#ifdef WIN32
#include <windows.h>
#endif

// win32 needs windows.h before gl.h
#ifdef WIN32
#  include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

class COGLTexture
{
public:
	unsigned int GetID();
	void LoadFromFile(char *filename);
	void SetActive();
	int GetWidth();
	int GetHeight();
private:
	int Width, Height;
	unsigned int ID;
};

#endif
