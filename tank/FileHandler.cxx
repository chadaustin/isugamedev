
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     FileHandler class     =-
//
// Description: ""
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: FileHandler.cxx,v $
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
#include "CFileIO.h"  //to check if a file exists.
#include "Defines.h" // MIN
#include "FileHandler.h"

//: test if a file is supported by this importer
bool FileHandler::canHandle( const char* const filename ) const
{
	bool canload = false;

	for (int x = 0; x < _extensions.size(); ++x)
	{
		// we need a non-const version of filename...
		char* file = new char[::strlen(filename)+1];
		::strcpy( file, filename );

		// see if .ext exists in the string "filename"
		std::string fileExt = CFileIO::fileExtension( file );
		std::string currentExt = _extensions[x];

		int amountToCompare = kev::MIN(fileExt.size(), currentExt.size());
		#ifdef WIN32
		if (strnicmp( fileExt.data(), currentExt.data(), amountToCompare ) == 0)
			canload = true;
		#else
		if (strncasecmp( fileExt.data(), currentExt.data(), amountToCompare ) == 0)
			canload = true;
		#endif
		
		// cleanup
		delete []file;
	}

	return canload;
}

//: the extension supported by this importer.  i.e. bmp, rgb, pcx
//  give - an index number for importers that support multiple file extensions
//  returns - the extension supported by this importer.
const char* const FileHandler::extension( const int& index ) const
{
	return _extensions[index].data();
}

//: returns - the number of extensions supported
int FileHandler::numberOfExtensionsSupported() const
{
	return _extensions.size();
}

//: add an extension descriptor
//  usually this is only used by the importer's constructor to add extension descriptions.
//  give - a file extension such as bmp, rgb, pcx
void FileHandler::addExtension( const char* const ex )
{
	_extensions.push_back( std::string(ex) );
}
