#include <map>
#include <gmtl/Matrix.h>
#include <gmtl/Quat.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>

#include "Weapon.h"
#include "Player.h"
#include "GameState.h"
#include "cubeGeometry.h"
#include "NullWeapon.h"

namespace mw
{

   Player::Player() : mPos(), mVel(), mRot(), mCurrentWeapon( mWeapons.end() )
   {
      // add default weapon...
      this->addWeapon( new NullWeapon );
      assert( !this->isWeaponSlotEmpty( NullWeapon().getType() ) && "NullWeapon not registered, no default weapon!");
      
      this->init();
   }

   void Player::init()
   {
   }

   void Player::draw() const
   {
      //glEnable( GL_TEXTURE_2D );
      glPushMatrix();
         glMultMatrixf( mXForm.getData() );
         glTranslatef( 0, 1, 0 );
         glPushMatrix();
            glScalef( 0.5f, 0.3f, 0.4f );
            cubeGeometry().render();
         glPopMatrix();
      glPopMatrix();
      
      this->weapon().draw();
   }

   bool Player::isWeaponSlotEmpty( int slot )
   {
      return mWeapons.count( slot ) == 0;
   }
   
   /**
    * Gets this player's current weapon.
    */
   Weapon& Player::weapon()
   {
      if (mCurrentWeapon != mWeapons.end())
      {
         return *(*mCurrentWeapon).second;
      }

      // return something safe :)
      assert( mWeapons.count( NullWeapon().getType() ) > 0 && "huh?" );
      return *(*mWeapons.find( NullWeapon().getType() )).second;
   }
   
   /**
    * Gets this player's current weapon.
    */
   const Weapon& Player::weapon() const
   {
      if (mCurrentWeapon != mWeapons.end())
      {
         return *(*mCurrentWeapon).second;
      }

      // return something safe :)
      assert( mWeapons.count( NullWeapon().getType() ) > 0 && "huh?" );
      return *(*mWeapons.find( NullWeapon().getType() )).second;
   }
   
   /**
    * Sets the player's current in-use weapon.
    */
   void Player::setWeapon( int slot )
   {
      if (!this->isWeaponSlotEmpty( slot ))
      {
         // set current weapon to this one...
         mCurrentWeapon = mWeapons.find( slot );
      }
   }
   
   /** adds weapon to player's inventory.
    *  each added weapon may cause that weapon to immediately become active
    *  depending on the player's game preferences.
    */
   void Player::addWeapon( Weapon* w )
   {
      assert( NULL != w && "bad weapon ptr" );
      
      // if slot already had a weapon, remove it
      if (mWeapons.count( w->getType() ) > 0)
      {
         delete mWeapons[w->getType()];
         mWeapons.erase( w->getType() );
      }
      
      // add the weapon to the slot
      mWeapons[w->getType()] = w;
      
      // set current weapon to the newly added one.
      mCurrentWeapon = mWeapons.find( w->getType() );
   }
   
   /** make the next weapon active.
    *  this will either iterate round-robin through the list
    *  of weapons that the player has, or it may iterate in an 
    *  alternate order specified by player's game preferences.
    */
   void Player::nextWeapon()
   {
      if (!mWeapons.empty())
      {
         ++mCurrentWeapon;
         if (mCurrentWeapon == mWeapons.end())
         {
            mCurrentWeapon = mWeapons.begin();
         }
         
         // call setWeapon for any extra behaviour needed.
         this->setWeapon( (*mCurrentWeapon).second->getType() );
      }
   }

   /**
    * Gets the position at the end of the barrel.
    */
   gmtl::Vec3f Player::getBarrelEndPos() const
   {
      gmtl::Vec3f barrelEndPos = gmtl::Vec3f( 0, 2, -3 );
      return (mRot * barrelEndPos) + mPos;
   }
   
   gmtl::Vec3f Player::getForward() const
   {
      gmtl::Vec3f forward( 0,0,-1 );
      return mRot * forward;
   }
   
   const gmtl::Matrix44f& Player::matrix() const 
   {
      return mXForm;
   }
      
   void Player::setPos( const gmtl::Vec3f& pos )
   {
      mPos = pos;
   }
      
   void Player::update( GameState& gs, float timeDelta )
   {
      // POS
      // x' = v = vel in tank local coord system
      gmtl::Vec3f pos_delta = mRot * mVel;
      pos_delta *= timeDelta; // scale by time...
      
      // add the derivative onto the tank's position
      this->setPos( this->position() + pos_delta );
      
      /*
      // ROT
      // update ang velocity.
      // change in rotation is 1/2 angvel times current rotation or...
      // q' = 1/2 w * q, where w is a Vec3 who's magnitude is amount of angvel
      // and who's axis defines the axis of rotation.
      gmtl::Quatf rot_delta, temp;
      temp.mult( mRotVel * 0.5f, mRot );
      rot_delta.mult( temp, timeDelta );  // scale by time...
      
      // add the derivative onto the tank's rotation
      mRot.add( mRot, rot_delta );
      mRot.normalize();
      */
            
      // XFORM
      // store the matrix from the pos/rot data...
      gmtl::set( mXForm, mRot );
      gmtl::setTrans( mXForm, mPos );

      // update the current weapon
      this->weapon().setPos( this->position() + this->rotation() * gmtl::Vec3f( 0, 0, -0.5f ) );
      this->weapon().setRot( this->rotation() );
      this->weapon().update( gs, timeDelta );
   }

   const gmtl::Vec3f& Player::velocity() const
   {
      return mVel;
   }
   
   // with repect to tank local coordinate system.
   // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
   void Player::setVelocity( const gmtl::Vec3f& vel )
   {
      mVel = vel;
   }
   
   // with repect to tank local coordinate system.
   // i.e. if tank is rotated, then 0,0,-1 is always "forward" for the tank.
   void Player::setVelocity( float x, float y, float z )
   {
      mVel.set( x, y, z );
   }
   
   void Player::translate( const gmtl::Vec3f& offset )
   {
      mPos += offset;
   }
     
   void Player::setRot( gmtl::Quatf r )
   {
      mRot = r;
   }

   // true ang velocity vector
   // w = [0, mag, 0]
   void Player::setAngVel( float magnitude )
   {
      //mRotVel = gmtl::makePure<gmtl::Quatf>( gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) * magnitude );
   }

   const gmtl::Vec3f& Player::position() const
   {
      return mPos;
   }

   const gmtl::Quatf& Player::rotation() const
   {
      return mRot;
   }
}// namespace.
