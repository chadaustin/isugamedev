#include "collide.h"

bool ifNCollide(generic *obj1, generic *obj2)
{
	bool nCollide = true;

	GLfloat obj1X = obj1->getX();
	GLfloat obj1Z = obj1->getZ();
	GLfloat obj1Extents = obj1->getExtents();

	GLfloat obj2X = obj2->getX();
	GLfloat obj2Z = obj2->getZ();
	GLfloat obj2Extents = obj2->getExtents();

	GLfloat maxLength = obj1Extents + obj2Extents;
	GLfloat lengthBetween = sqrt(((obj1X - obj2X)*(obj1X - obj2X)) + ((obj1Z - obj2Z)*(obj1Z - obj2Z)));

	if ( lengthBetween <= maxLength)
		nCollide = false;

	return nCollide;
}

bool terrainCollide(generic *object, generic *terrain, bool &hitBack)
{
	bool collide = false;

	GLfloat boundary = terrain->getExtents();
	GLfloat objX = object->getX();
	GLfloat objZ = object->getZ();
	GLfloat objExtents = object->getExtents();

	if( (objX - objExtents) < (-boundary) )
	{
		// object is hitting the right wall
		collide = true;

		if(object->getAngle() < 90 || object->getAngle() > 270)
		{
			// front end collision
			hitBack = false;
		}
	}
	else if((objX + objExtents) > boundary)
	{
		// object hitting left wall
		collide = true;

		if(object->getAngle() < 90 || object->getAngle() > 270)
		{
			// back end collision
			hitBack = true;
		}
	}
	else if((objZ - objExtents) < (-boundary))
	{
		// hitting bottom wall
		collide = true;

		if(object->getAngle() > 180)
		{
			// front end collision
			hitBack = false;
		}
	}
	else if ((objZ + objExtents) > (boundary))
	{
		// hitting top wall
		collide = true;

		if(object->getAngle() < 180)
		{
			// back end collision
			hitBack = true;
		}
	}

	return collide;
}