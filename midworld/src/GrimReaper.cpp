/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "GrimReaper.h"

namespace mw
{
   void GrimReaper::reap(std::vector<RigidBody*> &list)
   {
      ///@TODO:  Figure out how to reap the rigid bodies.
   }

   void GrimReaper::reap(std::vector<Enemy*> &list)
   {
      ///@TODO:  FIgure out how to reap the enemies.
   }

   void GrimReaper::reap(std::vector<BaseBullet*> &list)
   {
      vector<BaseBullet*>::iterator i = list.begin();
      for ( ; i != list.end(); )
      {
         if ((*i)->isExpired())
         {
            delete *i;
            list.erase(i);
         }
         else
         {
            ++i;
         }
      }
   }

}//end of namespace mw
