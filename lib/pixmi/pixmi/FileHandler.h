
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     file handler    =-
//
// Description: "generalized class type for all pluggable io objects"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: FileHandler.h,v $
//    $Date: 2002-01-17 00:04:56 $
//    $Revision: 1.1.1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
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
#ifndef FILE_HANDLER
#define FILE_HANDLER

// Abstract base class for such types as handlers/exporters of image and geometry data.
// Implements common attributes that a file handler would need, 
//     such as "can it deal with this filename?", 
//     "what is the description of this handler?",
//     and "what file extensions are supported by this handler?"
#include <vector>
#include <string>

namespace pixmi
{

class FileHandler
{
// construction
public:
   //: virtual destructor
   virtual ~FileHandler() {}

// methods
public:
   //: test if this handler can deal with a file called filename.  
   //  this implementation of this function only tests the file extension.
   //  NOTE: derived classes may want to overload this to actually test the file
   //        header for majic number, valid data, etc...
   virtual bool            canHandle( const char* const filename ) const;

   //: a string that describes the files supported by this handler
   virtual const char* const   description() const = 0;

   //: the extension supported by this handler.  i.e. bmp, rgb, pcx
   //  give - an index number for handler that support multiple file extensions
   //  returns - the extension supported by this handler.
   const char* const         extension( const int& index ) const;

   //: returns - the number of extensions supported
   int                     numberOfExtensionsSupported() const;

protected:
   //: add an extension descriptor
   //  usually this is only used by the handler's constructor to add extension descriptions.
   //  give - a file extension such as bmp, rgb, pcx
   void                  addExtension( const char* const ex );

private:
   std::vector<std::string>   _extensions;
};


} // namespace
#endif
