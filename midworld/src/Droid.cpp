#include <iostream>

#include <gmtl/Math.h>

#include "EntityFactory.h"
#include "Pistol.h"
#include "Droid.h"
//#include "ParticleEngine.h"
#include "NavNodeTree.h"

namespace mw
{
   Droid::Droid(GameState* gameState)
      : Enemy(gameState)
   {
      gun = new Pistol();
      gun->setSource("Droid");
      fuckedFlag = true;
      mTree = new NavNodeTree();     

      goalNode = new Node();
      fakeNode = new Node();
      currentNode = new Node();
      
      
   }

   Droid::~Droid()
   {
 /*     EntityFactory& factory = EntityFactory::instance();
      ParticleEngine* engine = new ParticleEngine(
            factory.getGameState(),
            "explosive_particle",
            100);
      factory.add(engine);

      engine->setPos(getPos());
*/   }

   float Droid::getTimeDelta()
   {
      return timeDelta;
   }

   void Droid::update(float dt)
   {
      timeDelta = dt;
      Enemy::update(dt);
      gun->update(*getGameState(), dt);
      gun->trigger(false);
   }

   void Droid::shoot()
   {
      gun->trigger(true);
   }

   Weapon* Droid::getGun()
   {
      return gun;
   }

   void Droid::walkRandom()
   {
      if (rand() % 100 < 5)
      {
         gmtl::Vec3f force = randomUnitVector() * 5;
         force[1] = 0;  // no vertical forces
         addForce(force);
      }
      if ((rand() % 100) == 0)
      {

         gmtl::Quatf nRot = gmtl::makeRot<gmtl::Quatf>(
            gmtl::AxisAnglef(3.141/2.0, 0, 1, 0));
         setRot(nRot);
      }
   }

}



