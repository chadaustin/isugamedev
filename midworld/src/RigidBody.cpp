/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Johnathan Gurley, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: RigidBody.cpp,v $
 * Date modified: $Date: 2002-06-24 05:21:54 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/VecOps.h>
#include <gmtl/Generate.h>
#include "RigidBody.h"
#include "cubeGeometry.h"

namespace mw
{
   void RigidBody::update(u64 elapsedTime)
   {
      float dt = static_cast<float>(elapsedTime) / 1000000.0f;

      // Linear momentum
      // 
      gmtl::Vec3f accel = mForce / mMass;
      mVel  += accel * dt;
      mPos  += mVel * dt;

      // Angular momentum
      // w = w0 + at
      // r = r0 + wt
      
   }

   void RigidBody::addForce(const gmtl::Vec3f& force)
   {
      mForce += force;
   }

   void RigidBody::addForce(const gmtl::Vec3f& force, const gmtl::Vec3f& pos)
   {
      mTorque += gmtl::cross(pos, force);
   }

   void RigidBody::draw()
   {
      glPushMatrix();
         glTranslatef(mPos[0], mPos[1], mPos[2]);
         glMultMatrixf( gmtl::make<gmtl::Matrix44f>( mRot ).getData() );
         glScalef(0.5f, 0.5f, 0.5f);
         cubeGeometry().render();
      glPopMatrix();
   }

   const gmtl::AABoxf& RigidBody::getBounds() const
   {
      return mBounds;
   }
}
