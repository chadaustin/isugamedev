
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     CppImageExport class     =-
//
// Description: "Exports an Image as c code.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: CppImageExporter.h,v $
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
#ifndef CPP_PIXMAP_CODE_EXPORTER_INCLUDED
#define CPP_PIXMAP_CODE_EXPORTER_INCLUDED

#include "Image.h"
#include "ImageExporter.h"

//: CppImageExporter
// Write an Image object out to file
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   /* now do some changes to the image, white noise, a fractal, etc.. */
//   CppImageExporter cpp_export;
//   cpp_export( "bugs.cpp", image );
// 
// alternately, you can call operator() this way:
//   cpp_export.operator()( "bugs.cpp", image );
//
class CppImageExporter : public ImageExporter
{	
public:
	//: Default constructor
	CppImageExporter();		
		
	//: Destructor
	virtual ~CppImageExporter();
		
	//: Save the image as "filename"
	//  returns true or false for successful or unsuccessful
	virtual bool				operator()( const char* const filename, const Image& image );	
	
	//: a string that describes the files supported by this importer
	virtual const char* const	description() const;
};

#endif
