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
 * File:          $RCSfile: GameScene.h,v $
 * Date modified: $Date: 2002-09-24 04:43:37 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cubeGeometry.h"
#include "Texture.h"

namespace mw
{

   class GameScene
   {
   public:
      GameScene()
      {
         mTexture = new Texture("images/ground.png");
      }

      ~GameScene()
      {
         delete mTexture;
      }

      void draw()
      {
         /** draw the scene. */
         static cubeGeometry cube;

         const int size = 500;
         const int spacing = 10;
         const int spacing_2 = spacing / 2;
         for (int x = -size; x < size; x += spacing)
         {
            for (int y = -size; y < size; y += spacing)
            {
               glPushMatrix();
               glRotatef(90, 1, 0, 0);
               mTexture->drawRectangle(
                  x - spacing_2, y - spacing_2,
                  x + spacing_2, y + spacing_2);
               glPopMatrix();
            }
         }

         const float pillar_height = 0.5f;
         const float pillar_width = 0.4f;
         const int size_2 = 100 / 2;
         for (int x = -size_2; x < size_2; x += spacing)
         {
            for (int y = -size_2; y < size_2; y += spacing)
            {
               glPushMatrix();
               glTranslatef( (GLfloat)x, pillar_height, (GLfloat)y );
               glScalef( pillar_width, pillar_height, pillar_width );
               if (!(x == 0 && y == 0))
                  cube.render();
               glPopMatrix();
            }
         }
      }

   private:
      Texture* mTexture;
   };

}

#endif
