#include "Particle.h"
#include <SDL_opengl.h>

namespace mw
{
	Particle::Particle(float particleLife)
	{
		life = particleLife;
		dead = false;
		elapsedTime = 0.0;
	}

	Particle::~Particle()
	{

	}

	bool Particle::isExpired() const
	{
		return dead;
	}

	void Particle::size(float particleSize)
	{
		theSize = particleSize;
	}

	void Particle::draw()
	{
		const gmtl::Point3f& pos = this->getPos();
		
		glBegin(GL_QUADS);
			glTexCoord2d(1,1); glVertex3f(pos[0]+theSize,pos[1]+theSize,pos[2]);
			glTexCoord2d(0,1); glVertex3f(pos[0]-theSize,pos[1]+theSize,pos[2]); // Top Left
			glTexCoord2d(1,0); glVertex3f(pos[0]+theSize,pos[1]-theSize,pos[2]); // Bottom Right
			glTexCoord2d(0,0); glVertex3f(pos[0]-theSize,pos[1]-theSize,pos[2]); // Bottom Left
		glEnd();

	}

	void Particle::update(float dt)
	{
		elapsedTime += dt;

		if(elapsedTime > life)
			dead = true;
	}
}

