#ifndef __COLLISION_DETECTION_H__
#define __COLLISION_DETECTION_H__

#include "MyObject.h"
#include "myobjectstore.h"
#include <iostream.h> //temporary

struct EdgeStore
{
	int Edge;
	bool start;
	MyObject* TheObject;
};

/////////////////////////////////////////////////////
// Notes:
//	Once an object is added to the CollsionDetection
//  none of the SetFuctions should be used on the object
//  except SetState unless the CollisionDetection Class
//  is updated with the new object properties.  
//   ** i.e.  Object is Removed and then ReAdded.
//////////////////////////////////////////////////////
class CollisionDetection
{
public:
	CollisionDetection();

	~CollisionDetection();

	///////////////////////////////////////////////////
    // AddObject()
	///////////////////////////////////////////////////
	// Notes: This function adds the input object to
	//	Collision Dection List
	///////////////////////////////////////////////////
	bool AddObject(MyObject*& InObject);

	///////////////////////////////////////////////////
    // RemoveObject()
	///////////////////////////////////////////////////
	// Notes: This function removes the input object from
	//	Collision Dection List
	///////////////////////////////////////////////////
	bool RemoveObject(MyObject*& InObject);
	
	///////////////////////////////////////////////////////
	//Move()
	////////////////////////////////////////////////////////
	// Notes: 
	//	Moves given object to new x, y position and Updates
	//	ObjectToMove Position to X,Y;
	////////////////////////////////////////////////////////
	bool Move(MyObject*& ObjectToMove, int x, int y);

	///////////////////////////////////////////////////////
	//CheckForCollisions(MyObjectStore&)
	////////////////////////////////////////////////////////
	// Notes: 
	//	Call this after Move to find collisions.  If 
	//	collisions found returns true and Collisions holds
	//	a list of all collisions and Size hold the number of
	//  indexes in collisions array.
	////////////////////////////////////////////////////////	
	bool CheckForCollisions(MyObjectStore*& Collisions, int& Size);

	friend ostream& operator <<(ostream& outs, const CollisionDetection& source);

////////////////////////////////////////////////////////////////////////
private:
	EdgeStore* MyObjectEdges;
	int CurrentInsertPos;
	int ArraySize;


	///////////////////////////////////////////////////////
	//Intersects()
	////////////////////////////////////////////////////////
	// Notes: 
	//	Returns true if two Objects intersect otherwise
	//  return false
	////////////////////////////////////////////////////////
	bool Intersects(MyObject* one,MyObject* two);

	///////////////////////////////////////////////////////
	//Find()
	////////////////////////////////////////////////////////
	// Notes: 
	//	If TheObject is found returns true and LeftIndex, 
	//	RightIndex hold the index of both x rect edges.
	//	If TheObject is not found return false.
	//	LeftIndex, RightIndex remain unchanged.
	////////////////////////////////////////////////////////
	bool FindIndexs(MyObject* TheObject, int& LeftIndex, int& RightIndex);

	void ResizeArray();


};

#endif