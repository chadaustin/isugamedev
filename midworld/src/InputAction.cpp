/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: InputAction.cpp,v $
 * Date modified: $Date: 2002-11-05 21:22:16 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "InputAction.h"

namespace mw
{
   InputAction::InputAction()
   {
      mPressCount = 0;
      mLastPressCount = 0;
      mEdgeState = 0;
   }
   
   void InputAction::onPress(bool down)
   {
      down ?
         ++mPressCount :
         --mPressCount;
   }
   
   void InputAction::update(float /*dt*/)
   {
      mEdgeState = (mPressCount != 0) - (mLastPressCount != 0);
      mLastPressCount = mPressCount;
   }
   
   bool InputAction::isActive()
   {
      return (mPressCount != 0);
   }

   int InputAction::getEdgeState()
   {
      return mEdgeState;
   }
}
