#ifndef MW_PISTOL_H
#define MW_PISTOL_H

#include <gmtl/Math.h>
#include "BaseProjectileWeapon.h"

namespace mw
{
   /*PISTOL,a basic weapon*/
   class Pistol : public BaseProjectileWeapon
   {
   public:
      Pistol()
         : BaseProjectileWeapon( Weapon::HANDGUN, "Pistol", 1 )
      {}

      /** render the weapon using opengl calls. */
      void draw() const 
      {
         glPushMatrix();
            glMultMatrixf( this->matrix().getData() );
            glScalef( 0.15f, 0.15f, 0.3f );
            cubeGeometry().render();
         glPopMatrix();
      }

      // some of these will change to public...
   protected:
      void discharge(GameState& g)
      {
         // add the bulllet to the gamestate...
         RigidBody* bullet = this->createBullet();
         bullet->setRot( this->getRot() );
         bullet->setPos( this->getPos() );
         bullet->setVel( this->getRot() * bullet->getVel() );
         g.add( bullet ); // bullet is not mine anymore, belongs to GameState
      }

      void ejectCasing(GameState& g)
      {
         /// @todo eject a casing
      }
   };
}

#endif
