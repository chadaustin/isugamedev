#include "Particle.h"
#include <SDL_opengl.h>
#include <gmtl/Math.h>

namespace mw
{
   Particle::Particle(float life)
      : mLife(life)
      , mDead(false)
      , mElapsedTime(0.0f)
   {
       red = gmtl::Math::rangeRandom(0.5,1.0);
       green = gmtl::Math::rangeRandom(0.0, 0.5);
       blue = 0.0;
   }

   Particle::~Particle()
   {}

   bool Particle::isExpired() const
   {
      return mDead;
   }

   void Particle::size(float size)
   {
      mSize = size;
   }

   void Particle::draw()
   {
      glColor4f(red,green,blue,0.7);
      glBegin(GL_QUADS);
         glTexCoord2d(1,1); glVertex3f(mSize, mSize, 0); // Top right
         glTexCoord2d(0,1); glVertex3f(-mSize, mSize, 0); // Top left
         glTexCoord2d(0,0); glVertex3f(-mSize, -mSize, 0); // Bottom left
         glTexCoord2d(1,0); glVertex3f(mSize, -mSize, 0); // Bottom right
      glEnd();
   }

   void Particle::update(float dt)
   {
      mElapsedTime += dt;

      if(mElapsedTime > mLife)
         mDead = true;
   }
}
