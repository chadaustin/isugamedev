/////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//			-- lvanoort@aol.com -- 
//				2/4/2002
//
// collisiondetection.cpp
/////////////////////////////////////////////////////

#include "collisiondetection.h"
#include "MyObject.h"
#include "stdlib.h"
#include <vector>
#include <algorithm>

// The Collision detector was implemented using a sweeptest and ONLY
// WORKS FOR RECTANGLES. 
 
// Implementation Notes:
// A vector is used to store a data structure
// that contains an X coordinate of one edge a bool to decide where it
// is a right or left edge and a pointer back to the object it self.
// The vector is sorted according to X coordinates and any ties
// then check the boolean all, lefts come before right edges.  If they are
// both the same here it doesn't matter which one comes first.  
// 
// When CheckForCollisions is called the vector is then checked for overlapping 
// X coordinates these are then checked for an intersection.  A vectir of ObjectStore
// objects is then passed back with a list of all collisions.  
// The ObjectStore object is parsed as follows:
//		Each index represents a set of collisions
//		The first object in index is an First Collision Object
//		The remaining values are all the Objects that the First Object
//			collides with.
	

CollisionDetection::CollisionDetection()
{
	Moved = false;

}

CollisionDetection::~CollisionDetection()
{

}

/////////////////////////////////////////////////
// AddObject()
/////////////////////////////////////////////////
// Notes:
//	Adds Object edges to Array in proper locations 
/////////////////////////////////////////////////
void CollisionDetection::AddObject(MyObject*& InObject)
{
	float Edges[2];
	float Junk[2];
	EdgeStore temp;
	bool Left = true;


	InObject->GetGameCoordinates(Edges[0], Junk[0]);
	InObject->GetSize(Edges[1], Junk[1]);

	Edges[1] = Edges[0] + Edges[1];

	for (int i = 0; i < 2; i++)
	{
		temp.Edge = Edges[i];
		temp.start = Left;
		temp.TheObject = InObject;

		MyObjectEdges.push_back(temp);

		Left = false;
	}

	Moved = true;
}

/////////////////////////////////////////////////
// RemoveObject()
/////////////////////////////////////////////////
// Notes:
//	Sets the Edges in store array to default
//	values and shirks array.  
/////////////////////////////////////////////////
void CollisionDetection::RemoveObject(MyObject*& InObject)
{ 	
	unsigned int Index;

	Index = 0;
	while(Index < MyObjectEdges.size())
	{
		if(MyObjectEdges[Index].TheObject == InObject)
			MyObjectEdges.erase(MyObjectEdges.begin()+Index);
		else
			Index++;
	}

	Moved = true;

}

///////////////////////////////////////////////////////
//Move()
///////////////////////////////////////////////////////
// Notes: 
//	
////////////////////////////////////////////////////////
void CollisionDetection::Move(MyObject*& ObjectToMove, float x, float y)
{ 
	unsigned int Index = 0;
	float SizeX, SizeY;

	ObjectToMove->GetSize(SizeX, SizeY);

	while(Index < MyObjectEdges.size())
	{
		if(MyObjectEdges[Index].TheObject == ObjectToMove && MyObjectEdges[Index].start == true)
			MyObjectEdges[Index].Edge = x;
		else if(MyObjectEdges[Index].TheObject == ObjectToMove)
		{
			MyObjectEdges[Index].Edge = x+SizeX;
			Moved = true;
		}
		Index++;
	}

}

bool CollisionDetection::CheckForCollisions(vector<MyObject*> Collisions[30], int& Size)
{
	// The first object in the list is a collision and everyother
	// object in the list collides with that object.

	Size = 0;
	MyObject* Temp;
	vector<MyObject*> TempCollisions;
	bool CollisionFound = false;
	bool First;

	if(Moved)
	{
		Moved = false;
		sort(MyObjectEdges.begin(), MyObjectEdges.end());

		for (unsigned int i = 0; i < MyObjectEdges.size(); i++)
		{	
			if(MyObjectEdges[i].start)
			{
				unsigned int index = 0;
				First = true;

				while(index < TempCollisions.size())
				{
					Temp = TempCollisions[index];
					if(Intersects(Temp, MyObjectEdges[i].TheObject))
					{
						if(First)
						{
							Collisions[Size].push_back(MyObjectEdges[i].TheObject);
							First = false;
							CollisionFound = true;
						}
						Collisions[Size].push_back(Temp);
					}
					index++;
				}
				if(!First)
					Size++;

			TempCollisions.push_back(MyObjectEdges[i].TheObject);
			}
			else
			{
				int cursor = 0;

				while(TempCollisions[cursor] != MyObjectEdges[i].TheObject)
					cursor++;
				TempCollisions.erase(TempCollisions.begin()+cursor);
			}
		}
	}
	return CollisionFound;
}

bool CollisionDetection::Intersects(MyObject* one, MyObject* two)
{
	float OneXMax, OneYMax, OneXMin, OneYMin;
	float TwoXMax, TwoYMax, TwoXMin, TwoYMin;
	float sizex, sizey;

	///////////////////////////////////////////////
	// Lets get all info for intersection detection
	///////////////////////////////////////////////
	one->GetGameCoordinates(OneXMin, OneYMin);
	one->GetSize(sizex, sizey);

	OneXMax = OneXMin+sizex;
	OneYMax = OneYMin+sizey;

	two->GetGameCoordinates(TwoXMin, TwoYMin);
	two->GetSize(sizex, sizey);

	TwoXMax = TwoXMin+sizex;
	TwoYMax = TwoYMin+sizey;

	///////////////////////////////////
	// Actually check for collision
	////////////////////////////////////
	if (OneXMin > TwoXMax) return false;
	if (TwoXMin > OneXMax) return false;
	if (OneYMin > TwoYMax) return false;
	if (TwoYMin > OneYMax) return false;
	return true;
}

bool operator <(EdgeStore Left, EdgeStore Right)
{
	if((Left.Edge < Right.Edge) || 
		((Left.Edge == Right.Edge && Left.start == true) && (Right.start == false)))
		return true;
	else
		return false;
}



