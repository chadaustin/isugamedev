#include "BmpImporter.h"
#include "textures.h"

void COGLTexture::LoadFromFile(char *filename)
{
	pixmi::Image image;
         pixmi::BmpImporter bmp;
         bmp.load( filename, image ); 
	//Image = auxDIBImageLoadA( (const char*) filename );
	
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

      
void COGLTexture::SetActive()
{
	glBindTexture( GL_TEXTURE_2D, ID);
}

unsigned int COGLTexture::GetID()
{
	return ID;
}

