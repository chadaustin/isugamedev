#include "genInclude.h"


bool ifNCollide(generic *obj1, generic *obj2);
//	returns true if obj1 is NOT colliding with obj2
//  takes in pointers to 2 objects

bool terrainCollide(generic *object, generic *terrain, bool &hitBack);