/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_BASEBULLET_H
#define MW_BASEBULLET_H

#include "RigidBody.h"

namespace mw
{
   /**
    * This class represents the base bullet from which all guns derive
    * their bullet types.
    */
   class BaseBullet: public RigidBody
   {
   public:
      /**
       * Constructor
       */
      BaseBullet() :  mExistCount(0), mTimeOut(5), mExpired(false)
      {
      }
      /**
       * Destructor
       */
      ~BaseBullet()
      {
      }
      /**
       * Update this bullet based on the time that has passed.
       * @param dt the amount of time in seconds that has passed
       */
      virtual void update(float dt)
      {
         if (mExistCount >= mTimeOut)
         {
            mExpired = true;
         }
         mExistCount += dt;
         RigidBody::update(dt);
      }
      /**
       * Draw this bullet.
       * @TODO: Do something?
       */
      virtual void draw() const
      {
         RigidBody::draw();
      }

      bool isExpired() const
      {
         return mExpired;
      }
   protected:
      //The amount of time that this bullet has existed in the GameState
      float mExistCount;
      //The amount of time this bullet is allowed to stay in the GameState 
      float mTimeOut;
      //Am I expired yet?
      bool mExpired;
   private:
   };   

}//end of namespace mw
#endif
