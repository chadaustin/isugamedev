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
	GLfloat lengthBetween = sqrt(((obj1X + obj2X)*(obj1X + obj2X)) + ((obj1Z + obj2Z)*(obj1Z + obj2Z)));

	if ( lengthBetween <= maxLength)
		nCollide = false;

	return nCollide;
}