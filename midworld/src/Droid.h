#ifndef MW_DROID_H
#define MW_DROID_H

#include "Enemy.h"


namespace mw
{
   class Droid: public Enemy
   {
   public:
      Droid(GameState* gameState);
      ~Droid();

      void update(float dt);

      void shoot();

      float getTimeDelta();
      
      Weapon* getGun();
      
      void walkRandom();
      void rotate();

   private:
      float timeDelta;
      Weapon* gun;
   };
}

#endif
