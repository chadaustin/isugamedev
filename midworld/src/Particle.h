#ifndef MW_PARTICLE_H
#define MW_PARTICLE_H

#include "RigidBody.h"

namespace mw
{
   class Particle: public RigidBody
   {
   public:
      Particle(float life);
      ~Particle();

      bool isExpired() const;
      void update(float dt);
      void size(float size);
      void draw();

   private:
      float mLife;
      bool mDead;
      float mSize;
      float mElapsedTime;
   };
}

#endif
