
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
// File:          $RCSfile: EventInput.h,v $
// Date modified: $Date: 2003-02-09 07:43:03 $
// Version:       $Revision: 1.14 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_EVENTINPUT_H
#define GK_EVENTINPUT_H

#include <gk/gkCommon.h>
#include <vector>
#include <gk/DigitalInput.h>
#include <gk/AnalogInput.h>

namespace gk {

/** helper class, don't use directly.  for use by GameInput...
 */
class GK_DLL EventInput : public DigitalInput, AnalogInput
{
public:
   EventInput() : DigitalInput(), AnalogInput()
   {
   }
   virtual ~EventInput() {}
   virtual void update() {}
   virtual float data() const
   {
      if (mAnalogBindings.size() > 0)
      {
         return mAnalogBindings[0]->data();
      }
      else
      {
         return 0.0f;
      }
   }

   virtual EdgeTriggerState edgeState() const
   {
      DigitalInput::EdgeTriggerState state = DigitalInput::UP;
      for (unsigned int x = 0; x < mDigitalBindings.size(); ++x)
      {
         if (state == DigitalInput::UP)
         {
            switch (mDigitalBindings[x]->edgeState())
            {
               case DigitalInput::UP: state = DigitalInput::UP; break;
               case DigitalInput::EDGE_UP: state = DigitalInput::EDGE_UP; break;
               case DigitalInput::EDGE_DOWN: state = DigitalInput::EDGE_DOWN; break;
               case DigitalInput::DOWN: state = DigitalInput::DOWN; break;
            }
         }
         else if (mDigitalBindings[x]->edgeState() == DigitalInput::DOWN)
         {
            state = DigitalInput::DOWN;
         }
         else if (mDigitalBindings[x]->edgeState() == DigitalInput::EDGE_DOWN &&
                  state != DigitalInput::DOWN)
         {
            state = DigitalInput::EDGE_DOWN;
         }
      }
      return state;
   }

protected:

   friend class GameInput;

   void add( Input* in_put )
   {
      if (in_put)
      {
         DigitalInput* dig = dynamic_cast<DigitalInput*>( in_put );
         if (dig)
         {
            mDigitalBindings.push_back( dig );
         }
         AnalogInput* ana = dynamic_cast<AnalogInput*>( in_put );
         if (ana)
         {
            mAnalogBindings.push_back( ana );
         }
      }
   }

   void clear()
   {
      mAnalogBindings.clear();
      mDigitalBindings.clear();
   }

   std::vector< AnalogInput* > mAnalogBindings;
   std::vector< DigitalInput* > mDigitalBindings;
};

} // namespace gk

#endif
