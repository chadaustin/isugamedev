#ifndef MW_SHOTGUN_H
#define MW_SHOTGUN_H

#include <gmtl/Math.h>
#include <stdlib.h>
#include <vector.h>
#include "BaseProjectileWeapon.h"
#include "RigidBody.h"

const unsigned int NUM_PELLETS = 10;

namespace mw
{
   /*SHOTGUN,a basic weapon*/
   class  Shotgun: public BaseProjectileWeapon
   {
   private:
	       float mSpreadAngle;
   public:

      Shotgun() : BaseProjectileWeapon()
      {
	 mSpreadAngle=10.f;
	 srand(SDL_GetTicks());
         mMaxAmmoInBag = 1200;
         mClipSize = 6;
         mFiring = false;
         mReloading = false;
         mBusyCounter = 0;

         mReloadRate = 2.0f;
         mFireRate = 0.7f;

         mAmmoInClip = mClipSize;
         mAmmoInBag = 100;

         // init to no waiting time
         mBusyCounter = 0.0f;
         mReloadCounter = 0.0f;
      }
      
      /** return the Player slot number that the weapon goes in. */
      virtual int getType() { return 3; }
      
      /** render the weapon using opengl calls. */
      virtual void draw() const 
      {
         glPushMatrix();
            glMultMatrixf( this->matrix().getData() );
            glScalef( 0.15f, 0.15f, 0.8f );
            cubeGeometry().render();
         glPopMatrix();
      }

      // some of these will change to public...
   protected:
      RigidBody* Shotgun::createBullet()
      {
	 
         RigidBody* bullet = new RigidBody();
         bullet->setVel(gmtl::Vec3f(0,0,-30));


	 
         return bullet;
      }
	 
      virtual void emitBullet( GameState& g )
      {
	 
                     
         // add the bullet to the gamestate...
         
	 RigidBody** bullet;
	 bullet=new RigidBody *[NUM_PELLETS];
	 
	
	 
	 
	 for(unsigned int i=0;i<NUM_PELLETS;i++)
	 {
	     //TODO:  seed this according to world time?
	    

            //generate random bullet directions with the sweep of mSpreadAngle
	    //degrees	    
	    
      	    float angle = gmtl::Math::deg2Rad((mSpreadAngle* float(rand())/RAND_MAX) - (mSpreadAngle/2));
	    
            gmtl::Quatf r( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( angle, 0.0f, 1.0f, 0.0f ) ) );

	    bullet[i] = this->createBullet();
	         
	    bullet[i]->setRot( this->getRot() * r ); //shoot off at a limited random angle
            bullet[i]->setPos( this->getPos() );
            bullet[i]->setVel( this->getRot() * r * bullet[i]->getVel() );
	    
            g.add( bullet[i] ); // bullet is not mine anymore, belongs to GameState
	    
	 }
	 
	 // Remove the spent ammo from the clip
         --mAmmoInClip;

         // Start the reload process automagically if necessary
         if (mAmmoInClip == 0)
         {
            reload();
         }
         // Pause to put a new bullet in the chamber
         else
         {
            mBusyCounter = mFireRate;
         }


      }
   };
}

#endif
