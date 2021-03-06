
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: TypedDevice.h,v $
// Date modified: $Date: 2002-03-21 05:57:16 $
// Version:       $Revision: 1.1 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_DEVICE_H
#define GK_DEVICE_H

#include <gk/gkCommon.h>
#include <string>
#include <vector>
#include <map>
#include <gk/IDevice.h>

namespace gk {

template< typename INPUT_TYPE >
class TypedDevice : virtual public DLLImpl< IDevice >
{
public:
   typedef INPUT_TYPE InputType;

protected:
   TypedDevice() {}

public:
   virtual ~TypedDevice() {}

   void setNumInputs( int n )
   {
      mInput.resize( n );
   }

   /**
    * Get the number of inputs for this device.
    *
    * @return  the number of inputs
    */
   int numInputs() const
   {
      return mInput.size();
   }

   virtual Input* getInput( const std::string& input_name )
   {
      int k = 0;
      if (mMap.count( input_name ) > 0)
      {
         k = (*(mMap.find( input_name ))).second;
         return &mInput[k];
      }
      else
         return NULL;
   }

   virtual Input* getInput( const int& id )
   {
      assert( ((unsigned int)id) < mInput.size() && "out of bounds." );
      return &mInput[id];
   }

   virtual void update()
   {
      for (unsigned int x = 0; x < mInput.size(); ++x)
      {
         mInput[x].update();
      }
   }

   std::vector< INPUT_TYPE > mInput;
   std::map< std::string, unsigned int > mMap;
};

}

#endif
