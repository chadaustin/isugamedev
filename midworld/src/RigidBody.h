/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
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
