#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Matrix4f.h"
#include "Quat.h"
#include "convert.h"
#include "glRenderLight.h"


#include "glRenderTexture.h"
#include "ImageManager.h"
#include "GeodeCache.h"
#include "Geode.h"
#include "glRenderGeode.h"


extern int GetNextLightNum();

class Bullet
{
public:
   Bullet()
      : mRot(), mRotVel()
   {
      mGeometry.reset( new Geode );
      mXForm.makeIdent();

      mLight.setNumber(GetNextLightNum());
      mLight.setPos( 0.0f, 0.0f, 0.0f, 1.0f );
      mLight.setColor( Light::diffuse, 1.0f, 0.8f, 0.8f );
      mLight.setColor( Light::ambient, 0.3f, 0.3f, 0.3f );
      mLight.setColor( Light::specular, 1.0f, 1.0f, 1.0f );
      mLight.setAtten( 1.0f, 0.001f );
      mLight.on();

      GeodeCache::instance().load( mGeometry, "models/bullet.obj" );
   }

   ~Bullet()
   {
      glDisable( GL_LIGHT0 + mLight.number() );
   }

   /**
    * Draws this bullet.
    */
   void draw() const
   {
      kev::glRender(mLight);
      
      glPushMatrix();
         glMultMatrixf( mXForm.data() );
         kev::glRenderGeode( mGeometry );
      glPopMatrix();
   }

   /**
    * Updates the state and position of this bullet.
    */
   void update( float timeDelta = 1.0f )
   {
      Vec3<float> forward = getForward();
      
      //Update the position of the bullet
      translate( mVel * timeDelta );

      Quat<float> rotVel;
      rotVel.makeIdent();
      rotVel.makePure( forward * mRotVel );
      
      //Update the angular velocity and orientation
      Quat<float> delta;
      delta.mult( rotVel * 0.5f, mRot );
      delta.mult( delta, timeDelta );
      mRot.add( mRot, delta );
      mRot.normalize();

      //store the matrix for drawing
      kev::quat2mat( mPos, mRot, mXForm );

      //Update the light position
      Vec3<float> lightPos = mPos + forward * 5.0f;
      mLight.setPos( lightPos[0], lightPos[1], lightPos[2], 1.0f );
   }

   /**
    * Gets the vector pointing in the direction the bullet is facing.
    */
   Vec3<float> getForward() const
   {
      Vec3<float> forward( 0, 0, -1 );
      return mRot * forward;
   }

   /**
    * Sets the position of this bullet.
    */
   void setPos( const Vec3<float>& pos )
   {
      mPos = pos;
   }

   /**
    * Sets the velocity of this bullet.
    */
   void setVel( const Vec3<float>& vel )
   {
      mVel = vel;
   }

   /**
    * Sets the rotation of this bullet.
    */
   void setRot( const Quat<float> rot )
   {
      mRot = rot;
   }

   /**
    * Sets the angular velocity of the bullet around the z axis.
    */
   void setRotVel( float magnitude )
   {
      mRotVel = magnitude;
   }

   /**
    * Moves this bullet by the given translation.
    */
   void translate( const Vec3<float>& offset )
   {
      mPos += offset;
   }

   /**
    * Gets the position of this bullet.
    */
   const Vec3<float>& position() const
   {
      return mPos;
   }

private:
   Matrix4f mXForm;
   Vec3<float> mPos, mVel;
   Quat<float> mRot;
   float mRotVel;
   Light mLight;
   GeodePtr mGeometry;
};

#endif // ! BULLET_H_INCLUDED
