
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
// File:          $RCSfile: DigitalInput.h,v $
// Date modified: $Date: 2002-02-06 22:22:22 $
// Version:       $Revision: 1.8 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include "gk/gkCommon.h"
#include "gk/Input.h"
#include <assert.h>

class DigitalInput : virtual public Input
{
public:
   virtual ~DigitalInput() {}

   enum BinaryState
   {
      ON, OFF
   };
   enum EdgeTriggerState
   {
      DOWN, EDGE_DOWN, EDGE_UP, UP, FLOATING
   };

   DigitalInput() : mEdge( UP ), mBinary( OFF )
   {
   }

   virtual EdgeTriggerState edgeState() const
   {
      return mEdge;
   }

   const BinaryState& binaryState() const
   {
      return mBinary;
   }

   void setBinaryState( const BinaryState& bs )
   {
      mBinary = bs;
   }

   virtual void update()
   {
      //find out if...
      switch( mBinary )
      {
      case ON:
         //button has been held down or it is just down.
         switch( mEdge )
         {
         case FLOATING:
         case EDGE_UP:
         case UP:       mEdge = EDGE_DOWN;  break;
         case EDGE_DOWN: mEdge = DOWN; break;
         }
      break;

      case OFF:
         //button has been up or it is just up.
         switch( mEdge )
         {
         case FLOATING:
         case EDGE_DOWN:
         case DOWN:    mEdge = EDGE_UP; break;
         case EDGE_UP:  mEdge = UP; break;
         }
      break;

      default:
         //std::cout<<"broken on key: "<<x<<" of "<<mBinarys.size()<<" == "<<mBinarys[x]<<"\n"<<std::flush;
         assert(false);
      }
   }

private:
   EdgeTriggerState mEdge;
   BinaryState mBinary;
};

#endif
