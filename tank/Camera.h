#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include "Matrix4f.h"

class Camera
{
public:
   Camera() : mShouldFollow( false ), mPitch( 45.0f )
   {
      mXform.makeIdentity();
      mTargetPos.makeIdentity();
      
   }

   void setTargetPos( const Matrix4f& pos )
   {
      mTargetPos = pos;
   }

   void follow( bool shouldFollow )
   {
      mShouldFollow = shouldFollow;
   }   
   
   void update()
   {
      mXform = mTargetPos;
      
      if (mShouldFollow)
      {
         float angle = 70.0f;
         //float angle = -15;
         Matrix4f rot_mat, trans, temp;
         trans.makeTranslation( Vec3<float>( 0,0,30 ) );
         rot_mat.makeRotation( -angle * TO_RAD_F, 1,0,0 );
         Matrix4f::multiply( temp, rot_mat, trans );
         Matrix4f::multiply( mXform, mTargetPos, temp );
      }
   }

   const Matrix4f& matrix() const
   {
      return mXform;
   }
   
   void draw()
   {
      Matrix4f mat = mXform;
      mat.invert();
      
      glMultMatrixf( mat.data() );  
   }
   
   Vec3<float> position() const
   {
      Vec3<float> trans;
      mXform.getTranslation( trans );
      return trans;
   }  
   
   
   
private:
   Matrix4f mXform;
   Matrix4f mTargetPos;
   bool mShouldFollow;
   float mPitch;
};


#endif

