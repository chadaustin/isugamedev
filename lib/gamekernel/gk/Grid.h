
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: Grid.h,v $
// Date modified: $Date: 2002-01-31 06:13:17 $
// Version:       $Revision: 1.4 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GRID_H
#define GRID_H

#include "akiCommon.h"

class Grid
{
public:
   Grid()
   {
      size = 10;
      this->setPos( 0.0f, 0.0f, 0.0f );
      this->setColor( 0.3f, 0.2f, 0.6f );
   }
   void draw()
   {
      glColor3f( color[0], color[1], color[2] );
      glPushMatrix();
      glTranslatef( position[0], position[1], position[2] );
      glBegin( GL_LINES );
         for ( float x = -size; x < size; ++x)
         {
            glVertex3f( -size, 0, x );
            glVertex3f(  size, 0, x );
            glVertex3f( x, 0, -size );
            glVertex3f( x, 0,  size );
         }
      glEnd();
      glPopMatrix();
   }
   float size;
   void setPos( float x, float y, float z )
   {
      position[0] = x;
      position[1] = y;
      position[2] = z;
   }
   void setColor( float r, float g, float b )
   {
      color[0] = r;
      color[1] = g;
      color[2] = b;
   }
   float position[3];
   float color[3];
};

#endif
