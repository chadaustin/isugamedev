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
 * Date modified: $Date: 2002-06-06 04:53:59 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_RIGID_BODY_H
#define MW_RIGID_BODY_H

#include <gmtl/AABox.h>
#include <gmtl/Point.h>

namespace mw
{
   /**
    * Interface for a physical body that cannot be deformed.
    */
   class RigidBody
   {
   
      gmtl::Point3f mPos;  //position
      gmtl::Vec3f mVel;
      gmtl::Vec3f mAccel;
      gmtl::Vec3f mForce;	
      
   //rotation vars

      gmtl::Vec3f mRot;
      gmtl::Vec3f mRotVel;
      gmtl::Vec3f mRotAccel;
      gmtl::Vec3f mRotForce;


   public:

      float mMass;
      //private access//

      void setPos(gmtl::Point3f pos){ mPos=pos;}
      void setVel(gmtl::Vec3f vel){ mVel=vel;}
      void addForce(gmtl::Vec3f force);

      void setRot     (gmtl::Vec3f rotAngle ){ mRot=rotAngle;}
      void setRotVel  (gmtl::Vec3f rotVel)   { mRotVel=rotVel;}
      void addRotForce(gmtl::Vec3f rotForce);



      void move(float dt);	// update pos,vel,accel, and force
      void draw();	// display

      virtual ~RigidBody() {}

      /**
       * Gets the axis-aligned bounding box that tightly contains this body.
       *
       * @return  the bounding volume for this body
       */
      virtual const gmtl::AABoxf& getBounds() const;

      /**
       * Gets the position of this rigid body relative to the world's origin.
       *
       * @return  this body's position.
       */
      virtual const gmtl::Point3f& getPosition() const;
   };
}

#endif
