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
 * File:          $RCSfile: RigidBody.h,v $
 * Date modified: $Date: 2002-11-06 01:40:14 $
 * Version:       $Revision: 1.23 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_RIGID_BODY_H
#define MW_RIGID_BODY_H

#include <gmtl/AABox.h>
#include <gmtl/Point.h>
#include <gmtl/VecOps.h>
#include <gmtl/Quat.h>
#include <gmtl/Matrix.h>
#include "BodyState.h"

namespace mw
{
   /**
    * @ingroup Physics
    *
    * A physical body that cannot be deformed. All units are in SI units.
    */
   class RigidBody
   {
   public:

      RigidBody()
         : mMass( 1.0f )
         , mBounds(gmtl::Point3f(0,0,0), gmtl::Point3f(1,1,1))
      {
         mIsCollidable = true;
      }
      
      virtual ~RigidBody() {}

      /**
       * Sets the position of this rigid body relative to the world's origin.
       */
      void setPos(const gmtl::Point3f& pos)
      {
         getCurrentState().setPos(pos);
      }

      /**
       * Gets the position of this rigid body relative to the world's origin.
       */
      const gmtl::Point3f& getPos() const { return getCurrentState().getPos(); }
      gmtl::Point3f& getPos() { return getCurrentState().getPos(); }

      void setScale(const gmtl::Vec3f& scale) { getCurrentState().setScale(scale); }
      

      const gmtl::Vec3f& getScale() const { return getCurrentState().getScale(); }
      gmtl::Vec3f& getScale() { return getCurrentState().getScale(); }


	  /**
       * Sets the velocity of this rigid body.
       */
      void setVel(const gmtl::Vec3f& vel) { getCurrentState().setVel(vel); }

      /**
       * Gets the velocity of this rigid body.
       */
      const gmtl::Vec3f& getVel() const { return getCurrentState().getVel(); }

      /**
       * Applies a force on this body at its center of mass. This will not add
       * any torque on the body.
       *
       * @param force      the force to apply
       */
      void addForce(const gmtl::Vec3f& force);

      /// Gets the total force currently acting on this body.
      const gmtl::Vec3f& getForce() const { return mForce; }

      /// Gets the total torque currently acting on this body.
      const gmtl::Vec3f& getTorque() const { return mTorque; }

      /**
       * Sets the rotation of this rigid body.
       */
      void setRot(const gmtl::Quatf& rot) { getCurrentState().setRot(rot); }

      /**
       * Gets the rotation of this rigid body.
       */
      const gmtl::Quatf& getRot() const { return getCurrentState().getRot(); }

      /**
       * Sets the angular velocity of this rigid body.
       */
      void setRotVel(const gmtl::Vec3f& rotVel) { return getCurrentState().setRotVel(rotVel); }

      /**
       * Applies a force on this body at a position relative to its center. This
       * will add a torque to the body.
       *
       * @param force      the force to apply
       * @param pos        the vector from the center of the body to the point
       *                   on which the force is being applied
       */
      void addForce(const gmtl::Vec3f& force, const gmtl::Vec3f& pos);

      /**
       * Sets the mass of this body in kg.
       */
      void setMass(float mass) { mMass = mass; }

      /**
       * Gets the mass of this body in kg.
       */
      float getMass() const { return mMass; }

      /**
       * Gets the forward vector for this rigid body.
       */
      gmtl::Vec3f getForward() const;

      /**
       * Updates the internal state of this body given the amount of time that
       * has passed.
       *
       * @param dt      the differtial of time in seconds
       */
      virtual void update(float dt);

      /**
       * Gets the axis-aligned bounding box that tightly contains this body.
       *
       * @return  the bounding volume for this body
       */
      const gmtl::AABoxf& getBounds() const;

      void setBounds(const gmtl::AABoxf& box);

      /** convert the pos/rot to a matrix. */
      gmtl::Matrix44f matrix() const;

      /// Gets the current state of this body.
      BodyState& getCurrentState() { return mCurrentState; }
      const BodyState& getCurrentState() const { return mCurrentState; }

      /// Gets the next state of this body.
      BodyState& getNextState() { return mNextState; }
      const BodyState& getNextState() const { return mNextState; }
      
      bool isCollidable() const { return mIsCollidable; }
      void setCollidable(bool c) { mIsCollidable = c; }

      /// Makes the next state the current state.
      void moveToNextState();
   
   private:
      gmtl::Vec3f mForce;	
      gmtl::Vec3f mTorque;

      float mMass;

      /**
       * The current state of this rigid body. All calculations for the current
       * frame should be done relative to this state.
       */
      BodyState mCurrentState;

      /// The next state of this rigid body.
      BodyState mNextState;

      /// The bounding volume for this body
      gmtl::AABoxf mBounds;
      
      bool mIsCollidable;
   };
}

#endif
