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
 * File:          $RCSfile: Camera.cpp,v $
 * Date modified: $Date: 2002-09-23 04:00:11 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/Generate.h>
#include <gmtl/QuatOps.h>
#include <SDL_opengl.h>
#include "Camera.h"

namespace mw
{
   Camera::Camera()
      : mTargetPos()
      , mLastTargetPos()
      , mTargetRot()
      , mLastTargetRot()
      , mFollowDistance(20)
      , mFollowDistanceVel(0)
      , mYaw(0)
      , mYawVel(0)
      , mPitch(gmtl::Math::deg2Rad(90.0f))
      , mPitchVel(0)
      , mTransform()
   {}

   void
   Camera::setTarget(const gmtl::Point3f& pos, const gmtl::Quatf& rot)
   {
      mTargetPos = pos;
      mTargetRot = rot;
   }

   void
   Camera::update(float dt)
   {
      // Calculate our state updates assuming that our dt is twice as large so
      // that we get the impression that the camera moves half the distance.
      float camera_time = 2.0 * dt;

      // Calculate the new rotation
      gmtl::Quatf new_rot;
      gmtl::slerp(new_rot, camera_time, mLastTargetRot, mTargetRot);
      mLastTargetRot = new_rot;

      // Calculate the new position
      gmtl::Point3f new_pos;
      gmtl::lerp(new_pos, camera_time, mLastTargetPos, mTargetPos);
      mLastTargetPos = new_pos;

      // Calculate the matrix for the target location
      gmtl::CoordVec3AxisAnglef target_coord(
            new_pos,
            gmtl::make<gmtl::AxisAnglef>(new_rot));

      mTransform = gmtl::make<gmtl::Matrix44f>(target_coord);

      // Apply the camera's offset information
      mTransform *= gmtl::makeRot<gmtl::Matrix44f>(gmtl::AxisAnglef(-mYaw, gmtl::Vec3f(0,1,0)));
      mTransform *= gmtl::makeRot<gmtl::Matrix44f>(gmtl::AxisAnglef(-mPitch, gmtl::Vec3f(1,0,0)));
      mTransform *= gmtl::makeTrans<gmtl::Matrix44f>(gmtl::Vec3f(0,0,mFollowDistance));
      
//      gmtl::makeTrans<gmtl::Matrix44f>(target_mat, new_pos);
//      target_mat *= gmtl::makeRot<gmtl::Matrix44f>(

      // Update yaw, pitch, and follow distance by their velocities
      mYaw              += mYawVel * dt;
      mPitch            += mPitchVel * dt;
      mFollowDistance   += mFollowDistanceVel * dt;
   }

   void
   Camera::draw()
   {
      gmtl::Matrix44f cam_inv = gmtl::makeInverse(mTransform);
      glMultMatrixf(cam_inv.getData());

//      glRotatef( 90, 1,0,0 );
//      glTranslatef( mPos[0], mPos[1] - mDistance, mPos[2] );
   }

   void
   Camera::setFollowDistance(float distance)
   {
      mFollowDistance = distance;
   }

   void
   Camera::setFollowDistanceVel(float vel)
   {
      mFollowDistanceVel = vel;
   }

   void
   Camera::setYaw(float angle)
   {
      mYaw = angle;
   }

   void
   Camera::setYawVel(float vel)
   {
      mYawVel = vel;
   }

   void
   Camera::setPitch(float angle)
   {
      mPitch = angle;
   }

   void
   Camera::setPitchVel(float vel)
   {
      mPitchVel = vel;
   }

   gmtl::Vec3f
   Camera::getPos() const
   {
      return gmtl::makeTrans<gmtl::Vec3f>(mTransform);
   }
}
