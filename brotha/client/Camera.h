/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
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
 * File:          $RCSfile: Camera.h,v $
 * Date modified: $Date: 2002-04-28 16:41:03 $
 * Version:       $Revision: 1.2 $
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
#ifndef CLIENT_CAMERA_H
#define CLIENT_CAMERA_H

#include <osg/Vec3>
#include <osg/Quat>
#include <osg/Matrix>

namespace client {
   /**
    * Springy chase camera.
    */
   class Camera
   {
   public:
      /**
       * Creates a new camera at the origin targeting the origin with a follow
       * distance and pitch of 0.
       */
      Camera();

      /// Destroys this camera.
      ~Camera();

      /**
       * Updates the position of the camera based on the given amount of time
       * that has passed since the last update frame.
       *
       * @param delta      the amount of time that has passed in millisecs
       */
      void update(float delta);

      /**
       * @todo comment me
       */
      void setTarget(const osg::Vec3& pos, const osg::Quat& rot);

      /**
       * Sets the distance at which the camera follows the target.
       *
       * @param dist    the follow distance
       */
      void setFollowDist(float dist);

      /**
       * Gets the distance at which the camera follows the target.
       *
       * @return  the follow distance
       */
      float getFollowDist() const;

      /**
       * Sets the pitch at which the camera looks upon the target.
       *
       * @param angle      the pitch angle in radians
       */
      void setPitch(float angle);

      /**
       * Gets the pitch at which the camera looks upon the target.
       *
       * @return  the pitch angle in radians
       */
      float getPitch() const;

      /**
       * Sets whether this camera should follow the target or be at the target.
       *
       * @param follow     true to follow the target
       */
      void setFollow(bool follow);

      /**
       * Gets whether this camera should follow the target or be at the target.
       *
       * @return  true if the camera is following the target; false otherwise
       */
      bool getFollow() const;

      /// Gets the current position of the camera.
      const osg::Vec3& getCurrentPos() const
      {
         return mCurPos;
      }

      /// Gets the current rotation of the camera.
      const osg::Quat& getCurrentRot() const
      {
         return mCurRot;
      }

      /**
       * Gets the computed transform for this camera.
       */
      const osg::Matrix& getTransform() const
      {
         return mXForm;
      }

   private:
      /// The position of the object we're following
      osg::Vec3 mTargetPos;
      /// The rotation of the object we're following
      osg::Quat mTargetRot;

      /// The current position of the camera
      osg::Vec3 mCurPos;
      /// The current rotation of the camera
      osg::Quat mCurRot;

      /**
       * The transform used to describe the camera's orientation. The inverse
       * of this matrix should be applied to the view matrix before anything is
       * drawn to the screen.
       */
      osg::Matrix mXForm;

      /// The distance at which the camera follows the target
      float mFollowDist;

      /// The pitch at which the camera looks upon the target in radians
      float mPitch;

      /// Whether or not the camera should follow the target
      bool mFollow;
   };
}

#endif
