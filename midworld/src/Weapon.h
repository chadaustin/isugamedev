/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#ifndef MW_WEAPON_H
#define MW_WEAPON_H

#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>
#include <gmtl/Quat.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>

#include "RigidBody.h"

namespace mw
{
   class GameState;
   
   /**
    * Interface for all weapons that the player or enemies may use. A weapon
    * object functions a description of the weapon and is a projectile factory.
    */
   class Weapon
   {
   public:
      virtual ~Weapon() {}

      /** return the Player slot number that the weapon goes in. */
      virtual int getType() = 0;

      /**
       * Sets whether this weapon is currently firing. Think of it as though
       * we're setting whether or not the trigger is being held down.
       */
      virtual void trigger( bool firing ) = 0;

      /** render the weapon using opengl calls. */
      virtual void draw() const = 0;
        
      /**
       * Updates the state of this bullet based on the amount of time that has
       * passed.
       *
       * @param dt   the change in time in seconds
       */
      virtual void update( GameState& g, float timeDelta )
      {
         // POS
         // x' = v = vel in tank local coord system
         gmtl::Vec3f pos_delta = mRot * mVel;
         pos_delta *= timeDelta; // scale by time...

         // add the derivative onto the tank's position
         this->setPos( this->position() + pos_delta );

         /*
         // ROT
         // update ang velocity.
         // change in rotation is 1/2 angvel times current rotation or...
         // q' = 1/2 w * q, where w is a Vec3 who's magnitude is amount of angvel
         // and who's axis defines the axis of rotation.
         gmtl::Quatf rot_delta, temp;
         temp.mult( mRotVel * 0.5f, mRot );
         rot_delta.mult( temp, timeDelta );  // scale by time...

         // add the derivative onto the tank's rotation
         mRot.add( mRot, rot_delta );
         mRot.normalize();
         */

         // XFORM
         // store the matrix from the pos/rot data...
         gmtl::set( mXForm, mRot );
         gmtl::setTrans( mXForm, mPos );
      }

      /// for ammo pickup
      virtual void addAmmo( int ammount ) = 0;
      
      
      const gmtl::Vec3f& velocity() const
      {
         return mVel;
      }

      // with repect to tank local coordinate system.
      // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
      void setVelocity( const gmtl::Vec3f& vel )
      {
         mVel = vel;
      }

      // with repect to tank local coordinate system.
      // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
      void setVelocity( float x, float y, float z )
      {
         mVel.set( x, y, z );
      }

      void translate( const gmtl::Vec3f& offset )
      {
         mPos += offset;
      }

      void setPos( const gmtl::Vec3f& pos )
      {
         mPos = pos;
      }
            
      void setRot( gmtl::Quatf r )
      {
         mRot = r;
      }

      // true ang velocity vector
      // w = [0, mag, 0]
      void setAngVel( float magnitude )
      {
         //mRotVel = gmtl::makePure<gmtl::Quatf>( gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) * magnitude );
      }

      const gmtl::Vec3f& position() const
      {
         return mPos;
      }

      const gmtl::Quatf& rotation() const
      {
         return mRot;
      }
   
      const gmtl::Matrix44f& matrix() const
      {
         return mXForm;
      }
      
   private:
      gmtl::Matrix44f mXForm;
      gmtl::Vec3f mPos, mVel;
      gmtl::Quatf mRot;
   };
}

#endif
