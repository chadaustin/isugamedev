/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cubeGeometry.h"

namespace mw
{

   class GameScene
   {
   public:
      inline void draw()
      {
         /** draw the scene. */
         static cubeGeometry cube;

         glBegin( GL_LINES );
            for (int x = -1000; x < 1000; x += 50)
            {
               glVertex3f( -1000, 0, x );
               glVertex3f(  1000, 0, x );
               glVertex3f( x, 0, -1000 );
               glVertex3f( x, 0,  1000 );
            }
         glEnd();

         const float height = 3;
         for (int x = -500; x < 500; x += 50)
         {
            for (int y = -500; y < 500; y += 50)
            {
               glPushMatrix();
               glTranslatef( x, height, y );
               glScalef( 3, height, 3 );
               if (!(x == 0 && y == 0))
                  cube.render();
               glPopMatrix();
            }
         }
      }
   };

}

#endif
