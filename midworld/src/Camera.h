/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

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
         glTranslatef( mPos[0], mPos[1] - 30, mPos[2] );
      }
   private:
      gmtl::Vec3f mPos;
   };

}

#endif
