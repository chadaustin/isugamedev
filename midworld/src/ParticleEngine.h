#ifndef MW_PARTICLE_ENGINE_H
#define MW_PARTICLE_ENGINE_H

#include "PhysicsEngine.h"
#include "Particle.h"
#include "Texture.h"
#include "Camera.h"
#include <gmtl/Vec.h>
#include <gmtl/Point.h>
#include <list>

namespace mw
{
   class ParticleEngine
   {
   public:

	    ParticleEngine(const std::string& filename, const int numParticles, const Camera& gameCamera);
		~ParticleEngine();
		void update(float dt);
		void draw();
		bool isExpired();
		void setPos(const gmtl::Point3f& thePoint);
		const gmtl::Point3f& getPos() const;

   private:
		void billboardBegin(gmtl::Vec3f cam,gmtl::Vec3f objPos);
		void billboardEnd();

		gmtl::Point3f point;
		Texture* ParticleTexture;

		typedef std::list<Particle*> ParticleList;
		ParticleList ParticleGroup;
		PhysicsEngine* ParticlePhysics;
		Camera ParticleCamera;
   };
}

#endif
