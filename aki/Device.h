
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
// File:          $RCSfile: Device.h,v $
// Date modified: $Date: 2002-01-30 06:48:25 $
// Version:       $Revision: 1.6 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////

#ifndef DEVICE
#define DEVICE

#include <string>
#include "Input.h"
class Device
{
public:
   Device() {}
   virtual ~Device() {}
   virtual Input* getInput( const std::string& s ) = 0;
   virtual Input* getInput( const int& id ) = 0;
   virtual void update() = 0;
};

template< typename bok >
class TypedDevice : virtual public Device
{
public:
   TypedDevice() {}
   virtual ~TypedDevice() {}

   void setNumInputs( int n )
   {
      mInput.resize( n );
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
      return &mInput[id];
   }

   virtual void update()
   {
      for (int x = 0; x < mInput.size(); ++x)
      {
         mInput[x].update();
      }
   }

   std::vector< bok > mInput;
   std::map< std::string, unsigned int > mMap;
};

#endif
