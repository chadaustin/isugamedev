
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     CppImageExporter class     =-
//
// Description: "Exports an Image as c code.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: CppImageExporter.cxx,v $
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

#include <string>  // for std::string
#include "Defines.h"		// needed for kev::byteReverse()

#include "CppImageExporter.h"

//: Default constructor
CppImageExporter::CppImageExporter()
{
	this->addExtension( "cpp" );
}
	
//: Destructor
CppImageExporter::~CppImageExporter()
{
}

//: Save the image as "filename"
//  returns true or false for successful or unsuccessful
bool CppImageExporter::operator()(const char* const filename, const Image& image)
{
	//: Open a file to write as binary.
	FILE* fp = ::fopen( filename, "wb" );
	if (fp == NULL)
	{
		kev::Alert( fp != NULL, "Could not open file for writing" );
		return false;
	}

	char temp[256];
	std::string colonReturn = ";\n";
	std::string Return = "\n";
	std::string rightCurly = " }";
	std::string comma = ",";
	std::string space = " ";

	std::string comment = "// CppImageExporter written by Kevin Meinert KevinMeinert@bigfoot.com\n";
	comment += "// Image name = ";
	comment += image.name();
	comment += "\n\n\n";

	std::string width;
	width += "//: Number of pixels in one scanline, a pixel is typically 1,3, or 4 bytes\n";
	width += "static const unsigned int width = ";
	::sprintf( temp, "%d", image.width() );
	width += temp;
	width += colonReturn + Return;

	std::string height;
	height += "//: Number of scanlines in image data\n";
	height += "static const unsigned int height = ";
	::sprintf( temp, "%d", image.height() );
	height += temp;
	height += colonReturn + Return;

	std::string channels;
	channels += "//: Number of color channels in the image\n";
	channels += "//  Returns a number: '1' (Greyscale/Luminance), '3' (RGB), '4' (RGBA)\n";
	channels += "static const unsigned int channels = ";
	::sprintf( temp, "%d", image.channels() );
	channels += temp;
	channels += colonReturn + Return;

	std::string alignment;
	alignment += "//: Scanline alignment, each row's size in bytes is a multiple of this\n";
	alignment += "//  Each row is padded with (width % alignment) non-pixel bytes\n";
	alignment += "static const unsigned int alignment = ";
	::sprintf( temp, "%d", image.rowAlignment() );
	alignment += temp;
	alignment += colonReturn + Return;

	std::string padding;
	padding += "//: Scanline padding\n";
	padding += "//  This is the number of bytes (non-pixel data) attached to the end of each scanline.\n";
	padding += "static const unsigned int padding = ";
	::sprintf( temp, "%d", image.rowPadding() );
	padding += temp;
	padding += colonReturn + Return;
	
	std::string bpp;
	bpp += "//: Number of bits per pixel\n";
	bpp += "//  Typical values include 8, 15, 16, 24, 32\n";
	bpp += "static const unsigned int bpp = ";
	::sprintf( temp, "%d", image.bpp() );
	bpp += temp;
	bpp += colonReturn + Return;

	std::string data;
	data += "//: Image data\n";
	data += "//  Orientation is by scanline. RGBARGBARGBAX etc... where RGBA is pixel, X is padding\n";
	data += "static const unsigned char data[] = { ";

	//: Write header:
	::fwrite( comment.data(), comment.size(), 1, fp );
	::fwrite( width.data(), width.size(), 1, fp );
	::fwrite( height.data(), height.size(), 1, fp );
	::fwrite( channels.data(), channels.size(), 1, fp );
	::fwrite( alignment.data(), alignment.size(), 1, fp );
	::fwrite( padding.data(), padding.size(), 1, fp );
	::fwrite( bpp.data(), bpp.size(), 1, fp );	
	::fwrite( data.data(), data.size(), 1, fp );
	
	//: Write the data

	// for each scanline...
	std::string characterNumber;
	const char pad = '0';
	int linewidth = 0;
	for (int i = 0; i < image.height(); ++i)
	{
		const unsigned char* const rowPtr = image.row(i);
		for (int j = 0; j < image.width()*image.channels(); ++j)
		{
			// write a space every "channels" bytes (before every pixel)
			if (j%image.channels() == 0)
			{
				::fwrite( space.data(), space.size(), 1, fp );
				linewidth += space.size();
			}

			// write the byte value, and a comma
			int pixelColor = rowPtr[j];
			::sprintf( temp, "0x%.2x", pixelColor );
			characterNumber = temp;
			::fwrite( characterNumber.data(), characterNumber.size(), 1, fp );
			::fwrite( comma.data(), comma.size(), 1, fp );

			linewidth += characterNumber.size() + comma.size();

			// make the rows x chars wide.
			if (linewidth > 80)
			{
				::fwrite( Return.data(), Return.size(), 1, fp );
				linewidth = 0;
			}
		}

		if (image.rowAlignment() > 1)
		{
			::fwrite( space.data(), space.size(), 1, fp );
			::fwrite( space.data(), space.size(), 1, fp );
			for (int t = 0; t < image.rowPadding(); ++t)
			{
				::fwrite( &pad, 1, 1, fp );
				::fwrite( comma.data(), comma.size(), 1, fp );
			}
		}
		::fwrite( Return.data(), Return.size(), 1, fp );
		::fwrite( Return.data(), Return.size(), 1, fp );
	}

	::fwrite( rightCurly.data(), rightCurly.size(), 1, fp );
	::fwrite( colonReturn.data(), colonReturn.size(), 1, fp );

	//: close the file
	::fclose( fp );

	//: success! (what else is there?)
	return true;
}

//: a string that describes the files supported by this importer
const char* const CppImageExporter::description() const
{
	return "C++ code";
}
