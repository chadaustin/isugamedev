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
 * File:          $RCSfile: BodyState.h,v $
 * Date modified: $Date: 2002-10-01 07:54:16 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_BODY_STATE_H
#define MW_BODY_STATE_H

#include <gmtl/Point.h>
#include <gmtl/Vec.h>
#include <gmtl/Quat.h>

namespace mw
{
   /**
    * @ingroup Physics
    *
    * Represents the state a rigid body is in. The state consists of its
    * position, velocity, rotation, and rotational velocity. It is assumed that
    * all other attributes of a RigidBody remain constant for any given instant
    * in time.
    *
    * @see RigidBody
    */
   class BodyState
   {
   public:
      /**
       * Creates a body state position at the origin with no velocity, rotation,
       * or rotational velocity.
       */
      BodyState()
      {}

      /// Creates an exact duplicate of the given state.
      BodyState(const BodyState& state)
      {
         copy(state);
      }

      ///@{
      /// Gets the position for this state.
      gmtl::Point3f&       getPos()       { return mPos; }
      const gmtl::Point3f& getPos() const { return mPos; }
      ///@}

      /// Sets the position of this state to the given point.
      void setPos(const gmtl::Point3f& pos) { mPos = pos; }

      ///@{
      /// Gets the rotation for this state.
      gmtl::Vec3f&         getVel()       { return mVel; }
      const gmtl::Vec3f&   getVel() const { return mVel; }
      ///@}

      /// Sets the velocity of this state to the given vector.
      void setVel(const gmtl::Vec3f& vel) { mVel = vel; }

      ///@{
      /// Gets the rotation for this state.
      gmtl::Quatf&         getRot()       { return mRot; }
      const gmtl::Quatf&   getRot() const { return mRot; }
      ///@}

      /// Sets the rotation for this state.
      void setRot(const gmtl::Quatf& rot) { mRot = rot; }

      ///@{
      /// Gets the rotation velocity for this state in radians/second.
      gmtl::Vec3f&         getRotVel()       { return mRotVel; }
      const gmtl::Vec3f&   getRotVel() const { return mRotVel; }
      ///@}

      /// Sets the rotational velocity for this state in radians/second.
      void setRotVel(const gmtl::Vec3f& rotVel) { mRotVel = rotVel; }

      /// Makes this state a copy of the given state.
      BodyState& operator=(const BodyState& state)
      {
         copy(state);
         return *this;
      }

   private:
      /// Makes this state a copy of the given state.
      void copy(const BodyState& state)
      {
         mPos = state.mPos;
         mVel = state.mVel;
         mRot = state.mRot;
         mRotVel = state.mRotVel;
      }

   private:
      /// The body's position.
      gmtl::Point3f mPos;

      /// The body's velocity.
      gmtl::Vec3f mVel;

      /// The body's rotation.
      gmtl::Quatf mRot;

      /// The body's rotational velocity.
      gmtl::Vec3f mRotVel;
   };
}

#endif
