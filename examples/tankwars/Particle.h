// Particle.h: interface for the Particle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLE_H__E54C5CA2_AE0E_11D5_9903_0001023C9B87__INCLUDED_)
#define AFX_PARTICLE_H__E54C5CA2_AE0E_11D5_9903_0001023C9B87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

// GLuint texture[1];

class Particle  
{

public:
	Particle();
	~Particle();
/*
	Vertex3d prev_location;				// Prev location of the particle
	Vertex3d location;					// Current location of particle
	Vertex3d velocity;					// Velocity of the particle

	float clolor[4];					// color of particle
	float colorCounter[4];				// some counter for the color

	float alpha;						// particles current transparency
	float alphaCounter;					// add/sub transparency over time

	float size;							// size of the particle
	float sizeCounter;					// add/sub size over time

	float age;							// current age of particle
	float lifeSpan;						// how old the particle can be

	void setParentSystem(ParticleSystem *parent);
	void create(ParticleSystem *parent, float timeCounter);
	bool update(float timeCounter);

private:
	
	ParticleSystem *MaAndPa;
*/
};

#endif // !defined(AFX_PARTICLE_H__E54C5CA2_AE0E_11D5_9903_0001023C9B87__INCLUDED_)
