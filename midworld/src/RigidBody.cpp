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
 * Date modified: $Date: 2003-06-19 03:19:17 $
 * Version:       $Revision: 1.24 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/VecOps.h>
#include <gmtl/Generate.h>
#include "RigidBody.h"

namespace mw
{
   void RigidBody::addForce(const gmtl::Vec3f& force)
   {
      mForce += force;
   }

   void RigidBody::addForce( const gmtl::Vec3f& force, const gmtl::Vec3f& pos )
   {
      mForce += force; // yes we need both... :)
      mTorque += gmtl::makeCross( pos, force );
   }

   gmtl::Vec3f RigidBody::getForward() const
   {
      return getCurrentState().getRot() * gmtl::Vec3f(0,0,-1);
   }

   const gmtl::AABoxf& RigidBody::getBounds() const
   {
      return mBounds;
   }

   void RigidBody::setBounds(const gmtl::AABoxf& box)
   {
      mBounds = box;
   }
   
   gmtl::Matrix44f RigidBody::matrix() const 
   {
      // store the matrix from the pos/rot data...
      gmtl::Matrix44f xform;
      gmtl::set(xform, getCurrentState().getRot());
      gmtl::setTrans(xform, gmtl::Vec3f(getCurrentState().getPos()));
      return xform;
   }

   void RigidBody::moveToNextState()
   {
      mCurrentState = mNextState;
      mForce.set(0,0,0);
      mTorque.set(0,0,0);
      fireBodyChange();
   }

   void RigidBody::addBodyChangeListener(BodyChangeListener* listener)
   {
      mListeners.push_back(listener);
   }

   void RigidBody::removeBodyChangeListener(BodyChangeListener* listener)
   {
      std::list<BodyChangeListener*>::iterator itr =
                  std::find(mListeners.begin(), mListeners.end(), listener);
      if (itr != mListeners.end())
      {
         mListeners.erase(itr);
      }
   }

   void RigidBody::fireBodyChange()
   {
      BodyChangeEvent evt(this);
      for (std::list<BodyChangeListener*>::iterator itr = mListeners.begin();
           itr != mListeners.end(); ++itr)
      {
         (*itr)->bodyChanged(evt);
      }
   }
}
