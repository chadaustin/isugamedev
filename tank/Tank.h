#ifndef TANK_DEFINED
#define TANK_DEFINED

#include "Matrix4f.h"
#include "Quat.h"
#include "glRenderTexture.h"
#include "glRenderMaterial.h"
#include "ImageManager.h"

#include "ObjImporter.h"
#include "GeoSet.h"
#include "glRenderGeoSet.h"
#include "convert.h"

#include "iniFile.h"

class Tank
{
public:
   Tank() : mRot(), mRotVel(), mSpeed( 0.0f ), mMaterial()
   {
      mXForm.makeIdent();
      this->init();
   }

   void init()
   {
      std::string filename, weapon0;
      bool result;
      iniFile ini;
      ini.load( "tank.ini" );
      ini.getKey( "tank", "model", filename, result );
      assert( result );
      ini.getKey( "tank", "weapon0", weapon0, result );
      assert( result );

      kev::ObjImporter obj;
      obj.load( geosets, filename );
      assert( geosets.size() > 0 && "load failed" );
      obj.load( mWeapon0GeoSets, weapon0 );
      assert( mWeapon0GeoSets.size() > 0 && "load failed" );
   }
   
   void drawShip() const
   {
      glEnable( GL_TEXTURE_2D );
   
      // compensate for the 3DS scale and rotation...
      glPushMatrix();
      glTranslatef( 0, 2, 0 );
      kev::glRenderGeoSets( mWeapon0GeoSets );
      glPopMatrix();

      kev::glRenderGeoSets( geosets );
   }

   void draw() const
   {
      kev::glRender( mMaterial );
      glPushMatrix();
         glMultMatrixf( mXForm.data() );

         // vehicle (tank)
         glPushMatrix();
            drawShip();
         glPopMatrix();
         
      glPopMatrix();
   }
  
   /**
    * Gets the position at the end of the barrel.
    */
   Vec3<float> getBarrelEndPos() const
   {
      Vec3<float> barrelEndPos = Vec3<float>( 0, 2, -3 );
      return (mRot * barrelEndPos) + mPos;
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
      
   void update( float timeDelta )
   {
      // POS
      // x' = v = vel in tank local coord system
      Vec3<float> pos_delta = mRot * mVel;
      pos_delta *= timeDelta; // scale by time...
      
      // add the derivative onto the tank's position
      mPos += pos_delta;
      
      // ROT
      // update ang velocity.
      // change in rotation is 1/2 angvel times current rotation or...
      // q' = 1/2 w * q, where w is a Vec3 who's magnitude is amount of angvel
      // and who's axis defines the axis of rotation.
      Quat<float> rot_delta, temp;
      temp.mult( mRotVel * 0.5f, mRot );
      rot_delta.mult( temp, timeDelta );  // scale by time...
      
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

   const Quat<float>& rotation() const
   {
      return mRot;
   }

private:
   Matrix4f mXForm;
   Vec3<float> mPos, mVel;
   Quat<float> mRot, mRotVel;
   Material mMaterial;
   float mSpeed;
   
   std::vector< safe_ptr<GeoSet> > geosets;
   std::vector< safe_ptr<GeoSet> > mWeapon0GeoSets;
};

#endif
