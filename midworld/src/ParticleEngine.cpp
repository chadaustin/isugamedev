#include "ParticleEngine.h"
#include "Utility.h"
#include <gmtl/VecOps.h>
#include <gmtl/Math.h>

namespace mw
{
	ParticleEngine::ParticleEngine(const std::string& filename, const int numParticles, const Camera& gameCamera)
	{
		ParticleTexture = new Texture(filename);
		ParticleCamera = gameCamera;

		for(int i = 0; i < numParticles; i++)
		{
			gmtl::Vec3f velocity = randomUnitVector();
			velocity *= gmtl::Math::rangeRandom(2.0, 5.0);

			Particle* temp = new Particle(gmtl::Math::rangeRandom(1.0, 2.0));
			temp->size(0.2);
			temp->setMass(0.10);
			temp->setVel(velocity);
			ParticleGroup.push_back(temp);
		}
	}

	ParticleEngine::~ParticleEngine()
	{
		delete ParticleTexture;
	}

	void ParticleEngine::setPos(const gmtl::Point3f& thePoint)
	{
		point = thePoint;
	}

	const gmtl::Point3f& ParticleEngine::getPos() const
	{
		return point;
	}

	bool ParticleEngine::isExpired()
	{	
		if(ParticleGroup.size() == 0)
			return true;
		else 
			return false;
	}

	void ParticleEngine::draw()
	{
		gmtl::Vec3f CameraPos = ParticleCamera.getPos();
		gmtl::Point3f PartPos;
		ParticleTexture->bind();
		
		//billboardBegin();
		glDisable(GL_DEPTH_TEST);							
		//glEnable(GL_BLEND);									
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE);		
		for(ParticleList::iterator i=ParticleGroup.begin(); i != ParticleGroup.end(); ++i)
		{
			PartPos = (*i)->getPos();
			billboardBegin(CameraPos, PartPos); 
			(*i)->draw();
			billboardEnd();
		}
		//glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		//billboardEnd();

		ParticleTexture->unbind();
	}

	void ParticleEngine::update(float dt)
	{
		for(ParticleList::iterator i=ParticleGroup.begin(); i != ParticleGroup.end();)
		{
			(*i)->addForce(ParticlePhysics->GRAVITY * (*i)->getMass());
			(*i)->update(dt);
			ParticlePhysics->update((*i), dt);
			(*i)->moveToNextState();
			if((*i)->isExpired())
			{	
				delete (*i);
				i = ParticleGroup.erase(i);
			}
			else
				i++;
		}
	}

	/*void ParticleEngine::billboardBegin()
	{
		float modelview[16];
		int i,j;

		// save the current modelview matrix
		glPushMatrix();

		// get the current modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

		// undo all rotations
		// beware all scaling is lost as well 
		for( i=0; i<3; i++ ) 
		{
			for( j=0; j<3; j++ ) 
			{
				if ( i==j )
					modelview[i*4+j] = 1.0;
				else
					modelview[i*4+j] = 0.0;
			}
		}

		// set the modelview with no rotations
		glLoadMatrixf(modelview);
	}*/

	void ParticleEngine::billboardBegin(gmtl::Vec3f cam,gmtl::Vec3f objPos)									
	{

		gmtl::Vec3f lookAt,objToCamProj,upAux, objToCam;
		gmtl::Matrix44f modelview;
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
		//mathsNormalize(objToCamProj);

	// easy fix to determine wether the angle is negative or positive
	// for positive angles upAux will be a vector pointing in the 
	// positive y direction, otherwise upAux will point downwards
	// effectively reversing the rotation.

		upAux = gmtl::cross(lookAt, objToCamProj);
		//mathsCrossProduct(upAux,lookAt,objToCamProj);

	// compute the angle
		angleCosine = gmtl::dot(lookAt, objToCamProj);
		//angleCosine = mathsInnerProduct(lookAt,objToCamProj);

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
		//mathsNormalize(objToCam);

	// Compute the angle between objToCamProj and objToCam, 
	//i.e. compute the required angle for the lookup vector

		angleCosine = gmtl::dot(objToCamProj,objToCam);
		//angleCosine = mathsInnerProduct(objToCamProj,objToCam);


	// Tilt the object. The test is done to prevent instability 
	// when objToCam and objToCamProj have a very small
	// angle between them

		if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
			if (objToCam[1] < 0)
				glRotatef(acos(angleCosine)*180/3.14,1,0,0);	
			else
				glRotatef(acos(angleCosine)*180/3.14,-1,0,0);	
	      
	}

	void ParticleEngine::billboardEnd()
	{
		// restore the previously 
		// stored modelview matrix
		glPopMatrix();
	}
}
