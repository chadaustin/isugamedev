#include "collisiondetection.h"
#include "MyObject.h"
#include "stdlib.h"
#include <iostream.h> //temporary

// The Collision detector was implemented using a sweeptest and only
// works for rectangles.  A dynamic array is used to store a data structure
// that contains an X coordinate of one edge a bool to decide where it
// is a right or left edge and a pointer back to the object it self.
// The dynamic array is sorted according to X coordinates and any ties
// then check the boolean all, lefts come before right edges.  If they are
// both the same here it doesn't matter which one comes first.  
// 
// When CheckForCollisions is called the array is then checked for overlapping 
// X coordinates these are then checked for an intersection.  An array of ObjectStore
// objects is then passed back with a list of all collisions.  
// The ObjectStore object is parsed as follows:
//		Each index represents a set of collisions
//		The first object in index is an First Collision Object
//		The remaining values are all the Objects that the First Object
//			collides with.
	

CollisionDetection::CollisionDetection()
{
	ArraySize = 100;
	CurrentInsertPos = 0;
	MyObjectEdges = new EdgeStore[ArraySize];

	///////////////////////////////////
	// Set all items in array to default
	// value
	///////////////////////////////////
	for (int i = 0; i < ArraySize; i++)
	{
		MyObjectEdges[i].Edge = -1;
		MyObjectEdges[i].start = false;
		MyObjectEdges[i].TheObject = NULL;
	}

}

CollisionDetection::~CollisionDetection()
{
	delete MyObjectEdges;
}

/////////////////////////////////////////////////
// AddObject()
/////////////////////////////////////////////////
// Notes:
//	Adds Object edges to Array in proper locations 
/////////////////////////////////////////////////
bool CollisionDetection::AddObject(MyObject*& InObject)
{
	int Junk[2];
	bool Inserted = false;
	bool Left = true;
	bool LocationFound;
	int Edges[2];
	int Location;

	InObject->GetGameCoordinates(Edges[0], Junk[0]);
	InObject->GetSize(Edges[1], Junk[0]);

	///////////////////////////////////////////
	//Need to set right edge to proper value
	//Currently it just holds size we to add
	//Left value to this to get Right Value
	///////////////////////////////////////////
	Edges[1] = Edges[1] + Edges[0];

	if (!FindIndexs(InObject, Junk[0], Junk[1]))
	{
		/////////////////////////////////////
		// Need to go through twice once for
		// each X coordinate
		/////////////////////////////////////
		for (int times = 0; times <= 1; times++)
		{
			Location = 0;
			LocationFound = false;

			///////////////////////////////
			// While Location is not Found
			// keep looking
			///////////////////////////////
			while(!LocationFound)
			{
				if(Edges[times] <= MyObjectEdges[Location].Edge || 
					Location == CurrentInsertPos)
					LocationFound = true;
				else
					Location++;
			}

			//////////////////////////////////////////
			// Once we find insert location shift all 
			// edges down to make room for new edge
			//////////////////////////////////////////
			for(int i = CurrentInsertPos; i > Location; i--)
			{
				MyObjectEdges[i].Edge = MyObjectEdges[i-1].Edge;
				MyObjectEdges[i].start = MyObjectEdges[i-1].start;
				MyObjectEdges[i].TheObject = MyObjectEdges[i-1].TheObject;
			}

			////////////////////////////////////////////////////
			// Lets insert the object after the first edge is 
			// inserted set left to false because next edge to be
			// inserted will be the right egde.  
			///////////////////////////////////////////////////// 
			MyObjectEdges[Location].Edge = Edges[times];
			MyObjectEdges[Location].start = Left;
			Left = false;
			MyObjectEdges[Location].TheObject = InObject;

			////////////////////////////////////////
			// Increment CurrentInsertPos if it gets
			// larger than arraysize resize the array
			////////////////////////////////////////
			CurrentInsertPos++;
			if (CurrentInsertPos >= ArraySize)		
				ResizeArray();
		}

		Inserted = true;
	}


	return Inserted;
}

/////////////////////////////////////////////////
// RemoveObject()
/////////////////////////////////////////////////
// Notes:
//	Sets the Edges in store array to default
//	values and shirks array.  
/////////////////////////////////////////////////
bool CollisionDetection::RemoveObject(MyObject*& InObject)
{ 	
	int LeftIndex, RightIndex;
	int Shifted = 0;
	bool Removed = false;

	if (FindIndexs(InObject, LeftIndex, RightIndex))
	{
		///////////////////////////////////////////
		// Start at LeftIndex of Rect to be removed
		// shift everything to the right down one 
		// position until you reach RightIndex - 1
		// ////////////////////////////////////////
		for (int Left = LeftIndex; Left < RightIndex; Left++)
		{
			MyObjectEdges[Left].Edge = MyObjectEdges[Left+1].Edge;
			MyObjectEdges[Left].start = MyObjectEdges[Left+1].start;
			MyObjectEdges[Left].TheObject = MyObjectEdges[Left+1].TheObject;
		}

		RightIndex--;

		//////////////////////////////////////////////////
		// Start where LeftIndex left off shift everything
		// to the right of RightIndex down 2 positions to
		// make up for the two deleted edges
		//////////////////////////////////////////////////
		for (int Right = RightIndex; Right < CurrentInsertPos-2; Right++)
		{
			MyObjectEdges[Right].Edge = MyObjectEdges[Right+2].Edge;
			MyObjectEdges[Right].start = MyObjectEdges[Right+2].start;
			MyObjectEdges[Right].TheObject = MyObjectEdges[Right+2].TheObject;
		}

		//////////////////////////////////////////
		// Remove the last two Edges they are no
		// longer needed and reset CurrentInsertPos
		//////////////////////////////////////////
		for (int i = CurrentInsertPos-2; i < CurrentInsertPos; i++)
		{
			MyObjectEdges[i].Edge = -1;
			MyObjectEdges[i].start = false;
			MyObjectEdges[i].TheObject = NULL;
		}
		CurrentInsertPos = CurrentInsertPos - 2;

		Removed = true;
	}

	return Removed;
}

///////////////////////////////////////////////////////
//Move()
///////////////////////////////////////////////////////
// Notes: 
//	
////////////////////////////////////////////////////////
bool CollisionDetection::Move(MyObject*& ObjectToMove, int x, int y)
{ 
	int NewLeftRight[2];
	int IndexsLeftRight[2];
	bool Left = true;
	bool moved = false;
	int OldLeftRight[2];
	int SizeX, SizeY;
	int IndexVariable;

	ObjectToMove->GetSize(SizeX, SizeY);

	if (FindIndexs(ObjectToMove, IndexsLeftRight[0], IndexsLeftRight[1]))
	{
		OldLeftRight[0] = MyObjectEdges[IndexsLeftRight[0]].Edge;
		OldLeftRight[1] = MyObjectEdges[IndexsLeftRight[1]].Edge;

		NewLeftRight[0] = x;
		NewLeftRight[1] = x+SizeX;

		for (int i = 0; i < 2; i++)
		{
			if (OldLeftRight[i] > NewLeftRight[i])
			{
				for(IndexVariable = IndexsLeftRight[i]; \
					NewLeftRight[i] < MyObjectEdges[IndexVariable-1].Edge && IndexVariable-1 >= 0; \
					IndexVariable--)
				{
					MyObjectEdges[IndexVariable].Edge = MyObjectEdges[IndexVariable-1].Edge;
					MyObjectEdges[IndexVariable].start = MyObjectEdges[IndexVariable-1].start;
					MyObjectEdges[IndexVariable].TheObject = MyObjectEdges[IndexVariable-1].TheObject;
				}

				MyObjectEdges[IndexVariable].Edge = NewLeftRight[i];
				MyObjectEdges[IndexVariable].start = Left;
				MyObjectEdges[IndexVariable].TheObject = ObjectToMove;
			}
			else if (OldLeftRight[i] < NewLeftRight[i])
			{
				for(IndexVariable = IndexsLeftRight[i]; \
					NewLeftRight[i] > MyObjectEdges[IndexVariable+1].Edge && IndexVariable+1 < CurrentInsertPos; \
					IndexVariable++)
				{
					MyObjectEdges[IndexVariable].Edge = MyObjectEdges[IndexVariable+1].Edge;
					MyObjectEdges[IndexVariable].start = MyObjectEdges[IndexVariable+1].start;
					MyObjectEdges[IndexVariable].TheObject = MyObjectEdges[IndexVariable+1].TheObject;
				}

				MyObjectEdges[IndexVariable].Edge = NewLeftRight[i];
				MyObjectEdges[IndexVariable].start = Left;
				MyObjectEdges[IndexVariable].TheObject = ObjectToMove;
			}
			//////////////////////////////////////////////
			// Object didn't move on X axis so we don't 
			// need to worry changing the array
			//////////////////////////////////////////////
			else
			{
				ObjectToMove->SetGameCoordinates(x,y);
				return true;
			}
			Left = false;
			FindIndexs(ObjectToMove, IndexsLeftRight[0], IndexsLeftRight[1]);
		}
		moved = true;
		ObjectToMove->SetGameCoordinates(x,y);
	}

	return moved;

}

bool CollisionDetection::CheckForCollisions(MyObjectStore*& Collisions, int& Size)
{
	// I really need to find a good data stucture to return the list of
	// collisions.  Currently the best I can come up with is using a 
	// array of myobjectstore with each index being a collision.  
	// The first object in the list is a collision and everyother
	// object in the list collides with that object.
	
	int NumCollisions = 10;
	Collisions = new MyObjectStore[NumCollisions];
	Size = 0;
	MyObject* Temp;
	MyObjectStore TempCollisions;
	bool CollisionFound = false;
	bool First;

	for (int i = 0; i < CurrentInsertPos; i++)
	{	
		if(MyObjectEdges[i].start)
		{
			TempCollisions.ResetCursor();
			TempCollisions.GetCurrentObject(Temp);
			First = true;

			while(Temp!=NULL)
			{
				if(Intersects(Temp, MyObjectEdges[i].TheObject))
				{
					if(First)
					{
						Collisions[Size].Insert(MyObjectEdges[i].TheObject);
						First = false;
						CollisionFound = true;
					}
					Collisions[Size].Insert(Temp);
				}
				TempCollisions.GetCurrentObject(Temp);
			}
			if(!First)
				Size++;

		TempCollisions.Insert(MyObjectEdges[i].TheObject);
		}
		else
		{
			TempCollisions.Remove(MyObjectEdges[i].TheObject);
		}
	}
	return CollisionFound;
}

bool CollisionDetection::Intersects(MyObject* one, MyObject* two)
{
	int OneXMax, OneYMax, OneXMin, OneYMin;
	int TwoXMax, TwoYMax, TwoXMin, TwoYMin;
	int sizex, sizey;

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

bool CollisionDetection::FindIndexs(MyObject* TheObject, int& LeftIndex, int& RightIndex)
{
	bool LeftFound = false;
	bool RightFound = false;

	for(int i = 0; i <= CurrentInsertPos; i++)
	{
		////////////////////////////////////
		// Seach for both edges and set
		// respective index variable
		////////////////////////////////////
		if(MyObjectEdges[i].TheObject == TheObject)
		{
			if (MyObjectEdges[i].start == true)
			{
				LeftIndex = i;
				LeftFound = true;
			}
			else
			{
				RightIndex = i;
				RightFound = true;
			}
		}
	}
	return LeftFound && RightFound;
}

void CollisionDetection::ResizeArray()
{
	EdgeStore* temp;
	int TempSize = ArraySize;
	int i;
	temp = new EdgeStore[ArraySize];

	/////////////////////////////////////////
	// Copy all current array items to 
	// temp to store while array is resized
	/////////////////////////////////////////
	for (i = 0; i < ArraySize; i++)
	{
		temp[i].Edge = MyObjectEdges[i].Edge;
		temp[i].start = MyObjectEdges[i].start;
		temp[i].TheObject = MyObjectEdges[i].TheObject;
	}

	//////////////////////////////////////////
	// Delete old array and recreate new one
	// twice the size
	//////////////////////////////////////////
	delete MyObjectEdges;
	ArraySize = ArraySize * 2;
	MyObjectEdges = new EdgeStore[ArraySize];

	////////////////////////////////////////
	// Copy all temp items back to original
	// array
	////////////////////////////////////////
	for (i = 0; i < TempSize; i++)
	{
		MyObjectEdges[i].Edge = temp[i].Edge;
		MyObjectEdges[i].start = temp[i].start;
		MyObjectEdges[i].TheObject = temp[i].TheObject;
	}

}

ostream& operator <<(ostream& outs, const CollisionDetection& source)
{
	for (int i = 0; i < source.CurrentInsertPos; i++)
	{
		outs << "Index: " << i << endl;
		outs << "Edge: " << source.MyObjectEdges[i].Edge << endl;
		outs << "Start: " << source.MyObjectEdges[i].start << endl;
		outs << "TheObject: " << source.MyObjectEdges[i].TheObject << endl;
	}
	if (source.CurrentInsertPos == 0)
		outs << "No Edges" << endl;
	return outs;
}