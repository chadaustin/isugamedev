#ifndef TANK_DEFINED
#define TANK_DEFINED

#include "Matrix4f.h"
#include "Quat.h"
#include "glRenderTexture.h"
#include "glRenderMaterial.h"
#include "ImageManager.h"

#include "GeodeCache.h"
#include "glRenderGeode.h"
#include "convert.h"

#include "iniFile.h"

// particle system
#include "Fizix/Body.h"
#include "Fizix/Operator.h"
#include "Fizix/EulerODEsolver.h"
#include "Fizix/RungeKuttaODEsolver.h"
#include "Fizix/DynamicSystem.h"
#include "Fizix/systems/Torch.h"

#include "RenderDynamicSystem.h"
#include "glRenderEntity.h"
#include "TankGame.h"

class Tank
{
public:
   Tank() : mPos(), mVel(), mRot(), mRotVel(), mMaterial(), mSpeed( 0.0f ),
            mBodyGeometry( NULL ), mWeapon0Geometry( NULL ), mUseSprite( false ),
            mHitPoints( 20 ), mArmor( 0.2 )
   {
      mXForm.makeIdent();
      this->init();
   }

   void init()
   {
      std::string filename, weapon0, particle, usesprite;
      bool result;
      iniFile ini;
      ini.load( "tank.ini" );
      ini.getKey( "tank", "model", filename, result );
      assert( result );
      ini.getKey( "tank", "weapon0", weapon0, result );
      assert( result );
      ini.getKey( "tank", "particle", particle, result );
      assert( result );
      ini.getKey( "tank", "particlesprite", usesprite, result );
      assert( result );
      kev::string2bool( usesprite, mUseSprite );

      GeodeCache::instance().load( mBodyGeometry, filename );
      assert( mBodyGeometry->getNumGeoSets() > 0 && "load failed" );
      
      GeodeCache::instance().load( mWeapon0Geometry, weapon0 );
      assert( mWeapon0Geometry->getNumGeoSets() > 0 && "load failed" );
      
      glRenderEntityAsGeom<ani::FireParticle>* fire_particle_render = new glRenderEntityAsGeom<ani::FireParticle>;
      fire_particle_render->setGeom( particle );
      torchRender.setRender( fire_particle_render );
   }
   
   void drawShip() const
   {
      glEnable( GL_TEXTURE_2D );
   
      glPushMatrix();
      glTranslatef( 0, 2, 0 );
      kev::glRenderGeode( mWeapon0Geometry );
      glPopMatrix();

      kev::glRenderGeode( mBodyGeometry );
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

      // draw smoke if dead.
      if (mHitPoints == 0.0f)
      {
         const Matrix4f& cameraMat = TankGame::instance().getPlayer(0)->getCamera().matrix();
         this->torchRender.render( torch, cameraMat, true, mUseSprite );
      }
   }
  
   // armor is 0 to 1
   // hitpoints is 0 to n (we could change this.)
   void applyDamage( float hitpoints )
   {
      mHitPoints -= hitpoints * (1.0f - mArmor);
      if (mHitPoints < 0.0f) mHitPoints = 0;
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
      torch.setPos( pos );
   }
      
   void update( float timeDelta )
   {
      // POS
      // x' = v = vel in tank local coord system
      Vec3<float> pos_delta = mRot * mVel;
      pos_delta *= timeDelta; // scale by time...
      
      // add the derivative onto the tank's position
      this->setPos( this->position() + pos_delta );
      
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
      
      torch.step( timeDelta );
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
   void drawsmoke() const
   {
      for (int x = 0; x < torch.entities().size(); ++x)
      {
         const boost::shared_ptr<ani::FireParticle> ent = torch.entities()[x];
         const Vec3<float>& pos = ent->position();
         const ColorRGBA& col = ent->color(); 
         glColor4f( col[0], col[1], col[2], col[3] );
         //glPushMatrix();
         //glTranslatef( pos[0], pos[1], pos[2] );

         glBegin( GL_TRIANGLES );
         glNormal3f( 0,0,1 );
         glVertex3f( pos[0], pos[1], pos[2] );
         glVertex3f( pos[0]+1, pos[1], pos[2] );
         glVertex3f( pos[0]+1, pos[1]+1, pos[2] );
         glEnd();

         //glPopMatrix();
         //glVertex3f( pos[0], pos[1], pos[2] );
         //std::cout<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<"\n"<<std::flush;
      }
   }

   RenderDynamicSystem<ani::FireParticle> torchRender;
   ani::Torch<ani::FireParticle> torch;
   bool mUseSprite;

   float mHitPoints, mArmor;
   
   Matrix4f mXForm;
   Vec3<float> mPos, mVel;
   Quat<float> mRot, mRotVel;
   Material mMaterial;
   float mSpeed;

   GeodePtr mBodyGeometry, mWeapon0Geometry;
};

#endif
