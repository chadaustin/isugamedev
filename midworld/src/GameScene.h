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
            const int size = 500;
            const int spacing = 10;
            for (int x = -size; x < size; x += spacing)
            {
               glVertex3f( -size, 0, x );
               glVertex3f(  size, 0, x );
               glVertex3f( x, 0, -size );
               glVertex3f( x, 0,  size );
            }
         glEnd();

         const float pillar_height = 0.5;
         const float pillar_width = 0.4;
         const int size_2 = 500 / 2;
         for (int x = -size_2; x < size_2; x += spacing)
         {
            for (int y = -size_2; y < size_2; y += spacing)
            {
               glPushMatrix();
               glTranslatef( x, pillar_height, y );
               glScalef( pillar_width, pillar_height, pillar_width );
               if (!(x == 0 && y == 0))
                  cube.render();
               glPopMatrix();
            }
         }
      }
   };

}

#endif
