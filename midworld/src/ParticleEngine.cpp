#include "ParticleEngine.h"
#include "Utility.h"
#include <gmtl/VecOps.h>
#include <gmtl/Math.h>

namespace mw
{
   ParticleEngine::ParticleEngine(const std::string& filename,
                                  const int numParticles,
								  const gmtl::Point3f pos,
                                  const Camera& gameCamera)
      : mParticleCamera(gameCamera)
   {
      mParticleTexture = new Texture(filename);

      for(int i = 0; i < numParticles; i++)
      {
         gmtl::Vec3f velocity = randomUnitVector();
         velocity *= gmtl::Math::rangeRandom(5.0, 15.0);

         Particle* temp = new Particle(gmtl::Math::rangeRandom(1.0, 2.0));
         temp->size(0.2);
         temp->setMass(0.10);
         temp->setVel(velocity);
		 temp->setPos(pos);
         mParticleGroup.push_back(temp);
      }
   }

   ParticleEngine::~ParticleEngine()
   {
      delete mParticleTexture;
   }

   void ParticleEngine::setPos(const gmtl::Point3f& pos)
   {
      mPos = pos;
   }

   const gmtl::Point3f& ParticleEngine::getPos() const
   {
      return mPos;
   }

   bool ParticleEngine::isExpired()
   {
      if(mParticleGroup.size() == 0)
         return true;
      else
         return false;
   }

   void ParticleEngine::draw()
   {
      const gmtl::Vec3f& camera_pos = mParticleCamera.getPos();
      mParticleTexture->bind();

      glPushAttrib(GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      {
         glDisable(GL_DEPTH_TEST);
         glDisable(GL_LIGHTING);
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE);

         glColor4f(1,0,0,0.5f);

         for(ParticleList::iterator i=mParticleGroup.begin(); i != mParticleGroup.end(); ++i)
         {
            const gmtl::Point3f& part_pos = (*i)->getPos();
            billboardBegin(camera_pos, part_pos);
            (*i)->draw();
            billboardEnd();
         }
      }
      glPopAttrib();

      mParticleTexture->unbind();
   }

   void ParticleEngine::update(float dt)
   {
      for(ParticleList::iterator i=mParticleGroup.begin(); i != mParticleGroup.end();)
      {
         Particle* particle = *i;

         particle->addForce(PhysicsEngine::GRAVITY * particle->getMass());
         particle->update(dt);
         mParticlePhysics->update(particle, dt, false);
         particle->moveToNextState();
         if (particle->isExpired())
         {
            delete particle;
            i = mParticleGroup.erase(i);
         }
         else if (particle->getPos()[1] <= 0)
         {
            delete particle;
            i = mParticleGroup.erase(i);
         }
         else
         {
            i++;
         }
      }
   }

   void ParticleEngine::billboardBegin(const gmtl::Vec3f& cam, const gmtl::Vec3f& objPos)
   {
      gmtl::Vec3f lookAt,objToCamProj,upAux, objToCam;
      float angleCosine;

      glPushMatrix();

      // objToCamProj is the vector in world coordinates from the
      // local origin to the camera projected in the XZ plane
      objToCamProj[0] = cam[0] - objPos[0];
      objToCamProj[1] = 0;
      objToCamProj[2] = cam[2] - objPos[2] ;

      // This is the original lookAt vector for the object
      // in world coordinates
      lookAt[0] = 0;
      lookAt[1] = 0;
      lookAt[2] = 1;


      // normalize both vectors to get the cosine directly afterwards
      gmtl::normalize(objToCamProj);

      // easy fix to determine wether the angle is negative or positive
      // for positive angles upAux will be a vector pointing in the
      // positive y direction, otherwise upAux will point downwards
      // effectively reversing the rotation.

      upAux = gmtl::cross(lookAt, objToCamProj);

      // compute the angle
      angleCosine = gmtl::dot(lookAt, objToCamProj);

      // perform the rotation. The if statement is used for stability reasons
      // if the lookAt and objToCamProj vectors are too close together then
      // |angleCosine| could be bigger than 1 due to lack of precision
      if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
         glRotatef(acos(angleCosine)*180/3.14,upAux[0], upAux[1], upAux[2]);

      // so far it is just like the cylindrical billboard. The code for the
      // second rotation comes now
      // The second part tilts the object so that it faces the camera

      // objToCam is the vector in world coordinates from
      // the local origin to the camera
      objToCam[0] = cam[0] - objPos[0];
      objToCam[1] = cam[1] - objPos[1];
      objToCam[2] = cam[2] - objPos[2];

      // Normalize to get the cosine afterwards
      gmtl::normalize(objToCam);

      // Compute the angle between objToCamProj and objToCam,
      //i.e. compute the required angle for the lookup vector
      angleCosine = gmtl::dot(objToCamProj,objToCam);

      // Tilt the object. The test is done to prevent instability
      // when objToCam and objToCamProj have a very small
      // angle between them

      if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
      {
         if (objToCam[1] < 0)
         {
            glRotatef(acos(angleCosine)*180/3.14,1,0,0);
         }
         else
         {
            glRotatef(acos(angleCosine)*180/3.14,-1,0,0);
         }
      }
   }

   void ParticleEngine::billboardEnd()
   {
      // restore the previously
      // stored modelview matrix
      glPopMatrix();
   }
}
