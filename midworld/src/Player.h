#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

#include "gmtl/Matrix.h"
#include "gmtl/Quat.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/QuatOps.h"
#include "gmtl/Generate.h"

#include "cubeGeometry.h"

namespace mw
{

class Player
{
public:
   Player() : mPos(), mVel(), mRot()
   {
      this->init();
   }

   void init()
   {
   }

   void draw() const
   {
      //glEnable( GL_TEXTURE_2D );
   
      glPushMatrix();
         glTranslatef( 0, 1, 0 );
         cubeGeometry().render();
         glTranslatef( 0, 0, -2 );
         glScalef( 0.3, 0.3, 2 );
         cubeGeometry().render();
      glPopMatrix();
   }

   /**
    * Gets the position at the end of the barrel.
    */
   gmtl::Vec3f getBarrelEndPos() const
   {
      gmtl::Vec3f barrelEndPos = gmtl::Vec3f( 0, 2, -3 );
      return (mRot * barrelEndPos) + mPos;
   }
   
   gmtl::Vec3f getForward() const
   {
      gmtl::Vec3f forward( 0,0,-1 );
      return mRot * forward;
   }
   
   const gmtl::Matrix44f& matrix() const 
   {
      return mXForm;
   }
      
   void setPos( const gmtl::Vec3f& pos )
   {
      mPos = pos;
   }
      
   void update( float timeDelta )
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
     
   void setRot( float deg )
   {
      mRot = gmtl::makeRot<gmtl::Quatf>( gmtl::Math::deg2Rad( deg ), 0.0f, 1.0f, 0.0f );
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

private:
   gmtl::Matrix44f mXForm;
   gmtl::Vec3f mPos, mVel;
   gmtl::Quatf mRot;
};
}

#endif
