#ifndef IMAGE_IMPORTER_INCLUDED
#define IMAGE_IMPORTER_INCLUDED

#include "Image.h"
#include "FileHandler.h"

//: ImageImporter
// Abstract file handler for importation of Image objects from a file.
// Derived classes from ImageImporter will load an image file into 
// an Image object
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   TgaImporter tga_import;
//   tga_import( "bugs.tga", image );
// 
// alternately, you can call operator() this way:
//   tga_import.operator()( "bugs.tga", image );
//
class ImageImporter : public FileHandler
{
// construction
public:
	//: virtual destructor
	virtual		~ImageImporter() {}

// methods
public:
	//: Load the file "filename"
	//  returns true or false for successful or unsuccessful
	//  returns an Image object
	virtual bool operator()(const char* const filename, Image& image) = 0;
};

//////////////////////////////
// image importer properties.
//////////////////////////////
#include <iostream>
inline void outputImporterProperties( ImageImporter& ii )
{
	std::cout<<"Importer Type:      "<<ii.description()<<"\n"<<std::flush;
	std::cout<<"Related Extensions: ";
	for (int k = 0; k < ii.numberOfExtensionsSupported(); ++k)
	{
		std::cout<<'.'<<ii.extension(k)<<' ';
	}
	std::cout<<"\n"<<std::flush;
}

#endif
