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
 * File:          $RCSfile: Camera.h,v $
 * Date modified: $Date: 2002-07-07 02:21:10 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#ifndef CAMERA_H
#define CAMERA_H

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

namespace mw
{
   class Camera
   {
   public:
      Camera() : mPos() 
      {
      }
      
      void setPlayerPos( const gmtl::Vec3f& pos )
      {
         mPos = -pos;
      }
      
      void update( float timeDelta )
      {
      }
      
      void draw()
      {
         glRotatef( 90, 1,0,0 );
         glTranslatef( mPos[0], mPos[1] - 20, mPos[2] );
      }
   private:
      gmtl::Vec3f mPos;
   };

}

#endif
