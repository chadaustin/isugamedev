//#include <GL/glaux.h>
#ifndef TEXTURE
#define TEXTURE

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
