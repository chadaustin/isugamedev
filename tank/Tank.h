#ifndef TANK_DEFINED
#define TANK_DEFINED

#include "Matrix4f.h"
class Tank
{
public:
   Tank() : mRot(), mRotVel(), mSpeed( 0.0f )
   {
      mXForm.makeIdentity();
   }
   
   void drawPyramidThing()
   {
      glPushMatrix();
         glTranslatef( 0.0f, 0.0f, 0.25f );
         glBegin( GL_TRIANGLES );
            // left face
            glNormal3f( -1.0f, 1.0f, -1.0f );
            glVertex3f( -1.0f, 0.0f, 0.0f );
            glVertex3f(  0.0f, 1.0f, 0.1f );
            glVertex3f(  0.0f, 0.0f, -1.0f );

            // right face
            glNormal3f( 1.0f, 1.0f, -1.0f );
            glVertex3f( 0.0f, 1.0f, 0.1f );
            glVertex3f( 1.0f, 0.0f, 0.0f );
            glVertex3f( 0.0f, 0.0f, -1.0f );

            // back face
            glNormal3f(  0.0f, 0.0f, 1.0f );
            glVertex3f(  0.0f, 1.0f, 0.1f );
            glVertex3f( -1.0f, 0.0f, 0.0f );
            glVertex3f(  1.0f, 0.0f, 0.0f );
         glEnd();
      glPopMatrix();
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
   
   void travel( float speed )
   {
      mSpeed = speed;
   }
   
   const Matrix4f& matrix() const 
   {
      return mXForm;
   }
      
   void setPos( const Vec3<float>& pos )
   {
      mPos = pos;
   }
      
   void update( float timeDelta = 1.0f )
   {
      // POS
      // x' = v = vel in tank local coord system
      Vec3<float> pos_delta = mRot * mVel;
      
      // add the derivative onto the tank's position
      mPos += pos_delta * timeDelta;
      
      // ROT
      // update ang velocity.
      // change in rotation is 1/2 angvel times current rotation or...
      // q' = 1/2 w * q, where w is a Vec3 who's magnitude is amount of angvel
      // and who's axis defines the axis of rotation.
      Quat<float> rot_delta;
      rot_delta.mult( mRotVel * 0.5f, mRot );
      rot_delta.mult( rot_delta, timeDelta );  // scale by time...
      
      // add the derivative onto the tank's rotation
      mRot.add( mRot, rot_delta );
      mRot.normalize();
      
      // XFORM
      // store the matrix from the pos/rot data...
      kev::quat2mat( mPos, mRot, mXForm );
   }

   const Vec3<float>& velocity() const
   {
      return mVel;
   }
   
   // with repect to tank local coordinate system.
   // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
   void setVelocity( const Vec3<float>&  vel )
   {
      mVel = vel;
   }
   
   // with repect to tank local coordinate system.
   // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
   void setVelocity( float x, float y, float z )
   {
      mVel.set( x, y, z );
   }
   
   void translate( const Vec3<float>& offset )
   {
      mPos += offset;
   }
     
   void setRot( float deg )
   {
      mRot.makeRot( kev::deg2rad( deg ), 0,1,0 );
   }
   
   // true ang velocity vector 
   // w = [0, mag, 0]
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
