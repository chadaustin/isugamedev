#ifndef MW_PARTICLE_H
#define MW_PARTICLE_H

#include "RigidBody.h"

namespace mw
{
   class Particle: public RigidBody
   {
   public:
	   Particle(float particleLife);

	   ~Particle();

      bool isExpired() const;

	  void update(float dt);

	  void size(float particleSize);

	  void draw();

   private:
	   float life;
	   bool dead;
	   float theSize;
	   float elapsedTime;
   };
}

#endif
