//////////////////////////////////////////////////////////////////////////////
//
//                         -=     BmpImport class     =-
//
// Description: "a class for loading of device independent bitmap (bmp) images"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: BmpImporter.cxx,v $
//    $Date: 2001-09-14 05:00:57 $
//    $Revision: 1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////

//////////////////////////////////////////////////////////////////////////////

#include <string>             // for std::string
#include <fstream.h>
#include "Defines.h"            // needed for kev::byteReverse()
#include "CFileIO.h" // for fileexists..
#include "Endian.h" // for endianness

#include "BmpImporter.h"



BmpImporter::BmpImporter() : ImageImporter()
{
	this->_init();
	this->addExtension( "bmp" );
}

//: a string that describes the files supported by this importer
const char* const BmpImporter::description() const
{
	return "Windows Bitmap Image";
}

//
// Destructor, free memory
//
BmpImporter::~BmpImporter()
{
	//Private to BmpImport...
	if( _bmiColors != NULL )
		delete _bmiColors;
}

//
// LoadFile --- loads a dib
//
bool BmpImporter::operator()( const char* const filename, Image& image )
{
   if (!CFileIO::fileExists( filename ))
   {
      cout<<"File doesn't exist!\n"<<flush;
      return false;
   }

	#ifdef WIN32
	ifstream hBitmapFile( filename, ios::in | ios::nocreate | ios::binary, filebuf::openprot );
	#else
	ifstream hBitmapFile( filename, ios::in | ios::nocreate, filebuf::openprot );
	#endif
	
	image.setName( filename );
	bmpheader::BITMAPFILEHEADER fileHeader;
	
	//
	// bail if fileopen failed
	//
	if( !hBitmapFile.rdbuf()->is_open() )
	{
		//Log(7)<<"OOpS!: Can't open file "<<filename<<"\n"<<flush;
		hBitmapFile.close();
		this->_init();
		return false;
	}
	//
	// Read file header---should be the first thing that you encounter in the file...
	//

	hBitmapFile.read(reinterpret_cast<char*>( &fileHeader.bfType ), sizeof(unsigned short));
	hBitmapFile.read(reinterpret_cast<char*>( &fileHeader.bfSize ), sizeof(unsigned long));
	hBitmapFile.read(reinterpret_cast<char*>( &fileHeader.bfReserved1 ), sizeof(unsigned short));
	hBitmapFile.read(reinterpret_cast<char*>( &fileHeader.bfReserved2 ), sizeof(unsigned short));
	hBitmapFile.read(reinterpret_cast<char*>( &fileHeader.bfOffBits ), sizeof(unsigned long));
	
   
	// BMP format is little endian, 
   // so will need to swap bytes if system architecture is big endian.
   if (kev::isBigEndian())
   {
	   kev::byteReverse(fileHeader.bfType );
	   kev::byteReverse(fileHeader.bfSize );
	   kev::byteReverse(fileHeader.bfReserved1 );
	   kev::byteReverse(fileHeader.bfReserved2 );
	   kev::byteReverse(fileHeader.bfOffBits );
   }
      	
   // Check magic-cookie and read bitmap info if the cookie's ok
	if( fileHeader.bfType != bmpheader::BMP_MAGIC )
	{
		hBitmapFile.close();
		//Log(5)<<"OOpS!: Bad magic ("<<fileHeader.bfType<<") in \""<<filename<<"\n"<<flush;
		return false;
	} 

	//read the info header.
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biSize ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biWidth ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biHeight ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biPlanes ), sizeof(short));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biBitCount ), sizeof(short));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biCompression ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biSizeImage ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biXPelsPerMeter ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biYPelsPerMeter ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biClrUsed ), sizeof(long));
	hBitmapFile.read(reinterpret_cast<char*>( &_infoheader.biClrImportant ), sizeof(long));
	
	// BMP format is little endian, 
   // so will need to swap bytes if system architecture is big endian.
   if (kev::isBigEndian())
   {
	   kev::byteReverse(_infoheader.biSize );
	   kev::byteReverse(_infoheader.biWidth);
	   kev::byteReverse(_infoheader.biHeight);
	   kev::byteReverse(_infoheader.biPlanes);
	   kev::byteReverse(_infoheader.biBitCount);
	   kev::byteReverse(_infoheader.biCompression);
	   kev::byteReverse(_infoheader.biSizeImage);
	   kev::byteReverse(_infoheader.biXPelsPerMeter);
	   kev::byteReverse(_infoheader.biYPelsPerMeter);
	   kev::byteReverse(_infoheader.biClrUsed);
	   kev::byteReverse(_infoheader.biClrImportant);
   }
      	
	//
	// Check the info's header we read, to see if makes sense as a bitmap
	//
	if( !( 
			( _infoheader.biSize == sizeof(bmpheader::BITMAPINFOHEADER) ) &&
			( _infoheader.biPlanes == 1)    &&
			(	
				(_infoheader.biBitCount == 1 ) ||
				(_infoheader.biBitCount == 4 ) ||
				(_infoheader.biBitCount == 8 ) ||
			 	(_infoheader.biBitCount == 24)	||
				(_infoheader.biBitCount == 32)
			) &&
			(_infoheader.biCompression == bmpheader::BI_RGB)
		))
	{
		//Log<<"OOpS!: Invalid Color Depth. == "<<_infoheader.biBitCount<<"\n"<<flush;
		hBitmapFile.close();
		this->_init();
		//Log(5)<<"OOpS!: \""<<filename<<"\" Header info makes no sense\n"<<flush;
		return false;
	}

	
	//
	// Read the color palette
	//
	//colorTableSize = ColorsUsed() * sizeof(long);
	//if( infoHeader->biBitCount <= 24 ) //was 8
	//{
	//	hBitmapFile.read((char *)& (_bmiColors), colorTableSize);
	//	if( hBitmapFile.eof() ) //bytes read doesn't == colorTable size
	//	{
	//		//Log<<"OOpS!: Color table size in bitmap does not match size in header\n"<<flush;
	//		hBitmapFile.close();
	//		this->_init();
	//		return false;
	//	}
	//}

	// a 24-bit BMP has 3 8-bit channels per pixel (24-bit image)
	const int threeChannels = 3;
	kev::Alert( _infoheader.biBitCount == 24, "Only 24 bit bmps are supported at this time." );
	const int alignment = 4;
	image.reserve( _infoheader.biWidth, _infoheader.biHeight, _infoheader.biBitCount, threeChannels, alignment );

	// read the image, preserving the 4-byte alignment
	hBitmapFile.read( reinterpret_cast<char*>( image.data() ), image.size() );
	
	// we read in the data bgrbgrbgrbgr.
	// swap the b and r bytes so it is rgbrgbrgb:
	image.swapChannels( 0, 2 );

	hBitmapFile.close();

	return true;
}
