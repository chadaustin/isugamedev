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
 * File:          $RCSfile: cubeGeometry.h,v $
 * Date modified: $Date: 2002-07-07 02:21:11 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef CUBE_GEOM___
#define CUBE_GEOM___

#ifdef WIN32
#  include <windows.h>
#endif
#include <GL/gl.h>

class cubeGeometry
{
public:
   // number of verticies
   // this can be passed to opengl's glDrawArrays( .., .. );
   unsigned int size() const { return cubeGeometry::mSize; }

   // format is: T2F_C4F_N3F_V3F
   float* data() { return (float*)cubeGeometry::mData; }
   const float* data() const { return (float*)cubeGeometry::mData; }

   void render() const
   {
      glEnable( GL_VERTEX_ARRAY );
      glInterleavedArrays( GL_T2F_C4F_N3F_V3F, 0, (float*)mData ); //GL_T2F_C4F_N3F_V3F format
      glDrawArrays( GL_TRIANGLES, 0, mSize );
   }

private:
   static const unsigned int mSize;
   static const float mData[432];
};

#endif
