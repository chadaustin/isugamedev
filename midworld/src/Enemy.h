/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_ENEMY_H
#define MW_ENEMY_H

#include <cstdlib>
#include "RigidBody.h"

namespace mw
{
   /**
    * Base class for all enemy types.
    */
   class Enemy: public RigidBody
   {
   public:

      /**
       * Constructor
       */
      Enemy()
      {
         srand(5);
      }
      /**
       * Destructor
       */
      ~Enemy()
      {
      }
      
      /**
       * Gets the current health value of this enemy.
       * @return the amount of health this enemy has left.
       */
      long int getHealth() {return mHealth;}
      /**
       * Sets the current health value of this enemy.
       * @param health the amount of health to set this enemy at.
       */
      void setHealth(long int health)  {mHealth = health;}
      
      /**
       * Updates the internal state of this enemy taking into account
       * the amount of time that has passed.
       * @param timeDelta the change in time that has occurred since the last
       * update
       */
      virtual void update(float timeDelta);
      /**
       * Draws this enemy onto the screen.
       */
      virtual void draw() const;
      
   private:
      long int mHealth;   
   };

}//end of namespace mw
#endif
