
//////////////////////////////////////////////////////////////////
//
//                         -=     ContextManager     =-
//
// Definition: "a lookup for resource ID (context sensative)"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ContextManager.h,v $
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
#ifndef CONTEXT_MANAGER_
#define CONTEXT_MANAGER_

#include <map>
#include <vector>
#include "Singleton.h"
#include "ResourceID.h"

// context sensative resource ID lookup
class ContextManager : public kev::Singleton<ContextManager>
{
public:
   ContextManager() : mCurrentBindLookup( NULL ), mContext( 9934999 )
   {
   }

   inline void setContext( int id )
   {  
      mContext = id;
    
      mCurrentBindLookup = &mBindLookupByContext[id];
      if (mCurrentBindLookup->size() == 0)
      {
         unsigned short max_cap = 0; max_cap--;
         mCurrentBindLookup->resize( max_cap );
      }
   }
   
   inline int context() { return mContext; }
   
   inline void associate( const kev::ResourceID<unsigned short>& resource, const kev::ResourceID<unsigned int>& value )
   {
      assert( mCurrentBindLookup != NULL );
      assert( resource.id < (*mCurrentBindLookup).size() );
      (*mCurrentBindLookup)[resource.id] = value;
   }   

   inline const kev::ResourceID<unsigned int>& lookup( const kev::ResourceID<unsigned short>& resource )
   {
      assert( mCurrentBindLookup != NULL );
      assert( resource.id < (*mCurrentBindLookup).size() );
      return (*mCurrentBindLookup)[resource.id];
   }   
   
   int mContext;
   std::vector<kev::ResourceID<unsigned int> >* mCurrentBindLookup;
   
   // vector = mBindIDs[context]
   // openglbindID = vector[imageHandle]
   std::map<int, std::vector<kev::ResourceID<unsigned int> > > mBindLookupByContext;
};

#endif
