/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * File:          $RCSfile: Kernel.cpp,v $
 * Date modified: $Date: 2003-02-03 03:38:28 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include "Kernel.h"
#include "State.h"
#include "StateFactory.h"

namespace siren
{
   Kernel::Kernel()
      : mWidth(0)
      , mHeight(0)
   {}

   Kernel::~Kernel()
   {}

   void
   Kernel::update(float dt)
   {
      // Check if we need to transition to the next state
      if (mNextState)
      {
         mState = mNextState;
      }

      if (mState)
      {
         // Let the current state do its update
         mState->update(dt);

         // Store the transition to the next state
         mNextState = mState->getNext();
      }
   }

   void
   Kernel::draw() const
   {
      if (mState)
      {
         mState->draw();
      }
   }

   StatePtr
   Kernel::getState() const
   {
      return mState;
   }

   void
   Kernel::transitionTo(const std::string& name)
   {
      mNextState = StateFactory::getInstance().create(name);
   }

   void
   Kernel::resize(int width, int height)
   {
      mWidth  = width;
      mHeight = height;
   }

   void
   Kernel::onKeyPress(SDLKey sym, bool down)
   {
      mState->onKeyPress(sym, down);
   }

   void
   Kernel::onMousePress(Uint8 button, bool down, int x, int y)
   {
      mState->onMousePress(button, down, x, y);
   }

   void
   Kernel::onMouseMove(int x, int y)
   {
      mState->onMouseMove(x, y);
   }

   bool
   Kernel::shouldQuit()
   {
      if (mState)
      {
         return mState->isQuitting();
      }
      return false;
   }

   int
   Kernel::getWidth() const
   {
      return mWidth;
   }

   int
   Kernel::getHeight() const
   {
      return mHeight;
   }
}
