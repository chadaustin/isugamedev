#ifndef TANK_DEFINED
#define TANK_DEFINED

#include "Matrix4f.h"
class Tank
{
public:
   Tank() : mRot(), mRotVel()
   {
      mXForm.makeIdentity();
   }
   
   void draw()
   {
      glPushMatrix();

         glMultMatrixf( mXForm.data() );
         glColor3f( 1,0,1 );
         glScalef( 10,10,10 );
         glBegin( GL_TRIANGLES );
         
              glNormal3f( -1.0f, 1.0f, -1.0f );
              glVertex3f( -1.0f, 0.0f, 0.0f );
              glVertex3f(  0.0f, 1.0f, 0.0f );
              glVertex3f(  0.0f, 0.0f, -1.0f );

              glNormal3f( 1.0f, 1.0f, -1.0f );
              glVertex3f( 0.0f, 1.0f, 0.0f );
              glVertex3f( 1.0f, 0.0f, 0.0f );
              glVertex3f( 0.0f, 0.0f, -1.0f );

              glNormal3f(  0.0f, 0.0f, 1.0f );
              glVertex3f(  0.0f, 1.0f, 0.0f );
              glVertex3f( -1.0f, 0.0f, 0.0f );
              glVertex3f(  1.0f, 0.0f, 0.0f );
         glEnd();

      glPopMatrix();
   }
  
   
   
   Vec3<float> getForward() const
   {
      Vec3<float> forward( 0,0,-1 );
      return mRot * forward;
   }
   
   const Matrix4f& matrix() const 
   {
      return mXForm;
   }
      
   void setPos( const Vec3<float>& pos )
   {
      mPos = pos;
   }
      
   void update()
   {
      this->translate( mVel );
      
      // update ang velocity.
      // q' = 1/2 w * q
      Quat<float> delta;
      delta.mult( mRotVel * 0.5f, mRot );
      //delta.mult( delta, time_delta ); 
      
      mRot.add( mRot, delta );
      mRot.normalize();
      
      // store the matrix from the pos/rot data...
      kev::quat2mat( mPos, mRot, mXForm );
   }   
   
   void setVelocity( const Vec3<float>& velocity )
   {
      mVel = velocity;
   }   
   
   const Vec3<float>& velocity() const
   {
      return mVel;
   }   
   
   void translate( const Vec3<float>& offset )
   {
      mPos += offset;
   }   
   
   void setRot( float deg )
   {
      mRot.makeRot( kev::deg2rad( deg ), 0,1,0 );
   }   
   void setAngVel( float magnitude )
   {
      mRotVel.makePure( Vec3<float>( 0,1,0 ) * magnitude );
   }  
   
   const Vec3<float>& position() const
   {
      return mPos;
   }  
private:
   Matrix4f mXForm;
   Vec3<float> mPos, mVel;
   Quat<float> mRot, mRotVel;
};

#endif
