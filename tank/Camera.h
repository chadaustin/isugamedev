#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include "Matrix4f.h"
#include "Quat.h"
#include "convert.h"

class Camera
{
public:
   Camera() : mTargetPos(0,0,0), mShouldFollow( false ), mYaw(0.0f), mYawVel(0.0f), mPitch( 70.0f ), mPitchVel( 0.0f )
   {
      mXform.makeIdentity();
      mTargetRot.makeIdent();
   }

   void setTargetPos( const Matrix4f& mat )
   {
      kev::mat2quat( mat, mTargetPos, mTargetRot );
   }
   
   void setTargetPos( const Vec3<float>& pos, const Quat<float>& rot )
   {
      mTargetPos = pos;
      mTargetRot = rot;
   }

   void follow( bool shouldFollow )
   {
      mShouldFollow = shouldFollow;
   }   
   
   void update( float timeDelta = 1.0f )
   {
      if (mShouldFollow)
      {
         // instead of instantly setting the camera rotation 
         // equal to the target angle, apply some dampening so 
         // that the camera takes longer to catch up.
         float dampening_factor = 0.01f;
         Quat<float> dampened_rot;
         dampened_rot.slerp( dampening_factor, mTargetRotOld, mTargetRot );
         mTargetRotOld = dampened_rot;

         // set the target matrix that the camera would match if mounted to 
         // the vehicle on a springy dampened platform.  this will be 
         // used to determine the camera local coordinate system
         // used then as a basis for pitching and yawing the camera.
         Matrix4f target_mat;
         kev::quat2mat( mTargetPos, dampened_rot, target_mat );
         mXform = target_mat;

         Matrix4f pitch_mat, yaw_mat, trans, temp;
         trans.makeTranslation( Vec3<float>( 0,0,30 ) );
         pitch_mat.makeRotation( -mPitch * TO_RAD_F, 1,0,0 );
         yaw_mat.makeRotation( -mYaw * TO_RAD_F, 0,1,0 );
         Matrix4f::multiply( temp, yaw_mat * pitch_mat, trans );
         Matrix4f::multiply( mXform, target_mat, temp );
      }
      else
      {
         // set the camera's xform to match as if mounted to 
         // the target object
         kev::quat2mat( mTargetPos, mTargetRot, mXform );
      }

      
      mPitch += mPitchVel;
      mYaw += mYawVel;
   }

   void setPitch( float deg )
   {
      mPitch = deg;
   }   
   
   void setPitchVel( float deg )
   {
      mPitchVel = deg;
   }   
   
   void setYaw( float deg )
   {
      mYaw = deg;
   }   
   
   void setYawVel( float deg )
   {
      mYawVel = deg;
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
   Vec3<float> mTargetPos;
   Quat<float> mTargetRot, mTargetRotOld;
   bool mShouldFollow;
   float mPitch, mPitchVel;
   float mYaw, mYawVel;
   
};


#endif

