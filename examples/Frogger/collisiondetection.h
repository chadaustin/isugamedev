/////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//			-- lvanoort@aol.com -- 
//				2/4/2002
//
// collisiondetection.h
/////////////////////////////////////////////////////

#ifndef __COLLISION_DETECTION_H__
#define __COLLISION_DETECTION_H__

#include "MyObject.h"
#include <vector>

using namespace std;

////////////////////////////////////////////////////////
//CollisionDetection
////////////////////////////////////////////////////////
// This class is a general Collision Detector for 2D
// games.  It will detect Collision between any objects
// as long as they are inhereted from MyObject Class.
// MyObject class needs the following members functions
//		GetGameCoordinates(float& x, float& y);
//		GetSize(float& x, float& y);
///////////////////////////////////////////////////////

struct EdgeStore
{
	float Edge;
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
	void AddObject(MyObject*& InObject);

	///////////////////////////////////////////////////
    // RemoveObject()
	///////////////////////////////////////////////////
	// Notes: This function removes the input object from
	//	Collision Dection List
	///////////////////////////////////////////////////
	void RemoveObject(MyObject*& InObject);
	
	///////////////////////////////////////////////////////
	//Move()
	////////////////////////////////////////////////////////
	// Notes: 
	//	Moves given object to new x, y position and Updates
	//	ObjectToMove Position to X,Y;
	////////////////////////////////////////////////////////
	void Move(MyObject*& ObjectToMove, float x, float y);

	///////////////////////////////////////////////////////
	//CheckForCollisions(Collisions)
	////////////////////////////////////////////////////////
	// Notes: 
	//	Call this after Move to find collisions.  If 
	//	collisions found returns true and Collisions holds
	//	a list of all collisions and Size hold the number of
	//  indexes in collisions array.
	//	Each vectors 1st item is the collision item and every
	//	item after that is an item that collided with the
	//	first item
	////////////////////////////////////////////////////////	
	bool CheckForCollisions(vector<MyObject*> Collisions[30], int& Size);

	vector<EdgeStore> MyObjectEdges;
////////////////////////////////////////////////////////////////////////
private:

	bool Moved;

	///////////////////////////////////////////////////////
	//Intersects()
	////////////////////////////////////////////////////////
	// Notes: 
	//	Returns true if two Objects intersect otherwise
	//  return false
	////////////////////////////////////////////////////////
	bool Intersects(MyObject* one,MyObject* two);

};

#endif