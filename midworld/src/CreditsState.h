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
 * File:          $RCSfile: CreditsState.h,v $
 * Date modified: $Date: 2002-07-07 03:10:59 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#ifndef MW_CREDITS_STATE_H
#define MW_CREDITS_STATE_H

#include <vector>
#include "State.h"
#include "Texture.h"
#include "MenuState.h"

namespace mw
{
   class Application;
   class CreditsState : public State
   {
   public:
      CreditsState( Application* );

      ~CreditsState()
      {
         std::vector<Texture*>::iterator itr;
         for (itr = mImages.begin(); itr != mImages.end(); ++itr)
         {
            delete *itr;
         }
         mImages.clear();
      }

      void update(float dt) {}

      void draw()
      {
         glEnable(GL_TEXTURE_2D);
         glDisable(GL_DEPTH_TEST);
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

         glClear(GL_COLOR_BUFFER_BIT);

         /// @todo  we assume 640x480...  :(

         // set up projection matrix
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         glOrtho(0, 640, 480, 0, -1, 1);

         // set up view matrix
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();

         glColor4f(1, 1, 1, 1);
         mImages[0]->drawRectangle(0,0,640,480);	// draw background
      }

      void onKeyPress(SDLKey sym, bool down)
      {
         if (down)
         {
            invokeTransition(new MenuState( &this->application() ));
         }
      }
      void onMousePress(Uint8 button, bool down, int x, int y) {}
      void onMouseMove(int x, int y) {}

   private:
      std::vector<Texture*> mImages;
   };
}

#endif
