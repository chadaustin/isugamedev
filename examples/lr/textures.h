//#include <GL/glaux.h>
#ifndef TEXTURE
#define TEXTURE

// win32 needs windows.h before gl.h
#ifdef WIN32
#  include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

class COGLTexture
{
public:
	//_AUX_RGBImageRec *Image;
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
