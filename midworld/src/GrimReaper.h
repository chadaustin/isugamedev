/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_GRIMREAPER_H
#define MW_GRIMREAPER_H

#include "RigidBody.h"
#include "BaseBullet.h"
#include "Enemy.h"
#include <vector>

namespace mw
{
   /**
    * This class will clean up the expired bullets in the GameState.
    * @TODO: Eventually it should clean up all expired objects in the world.
    */
   class GrimReaper
   {
   public:
      /**
       * Constructor
       */
      GrimReaper()
      {
      }
      /**
       * Destructor
       */
      ~GrimReaper()
      {
      }
      /**
       * Cleans up all the expired objects in the list.
       * @param list the list of objects to reap
       */
      void reap(std::vector<RigidBody*> &list);
      /**
       * Cleans up all the expired objects in the list.
       * @param list the list of enemies to reap
       */
      void reap(std::vector<Enemy*> &list);
      /**
       * Cleans up all the expired objects in the list.
       * @param list the list of bullets to reap
       */
      void reap(std::vector<BaseBullet*> &list);
   };

   
}//end of namespace mw

#endif
