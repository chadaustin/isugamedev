#include "BmpImporter.h"
#include "textures.h"
#include <iostream>



/* Load a texture from a file 
 */
void COGLTexture::LoadFromFile(char *filename)
{
	pixmi::Image image;
         pixmi::BmpImporter bmp;
         bmp.load( filename, image ); 
	
         glPixelStorei( GL_UNPACK_ALIGNMENT, image.rowAlignment() );
         glPixelStorei( GL_UNPACK_ROW_LENGTH, image.width() );
         
         glGenTextures(1,&ID); 
         
	glBindTexture( GL_TEXTURE_2D, ID);
         Width = image.width();
	Height = image.height();
	gluBuild2DMipmaps( GL_TEXTURE_2D, 
			 image.channels(), 
			 Width,
			 Height,
			 GL_RGB,
			 GL_UNSIGNED_BYTE,
			 image.data() );
}

/* set it active
 */
void COGLTexture::SetActive()
{
	glBindTexture( GL_TEXTURE_2D, ID);
}

/* get the machines id of the texture
 */
unsigned int COGLTexture::GetID()
{
	return ID;
}

