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
 * File:          $RCSfile: RigidBody.h,v $
 * Date modified: $Date: 2002-07-06 05:11:01 $
 * Version:       $Revision: 1.13 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_RIGID_BODY_H
#define MW_RIGID_BODY_H

#include <gmtl/AABox.h>
#include <gmtl/Point.h>
#include <gmtl/Quat.h>
#include <gmtl/Matrix.h>

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

      RigidBody() : mMass( 1.0f )
      {
      }
      
      virtual ~RigidBody() {}

      /**
       * Sets the position of this rigid body relative to the world's origin.
       */
      void setPos(const gmtl::Point3f& pos) { mPos = pos; }

      /**
       * Gets the position of this rigid body relative to the world's origin.
       */
      const gmtl::Point3f& getPos() const { return mPos; }

      /**
       * Sets the velocity of this rigid body.
       */
      void setVel(const gmtl::Vec3f& vel) { mVel = vel; }

      /**
       * Gets the velocity of this rigid body.
       */
      const gmtl::Vec3f& getVel() const { return mVel; }

      /**
       * Applies a force on this body at its center of mass. This will not add
       * any torque on the body.
       *
       * @param force      the force to apply
       */
      void addForce(const gmtl::Vec3f& force);

      /**
       * Sets the rotation of this rigid body.
       */
      void setRot(const gmtl::Quatf& rot) { mRot = rot; }

      /**
       * Gets the rotation of this rigid body.
       */
      const gmtl::Quatf& getRot() const { return mRot; }

      /**
       * Sets the angular velocity of this rigid body.
       */
      void setRotVel(const gmtl::Vec3f& rotVel) { mRotVel = rotVel; }

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
       * Updates the internal state of this body given the amount of time that
       * has passed.
       *
       * @param dt      the differtial of time in seconds
       */
      virtual void update(float dt);
      virtual void draw() const;	// display

      /**
       * Gets the axis-aligned bounding box that tightly contains this body.
       *
       * @return  the bounding volume for this body
       */
      const gmtl::AABoxf& getBounds() const;

      /** convert the pos/rot to a matrix. */
      gmtl::Matrix44f matrix() const;
   
   private:
      gmtl::Point3f mPos;  //position
      gmtl::Vec3f mVel;
      gmtl::Vec3f mForce;	

   //rotation vars
      gmtl::Quatf mRot;
      gmtl::Vec3f mRotVel;
      gmtl::Vec3f mTorque;

      float mMass;

      /// The bounding volume for this body
      gmtl::AABoxf mBounds;
   };
}

#endif
