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
 * File:          $RCSfile: RigidBody.cpp,v $
 * Date modified: $Date: 2002-07-29 06:10:29 $
 * Version:       $Revision: 1.15 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/VecOps.h>
#include <gmtl/Generate.h>
#include "RigidBody.h"
#include "cubeGeometry.h"

namespace mw
{
   void RigidBody::update(float dt)
   {
      // zero mass not supported :(
      if (mMass < 0.0001f) mMass = 1.0f;
      
      // change in position over time (first order)
      // x' = v = P(t)/M
      gmtl::Vec3f pos_delta = mVel * dt;
      
      // change in lin momentum over time (second order)
      // P'(t) = F(t)
      gmtl::Vec3f linear_momentum_delta = mForce * dt;
      
      // change in rotation over time (first order)
      // R'(t) = w(t)*' R(t)   (matrix version)
      // q'(t) = 1/2 w(t) q(t) (quaternion version)
      gmtl::Quatf rot_delta, temp;
      gmtl::Quatf one_half_wt = gmtl::makePure( gmtl::Vec3f( mRotVel * 0.5f ) );
      gmtl::mult( temp, one_half_wt, mRot );
      gmtl::mult( rot_delta, temp, dt );  // scale by time...
      
      // change in ang momentum over time (second order)
      // L'(t) = T(t)
      gmtl::Vec3f ang_momentum_delta = mTorque;

      // add the derivitives to the current rigidbody state
      mPos += pos_delta;
      mVel += (linear_momentum_delta / mMass);
      mRot += rot_delta;
      gmtl::normalize( mRot ); // rot quats always normalized
      mRotVel += ang_momentum_delta; // @todo this is wrong (needs inertia tensor)
      
      // zero out the force, and torque accumulators.
      mForce.set( 0.0f, 0.0f, 0.0f );
      mTorque.set( 0.0f, 0.0f, 0.0f );

      // Move the bounds along with the body
      gmtl::Vec3f extents = (mBounds.getMax() - mBounds.getMin()) * 0.5f;
      mBounds.setMin(mPos - extents);
      mBounds.setMax(mPos + extents);
   }

   void RigidBody::addForce(const gmtl::Vec3f& force)
   {
      mForce += force;
   }

   void RigidBody::addForce( const gmtl::Vec3f& force, const gmtl::Vec3f& pos )
   {
      mForce += force; // yes we need both... :)
      mTorque += gmtl::cross( pos, force );
   }

   void RigidBody::draw() const
   {
      glPushMatrix();
         glTranslatef(mPos[0], mPos[1], mPos[2]);
         glMultMatrixf( gmtl::make<gmtl::Matrix44f>( mRot ).getData() );
         glScalef(0.5f, 0.5f, 0.5f);
         cubeGeometry().render();
      glPopMatrix();
   }

   gmtl::Vec3f RigidBody::getForward() const
   {
      return getRot() * gmtl::Vec3f(0,0,-1);
   }

   const gmtl::AABoxf& RigidBody::getBounds() const
   {
      return mBounds;
   }
   
   gmtl::Matrix44f RigidBody::matrix() const 
   {
      // store the matrix from the pos/rot data...
      gmtl::Matrix44f xform;
      gmtl::set( xform, this->getRot() );
      gmtl::setTrans( xform, gmtl::Vec3f( this->getPos() ) );
      return xform;
   }
}
