#ifndef MW_PARTICLE_ENGINE_H
#define MW_PARTICLE_ENGINE_H

#include <list>
#include <gmtl/Vec.h>
#include <gmtl/Point.h>
#include "PhysicsEngine.h"
#include "Particle.h"
#include "Texture.h"
#include "Camera.h"

namespace mw
{
   class ParticleEngine
   {
   public:
      ParticleEngine(const std::string& filename, const int numParticles, 
						const gmtl::Point3f pos,const Camera& gameCamera);
      ~ParticleEngine();
      void update(float dt);
      void draw();
      bool isExpired();
      void setPos(const gmtl::Point3f& pos);
      const gmtl::Point3f& getPos() const;

   private:
      void billboardBegin(const gmtl::Vec3f& cam, const gmtl::Vec3f& objPos);
      void billboardEnd();

   private:
      gmtl::Point3f mPos;
      Texture* mParticleTexture;

      typedef std::list<Particle*> ParticleList;
      ParticleList mParticleGroup;
      PhysicsEngine* mParticlePhysics;
      const Camera& mParticleCamera;
   };
}

#endif
