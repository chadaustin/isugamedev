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
 * Date modified: $Date: 2002-10-30 15:53:03 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_CAMERA_H
#define MW_CAMERA_H

#include <gmtl/Matrix.h>
#include <gmtl/Point.h>
#include <gmtl/Quat.h>

namespace mw
{
   /**
    * This camera will "chase" a target position/orientation.
    */
   class Camera
   {
   public:
      /**
       * Creates a new Camera looking at the origin from 20 units up the y-axis.
       */
      Camera();

      /**
       * Sets the target position and rotation for the camera. The camera will
       * attempt to move to the target position and orient itself to the target
       * rotation. The camera will also take into account its added follow
       * distance and yaw/pitch angles.
       *
       * @param pos     the target position
       * @param rot     the target rotation
       */
      void setTarget(const gmtl::Point3f& pos, const gmtl::Quatf& rot);

      /**
       * Updates the state of this camera based on the amount of time that has
       * passed since the last update. This camera will position itself halfway
       * to the destination position and rotation on each call to update based
       * on its current position and rotation.
       *
       * @param dt      the amount of time that passed in seconds
       */
      void update(float dt);

      void draw();

      /**
       * Sets the distance by which this camera should follow the target
       * position.
       *
       * @param distance   the follow distance
       */
      void setFollowDistance(float distance);
      
      /**
       * Sets the maximum following distance of the camera
       *
       * @param max        the maximum following distance
       */
      void setMaxFollowDistance(float max);

      /**
       * Sets the minimum following distance of the camera
       *
       * @param min        the minimum following distance
       */
      void setMinFollowDistance(float min);

      /**
       * Sets the velocity by which the follow distance should change.
       *
       * @param vel        the velocity of the follow distance
       */
      void setFollowDistanceVel(float vel);


      /**
       * Gets the pitch angle this camera adds to the target rotation.
       *
       * @return  the pitch angle in radians
       */
      float getPitch() const;

      /**
       * Sets the pitch angle this camera will add to the target rotation.
       *
       * @param angle      the pitch angle in radians
       */
      void setPitch(float angle);
      
      /**
       * Sets the maximum pitch angle this camera will rotate to.
       *
       * @param max        the maximum pitch angle in radians
       */
      void setMaxPitch(float max);
      
      /**
       * Sets the minimum pitch angle this camera will rotate to.
       *
       * @param min        the minimum pitch angle in radians
       */
      void setMinPitch(float min);

      /**
       * Sets the angular velocity by which the pitch angle should change.
       *
       * @param vel        the angular velocity of the pitch angle
       */
      void setPitchVel(float vel);

      /**
       * Gets the position of this camera in world coordinates.
       */
      gmtl::Vec3f getPos() const;

   private:
      gmtl::Point3f mTargetPos;
      gmtl::Point3f mLastTargetPos;

      gmtl::Quatf mTargetRot;
      gmtl::Quatf mLastTargetRot;

      // The distance by which the camera is following the target.
      float mFollowDistance;
      float mFollowDistanceVel;
      // The bounds on the camera's following distance
      float mMaxFollowDistance;
      float mMinFollowDistance;

      float mPitch;
      float mPitchVel;

      // The bounds on the camera's pitch
      float mMaxPitch;
      float mMinPitch;

      // Cache of the current transform for the location of the camera.
      gmtl::Matrix44f mTransform;
   };

}

#endif
