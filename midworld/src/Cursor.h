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
 * File:          $RCSfile: Cursor.h,v $
 * Date modified: $Date: 2002-10-26 05:04:34 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_CURSOR_H
#define MW_CURSOR_H

#include <gmtl/Point.h>
#include <gmtl/VecOps.h>
#include "cubeGeometry.h" // for default draw method

namespace gmtl
{
   typedef Point<float, 2> Point2f;
}

namespace mw
{
   /**
    * Describes a virtual cursor that hides the system cursor. It mimics the
    * system cursor, but is not allowed to leave the confines of the active
    * window. OpenGL is used to draw the virtual cursor on top of the
    * application.
    */
   class Cursor
   {
   public:
      Cursor()
      {
         init(640, 480);
      }

      virtual ~Cursor()
      {}

      /**
       * Gets the position of the cursor for this frame.
       */
      const gmtl::Point2f& getPos() const { return mMousePos; }

      /**
       * Gets the position of the cursor during the last frame.
       */
      const gmtl::Point2f& getLastPos() const { return mLastMousePos; }

      virtual void init(int w, int h)
      {
         mLastMousePos[0] = mMousePos[0] = w / 2.0f;
         mLastMousePos[0] = mMousePos[1] = h / 2.0f;
         mNeedWarp = true;

         // init the system mouse state...
         SDL_WarpMouse(w / 2, h / 2);
         SDL_ShowCursor(SDL_DISABLE);
      }

      /// overload this to draw your custom image.
      virtual void draw(int w, int h)
      {
         // draw cursor (dumb)
         glPushMatrix();
         glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, w, h, 0, 300, -300);
         glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(mMousePos[0], mMousePos[1], 0 );
            glScalef(3.0f, 3.0f, 3.0f);
            cubeGeometry().render();
            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
         glPopMatrix();
      }

      virtual void update(int w, int h)
      {
         // keep track of the mouse cursor...
         if (mNeedWarp)
         {
            ::SDL_WarpMouse(w / 2, h / 2);
            mNeedWarp = false;
         }

         mLastMousePos = mMousePos;
      }

      virtual void onMouseMove(int w, int h, int x, int y)
      {
         // keep track of the game-draw virtual cursor
         mNeedWarp = true;
         x -= w / 2;
         y -= h / 2;
         mMousePos[0] += x;
         mMousePos[1] += y;

         // constrain virtual cursor
         if (mMousePos[0] < 0)   mMousePos[0] = 0;
         if (w < mMousePos[1])   mMousePos[0] = float(w);
         if (mMousePos[1] < 0)     mMousePos[1] = 0;
         if (h < mMousePos[1])   mMousePos[1] = float(h);
      }

   private:
      /**
       * Location of the cursor on the screen relative to the upper-left corner
       * of the window.
       */
      gmtl::Point2f mMousePos;

      /**
       * Location of the cursor on the screen during the last update.
       */
      gmtl::Point2f mLastMousePos;

      /// Flag for whether we need to warp the cursor on the next update.
      bool mNeedWarp;
   };
}

#endif
