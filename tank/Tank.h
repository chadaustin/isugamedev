#ifndef TANK_DEFINED
#define TANK_DEFINED

#include "Matrix4f.h"
class Tank
{
public:
   Tank() : mRot(), mRotVel(), mSpeed(0.0f)
   {
      mXForm.makeIdentity();
   }
   
   void drawPyramidThing()
   {
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
   }   
   
   void draw()
   {
      glPushMatrix();
         glMultMatrixf( mXForm.data() );

         // vehicle (tank)
         glPushMatrix();
            glColor3f( 1,0,1 );
            glScalef( 10,10,25 );
            drawPyramidThing();
         glPopMatrix();
         
         // gun
         glPushMatrix();
            glScalef( 1,1,17 );
            glTranslatef( 0,8,0 );
            glColor3f( 0,0,1 );
            drawPyramidThing();
         glPopMatrix();
         
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
      //Calculate the new forward velocity of this tank based on its speed
      mVel = getForward() * mSpeed;
      this->translate( mVel );
      
      // update ang velocity.
      // change in rotation is 1/2 angvel times current rotation or...
      // q' = 1/2 w * q, where w is a Vec3 who's magnitude is amount of angvel
      // and who's axis defines the axis of rotation.
      Quat<float> delta;
      delta.mult( mRotVel * 0.5f, mRot );
      //delta.mult( delta, time_delta );  // do this if we're considering time...
      
      mRot.add( mRot, delta );
      mRot.normalize();
      
      // store the matrix from the pos/rot data...
      kev::quat2mat( mPos, mRot, mXForm );
   }

   /**
    * Sets the speed at which this tank moves. Negative speed implies that the
    * tank is running in reverse.
    */
   void setSpeed( float speed )
   {
      mSpeed = speed;
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
   float mSpeed;
};

#endif
