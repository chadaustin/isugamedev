#ifndef MW_STATIC_ENTITY_H
#define MW_STATIC_ENTITY_H


#include "AbstractEntity.h"


namespace mw
{

   class StaticEntity : public AbstractEntity
   {
   public:
      StaticEntity(GameState* gameState)
         : AbstractEntity(gameState)
      {
      }

      void onCollisionEntry(const CollisionEvent&)
      {
      }

      void onCollisionMovement(const CollisionEvent&)
      {
      }

      void onCollisionExit(const CollisionEvent&)
      {
      }

      bool isExpired() const
      {
         return false;
      }
   };

}


#endif
