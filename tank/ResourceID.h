
//////////////////////////////////////////////////////////////////
//
//                         -=     resource ID     =-
//
// Definition: "a smart resource identifier"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ResourceID.h,v $
//    $Date: 2001-09-10 15:27:29 $
//    $Revision: 1.1 $
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
#ifndef RESOURCE_ID
#define RESOURCE_ID

namespace kev
{
   // use the type: vjGlContextData<ResourceID>
   // to store your OpenGL texture object and display list IDs
   // i.e. vjGlContextData<ResourceID>  mTexObj;
   template <class _type>
   class ResourceID
   {
   public:
      ResourceID() : valid( false ), id( 0 )
      {
      }
      ResourceID( const kev::ResourceID<_type>& resource )
      {
         this->id = resource.id;
         this->valid = resource.valid;
      }
      bool operator==( const kev::ResourceID<_type>& resource ) const
      {
         return resource.id == this->id;
      }      
      _type id;
      bool valid;
   };
};
  
#endif
