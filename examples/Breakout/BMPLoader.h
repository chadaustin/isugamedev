// Copyright 2002 Jacob Marner. jacob@marner.dk. Released under LGPL.

#ifndef BMP_LOADER_HEADER
#define BMP_LOADER_HEADER

// Does you program not use GLUT? If not, remove the following
// include line and include the standard OpenGL headers instead,
// <GL/gl.h> and <GL/glu.h>.
// If you use Windows remember to include <windows.h> also.
#include <GL/glut.h>

// The following is the function return type. Use this to
// get information about how the loading operation went.

enum LOAD_TEXTUREBMP_RESULT {
  // The texture loading operation succeeded.
  LOAD_TEXTUREBMP_SUCCESS=0,
  // The file could not be found or it could not be opened for reading.
  LOAD_TEXTUREBMP_COULD_NOT_FIND_OR_READ_FILE,
  // The file does not comply with the specification.
  LOAD_TEXTUREBMP_ILLEGAL_FILE_FORMAT,
  // OpenGL could not accept the texture. You proably used a internal
  // format not accepted by your OpenGL implementation or you may have run 
  // out of available texture names.
  LOAD_TEXTUREBMP_OPENGL_ERROR,
  // The system ran out of heap memory during the texture load.
  LOAD_TEXTUREBMP_OUT_OF_MEMORY};

// Loads the specified BMP image and stores it into a OpenGL 2D texture, whose 
// name will be returned in textureName. If an error occured, texturename is
// undefined. The status of the operation will be returned as the 
// return value. 
  
// The bitmap will be loaded without borders and all mip maps will be
// generated automatically. If you need the bitmap for anything else than
// textures, or you need borders you will have to edit the source code.

// Parameters:
// [in] filename: The name of the texture file. Must be Windows .BMP format.
//   The actual file *must* use the .bmp extension. For the filename string 
//   given as parameter the extension is optional - if it is not there
//   it is appended automatically.
// [in/out] textureName: Pass a pointer to an already allocated GLuint and if 
//   the operation success then this data will point to the texture name 
//   of the texture object loaded. This can immediately be used with 
//   glBindTexture() to use the texture during drawing. If the return value 
//   is not LOAD_TEXTUREBMP_SUCCESS then this value is undefined. If you
//   later want to delete the loaded texture call glDeleteTextures() on the
//   returned texture name.
// [in] internalformat: The internal format of the loaded texture. Is passed 
//   directly to glTextImage2D(). Defaults to GL_RGB.
// Return value:
// [out] Status of operation.

LOAD_TEXTUREBMP_RESULT loadOpenGL2DTextureBMP(const char* filename, 
                                              GLuint* textureName, 
                                              GLint internalformat = GL_RGB);

#endif
