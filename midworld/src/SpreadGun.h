#ifndef MW_SPREADGUN_H
#define MW_SPREADGUN_H

#include <gmtl/Math.h>
#include <gmtl/AxisAngle.h>
#include "BaseProjectileWeapon.h"

namespace mw
{
   /*PISTOL,a basic weapon*/
   class SpreadGun : public BaseProjectileWeapon
   {
   public:
      SpreadGun()
         : BaseProjectileWeapon(Weapon::AUTOMATIC, "SpreadGun")
         , mSpinning( 0.0f )
      {
         mCockRate = 0.1f;
         mReloadRate = 0.5f;
      }

      /** render the weapon using opengl calls. */
      virtual void draw() const 
      {
         glPushMatrix();
            glMultMatrixf( this->matrix().getData() );
            glScalef( 0.3f, 0.3f, 0.4f );
            glRotatef( mSpinning, 0, 0, 1 );
            cubeGeometry().render();
         glPopMatrix();
      }
      
      virtual void update( GameState& g, float dt )
      {
         BaseProjectileWeapon::update( g, dt );
         if (mFiring)
         {
            mSpinning += 5.0f * 360.0f * dt; // 5 Revs per sec
         }
      }
      
   protected:
      void discharge(GameState& g)
      {
         // define the spread
         float angle = gmtl::Math::deg2Rad( 15.0f );
         gmtl::Quatf r0( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( angle, 0.0f, 1.0f, 0.0f ) ) ),
                     r1, 
                     r2( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( -angle, 0.0f, 1.0f, 0.0f ) ) );
         
         // define the 3 bullets in the spread weapon.
         RigidBody* bullet0 = this->createBullet();
         bullet0->setRot( this->getRot() * r0 );
         bullet0->setPos( this->getPos() );
         bullet0->setVel( this->getRot() * r0 * bullet0->getVel() );
         
         RigidBody* bullet1 = this->createBullet();
         bullet1->setRot( this->getRot() * r1 );
         bullet1->setPos( this->getPos() );
         bullet1->setVel( this->getRot() * r1 * bullet1->getVel() );
         
         RigidBody* bullet2 = this->createBullet();
         bullet2->setRot( this->getRot() * r2 );
         bullet2->setPos( this->getPos() );
         bullet2->setVel( this->getRot() * r2 * bullet2->getVel() );
         
         // add the three bullets to the game
         // bullet is not mine anymore, belongs to GameState
         g.add( bullet0 ); 
         g.add( bullet1 ); 
         g.add( bullet2 ); 
      }

      void ejectCasing(GameState& g)
      {
         /// @todo eject a casing into the game
      }
      
      float mSpinning;
   };
}

#endif
