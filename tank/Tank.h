#ifndef TANK_DEFINED
#define TANK_DEFINED

#include "Matrix4f.h"
class Tank
{
public:
   Tank()
   {
      mPos.makeIdentity();
   }
   
   void draw()
   {
      glPushMatrix();

         glMultMatrixf( mPos.data() );
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
  
   void translate( const Vec3<float>& offset )
   {
      Vec3<float> temp;
      mPos.getTranslation( temp );
      mPos.setTranslation( temp + offset );
   }   
   
   Vec3<float> getForward() const
   {
      Vec3<float> forward;
      forward[0] = mPos( 2, 0 );
      forward[1] = mPos( 2, 1 );
      forward[2] = mPos( 2, 2 );
      forward = -forward;
      forward.normalize();
      
      return forward;
   }
   
   const Matrix4f& matrix() const 
   {
      return mPos;
   }
      
   void setPos( const Matrix4f& pos )
   {
      mPos = pos;
   }   
   
   void update()
   {
      this->translate( mVel );
   }   
   
   void setVelocity( const Vec3<float>& velocity )
   {
      mVel = velocity;
   }   
   
   const Vec3<float>& velocity() const
   {
      return mVel;
   }   
   
   Vec3<float> position() const
   {
      Vec3<float> trans;
      mPos.getTranslation( trans );
      return trans;
   }  
private:
   Matrix4f mPos;
   Vec3<float> mVel;
};

#endif
