#ifndef MW_PARTICLE_ENGINE_H
#define MW_PARTICLE_ENGINE_H

#include <list>
#include <gmtl/Vec.h>
#include <gmtl/Point.h>
#include "AbstractEntity.h"
#include "Camera.h"
#include "Particle.h"
#include "PhysicsEngine.h"
#include "Texture.h"

namespace mw
{
   class ParticleEngine : public AbstractEntity
   {
   public:
      ParticleEngine(GameState* gameState,
                     const std::string& filename,
                     const int numParticles);
      ~ParticleEngine();
      void update(float dt);
      void draw() const;
      bool isExpired() const;
      
   private:
      void billboardBegin(
         const gmtl::Vec3f& cam,
         const gmtl::Vec3f& objPos) const;
      void billboardEnd() const;

   private:
      Texture* mParticleTexture;

      typedef std::list<Particle*> ParticleList;
      ParticleList mParticleGroup;
      PhysicsEngine* mParticlePhysics;
      const Camera& mParticleCamera;
   };
}

#endif
