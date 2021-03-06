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
 * File:          $RCSfile: Application.h,v $
 * Date modified: $Date: 2002-12-03 06:50:44 $
 * Version:       $Revision: 1.10 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_APPLICATION_H
#define MW_APPLICATION_H

#include <SDL.h>
#include "State.h"
#include "Types.h"

namespace mw
{
   class Application
   {
   public:
      Application();
      ~Application();

      /// elapsedTime is in milliseconds
      void update(u64 elapsedTime);

      void draw();
      void resize(int width, int height);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      bool shouldQuit();
      
      int getWidth() const { return mWidth; }
      int getHeight() const { return mHeight; }
      
   private:
      int mWidth;
      int mHeight;
      State* mState;

      /// The state to switch to the next time the app is updated
      State* mNextState;
   };
}

#endif
