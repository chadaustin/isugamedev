#ifndef MW_BULLET_CASING_H
#define MW_BULLET_CASING_H


#include "AbstractEntity.h"


namespace mw
{
   class BulletCasing : public AbstractEntity
   {
   public:
      typedef AbstractEntity Base;
   
      BulletCasing(GameState* gameState)
         : Base(gameState)
      {
         mExistCount = 0;
         mTimeOut = 5;
      }
      
      void update(float dt)
      {
         mExistCount += dt;
         return AbstractEntity::update(dt);
      }
      
      bool isExpired() const
      {
         return mExistCount >= mTimeOut;
      }
      
   private:
      float mExistCount;
      float mTimeOut;
   };
}


#endif
