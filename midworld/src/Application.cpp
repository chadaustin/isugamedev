/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Johnathan Gurley, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: Application.cpp,v $
 * Date modified: $Date: 2002-06-10 03:39:04 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <SDL/SDL_opengl.h>
#include "Application.h"
#include "IntroState.h"

namespace mw {

   Application::Application()
   {
      mWidth  = 0;
      mHeight = 0;
      mState  = new IntroState();
   }

   Application::~Application()
   {
      /// @todo  think about state management: who owns the memory? 
      ///        are states allocated in a pool?  should states even
      ///        have state or should they be purely behavior?
      delete mState;
   }

   void
   Application::update(u64 elapsedTime)
   {
      mState->update(elapsedTime);
   }

   void
   Application::draw()
   {
      mState->draw();
   }

   void
   Application::resize(int width, int height)
   {
      mWidth  = width;
      mHeight = height;
   }

   void
   Application::onKeyPress(SDLKey sym, bool down)
   {
      mState->onKeyPress(sym, down);
   }

   void
   Application::onMousePress(Uint8 button, bool down, int x, int y)
   {
      mState->onMousePress(button, down, x, y);
   }

   void
   Application::onMouseMove(int x, int y)
   {
      mState->onMouseMove(x, y);
   }

   bool
   Application::shouldQuit()
   {
      return mState->isQuitting();
   }

}
