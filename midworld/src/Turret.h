#ifndef MW_TURRET_H
#define MW_TURRET_H

#include "Enemy.h"

namespace mw
{
/** 
 * class for a turret 
 * inherits from enemy
 */
class Turret : public Enemy
{
public:
   /**
    *  Empty constructor
    */
   Turret() 
   {
   }

   /**
    * destructor
    */
   ~Turret()
   {
   }

   /**
    * This is the aim function so we will track the player 
    */
   void aim();

   /**
    * this is the shoot method so we will fire a bullet when this is 
    * called
    */
   void shoot();

};

}

#endif
