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
 * Date modified: $Date: 2002-07-29 03:36:48 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_CURSOR_H
#define MW_CURSOR_H

#include "cubeGeometry.h" // for default draw method

namespace mw
{
   /// virtual cursor, hides system sursor, shows opengl cursor
   class Cursor
   {
   public:
      Cursor()
      {
         this->init( 640, 480 );
      }
      
      virtual ~Cursor()
      {
      }
      
      float getX() const { return mMousePosX; }
      float getY() const { return mMousePosY; }
      
      virtual void init( int w, int h )
      {
         mMousePosX = w / 2;
         mMousePosY = h / 2;
         mNeedWarp = true;
         
         // init the system mouse state...
         ::SDL_WarpMouse( w / 2, h / 2 );
         ::SDL_ShowCursor( SDL_DISABLE );
      }      
      
      /// overload this to draw your custom image.
      virtual void draw( int w, int h )
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
            glTranslatef( mMousePosX, mMousePosY, 0 );
            glScalef( 3.0f, 3.0f, 3.0f );
            cubeGeometry().render();
            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
         glPopMatrix();
      }    
      
      virtual void update( int w, int h )
      {
         // keep track of the mouse cursor...
         if (mNeedWarp)
         {
            ::SDL_WarpMouse( w / 2, h / 2 );
            mNeedWarp = false;
         }
      }  
      
      virtual void onMouseMove( int w, int h, int x, int y )
      {
         // keep track of the game-draw virtual cursor
         mNeedWarp = true;
         x -= w / 2;
         y -= h / 2;
         mMousePosX += x;
         mMousePosY += y;

         // constrain virtual cursor
         if (mMousePosX < 0) mMousePosX = 0;
         if (w < mMousePosX) mMousePosX = w;
         if (mMousePosY < 0) mMousePosY = 0;
         if (h < mMousePosY) mMousePosY = h;
      }    
      
   private:
      // cursor
      float mMousePosX, mMousePosY;
      bool mNeedWarp;
   }; 
}

#endif
