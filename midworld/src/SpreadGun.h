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
      SpreadGun() : BaseProjectileWeapon(), mSpinning( 0.0f )
      {
      }

      /** return the Player slot number that the weapon goes in. */
      virtual int getType() { return 2; }
      
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
            mSpinning += 360.0f * dt; // 90 deg per sec
         }
      }
      
   protected:
      virtual void emitBullet( GameState& g )
      {
         // define the spread
         float angle = gmtl::Math::deg2Rad( 15.0f );
         gmtl::Quatf r0( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( angle, 0.0f, 1.0f, 0.0f ) ) ),
                     r1, 
                     r2( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( -angle, 0.0f, 1.0f, 0.0f ) ) );
         
         // define the 3 bullets in the spread weapon.
         RigidBody* bullet0 = this->createBullet();
         bullet0->setRot( this->rotation() * r0 );
         bullet0->setPos( this->position() );
         bullet0->setVel( this->rotation() * r0 * bullet0->getVel() );
         
         RigidBody* bullet1 = this->createBullet();
         bullet1->setRot( this->rotation() * r1 );
         bullet1->setPos( this->position() );
         bullet1->setVel( this->rotation() * r1 * bullet1->getVel() );
         
         RigidBody* bullet2 = this->createBullet();
         bullet2->setRot( this->rotation() * r2 );
         bullet2->setPos( this->position() );
         bullet2->setVel( this->rotation() * r2 * bullet2->getVel() );
         
         // add the three bullets to the game
         // bullet is not mine anymore, belongs to GameState
         g.add( bullet0 ); 
         g.add( bullet1 ); 
         g.add( bullet2 ); 
      }
      
      float mSpinning;
   };
}

#endif
