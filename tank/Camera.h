#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include "Matrix4f.h"
#include "Quat.h"
#include "convert.h"

class Camera
{
public:
   Camera() : mTargetPos(0,0,0), mTargetPosOld( 0,0,-30 ), mShouldFollow( false ), 
              mYaw(0.0f),
              mYawVel(0.0f), 
              mPitch( 30.8f ), 
              mPitchVel( 0.0f ),
              mFollowDist( 5.6f ), 
              mFollowDistVel( 0.0f )
   {
      mXform.makeIdent();
      mTargetRot.makeIdent();
      mTargetRotOld.makeIdent();
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
   
   void update( float timeDelta )
   {
      if (mShouldFollow)
      {
         // instead of instantly setting the camera rotation 
         // equal to the target angle, apply some dampening so 
         // that the camera takes longer to catch up.
         float dampening_factor = 2.0f * timeDelta;
         Quat<float> dampened_rot;
         dampened_rot.slerp( dampening_factor, mTargetRotOld, mTargetRot );
         mTargetRotOld = dampened_rot;
         
         // dampen the camera position...
         Vec3<float> dampened_pos;
         dampened_pos.lerp( dampening_factor, mTargetPosOld, mTargetPos );
         mTargetPosOld = dampened_pos;
         
         // set the target matrix that the camera would match if mounted to 
         // the vehicle on a springy dampened platform.  this will be 
         // used to determine the camera local coordinate system
         // used then as a basis for pitching and yawing the camera.
         Matrix4f target_mat;
         kev::quat2mat( dampened_pos, dampened_rot, target_mat );
         //mXform = target_mat;

         Matrix4f pitch_mat, yaw_mat, trans, temp;
         trans.makeTrans( Vec3<float>( 0,0, mFollowDist ) );
         pitch_mat.makeRot( -mPitch * TO_RAD_F, 1,0,0 );
         yaw_mat.makeRot( -mYaw * TO_RAD_F, 0,1,0 );
         Matrix4f::multiply( temp, yaw_mat * pitch_mat, trans );
         Matrix4f::multiply( mXform, target_mat, temp );
      }
      else
      {
         // set the camera's xform to match as if mounted to 
         // the target object
         kev::quat2mat( mTargetPos, mTargetRot, mXform );
      }

      
      mPitch += mPitchVel * timeDelta;
      mYaw += mYawVel * timeDelta;
      mFollowDist += mFollowDistVel * timeDelta;

	  //std::cout<<mFollowDist<<" "<<mPitch<<" "<<mYaw<<"\n"<<std::flush;
   }

   void setPitch( float deg )
   {
      mPitch = deg;
   }   
   
   // deg/sec
   void setPitchVel( float deg )
   {
      mPitchVel = deg;
   }   
   
   void setYaw( float deg )
   {
      mYaw = deg;
   }   
   
   // deg/sec
   void setYawVel( float deg )
   {
      mYawVel = deg;
   }

   void setFollowDist( float offset )
   {
      mFollowDist = offset;
   }

   void setFollowDistVel( float offsetVel )
   {
      mFollowDistVel = offsetVel;
   }
   
   const Matrix4f& matrix() const
   {
      return mXform;
   }
   
   void draw() const
   {
      Matrix4f mat = mXform;
      mat.invert();
      
      glMultMatrixf( mat.data() );  
   }
   
   Vec3<float> position() const
   {
      Vec3<float> trans;
      mXform.getTrans( trans );
      return trans;
   }

   float followDist() const
   {
       return mFollowDist;
   }
   
private:
   Matrix4f mXform;
   Vec3<float> mTargetPos, mTargetPosOld;
   Quat<float> mTargetRot, mTargetRotOld;
   bool mShouldFollow;
   float mPitch, mPitchVel;
   float mYaw, mYawVel;
   float mFollowDist, mFollowDistVel;
};


#endif

