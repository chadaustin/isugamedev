/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Camera.cpp,v $
 * Date modified: $Date: 2002-04-24 10:43:53 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
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
 ************************************************************ brotha-cpr-end */
#include "Camera.h"
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Convert.h>
#include <gmtl/Generate.h>

namespace client {
   Camera::Camera()
      : mTargetPos(0,0,0)
      , mTargetRot(0,0,0)
      , mCurPos(0,0,-30)
      , mCurRot(0,0,0)
      , mFollowDist(30)
      , mPitch(0.50)
      , mFollow(true)
   {}

   Camera::~Camera()
   {}

   void Camera::update(float delta)
   {
      if (mFollow)
      {
         // Only go half the distance per second to the target
         float lerpDist = 2.0f * delta;

         // Slerp to the new rotation
         gmtl::Quatf newRot;
         gmtl::slerp(newRot, lerpDist, mCurRot, mTargetRot);
         mCurRot = newRot;

         // Lerp to the new position
         gmtl::Vec3f newPos;
         gmtl::lerp(newPos, lerpDist, mCurPos, mTargetPos);
         mCurPos = newPos;

         // Compute the matrix transform for the camera's lerped target
//         gmtl::convert(mXForm, mTargetRot);
//         gmtl::setTrans(mXForm, mTargetPos);
         gmtl::convert(mXForm, mCurRot);
         gmtl::setTrans(mXForm, mCurPos);

         // Take into account the follow distance and pitch
         gmtl::Matrix44f trans, pitchRot;
         trans = gmtl::makeTrans(gmtl::Vec3f(0,0,mFollowDist), gmtl::Type2Type<gmtl::Matrix44f>());
         pitchRot = gmtl::makeRot(-mPitch, gmtl::Vec3f(1,0,0), gmtl::Type2Type<gmtl::Matrix44f>());

//         mXForm = ( pitchRot * trans);
         mXForm *= ( pitchRot * trans);
      }
      else
      {
         gmtl::convert(mXForm, mTargetRot);
         gmtl::setTrans(mXForm, mTargetPos);
      }
   }

   void Camera::setTarget(const gmtl::Vec3f& pos, const gmtl::Quatf& rot)
   {
      mTargetPos = pos;
      mTargetRot = rot;
   }

   void Camera::setFollowDist(float dist)
   {
      mFollowDist = dist;
   }

   float Camera::getFollowDist() const
   {
      return mFollowDist;
   }

   void Camera::setPitch(float pitch)
   {
      mPitch = pitch;
   }

   float Camera::getPitch() const
   {
      return mPitch;
   }

   void Camera::setFollow(bool follow)
   {
      mFollow = follow;
   }

   bool Camera::getFollow() const
   {
      return mFollow;
   }
}
