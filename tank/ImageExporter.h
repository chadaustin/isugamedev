#ifndef IMAGE_EXPORTER
#define IMAGE_EXPORTER

#include "Image.h"
#include "FileHandler.h"

//: TgaExporter
// Abstract file handler for exportation of Image objects to a file.
// Derived classes will be able to write an Image object out to file
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   /* now do some changes to the image, white noise, a fractal, etc.. */
//   TgaExporter tga_export;
//   tga_export( "bugs.tga", image );
// 
// alternately, you can call operator() this way:
//   tga_export.operator()( "bugs.tga", image );
//
class ImageExporter : public FileHandler
{
// construction
public:
	//: virtual destructor
	virtual ~ImageExporter() {}

// methods
public:
	//: Saves the image as "filename"
	//  returns true or false for successful or unsuccessful
	virtual bool	operator()( const char* const filename, const Image& image ) = 0;
};

#endif
