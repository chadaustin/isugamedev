/////////////////////////////////////
// Copyright Levi VanOort 5-2-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// BuildMaze.h
/////////////////////////////////////
#ifndef __BUILDMAZE_H
#define __BUILDMAZE_H

#include "WallObject.h"
#include "GameObject.h"

void BuildEdgeWalls(vector<GameObject*> &TheObjects)
{
	GameObject* Wall;
	float Position[3];

	Position[0] = 99.5;
	Position[1] = 0;
	Position[2] = 0.5;

	int i;

	// Build the containing walls
	for(i = 0; i < 100; i++)
	{
		Position[2] = 0.5;
		Position[1] = i+.5;
		Position[0] = 99.5;

		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);
		
		Position[0] = -99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[0] = 99.5;
		Position[2] = 1.5;

		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[0] = -99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);
		
		Position[0] = 99.5;
		Position[2] = 0.5;
		Position[1] *= -1;

		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[0] = -99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[0] = 99.5;
		Position[2] = 1.5;

		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[0] = -99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);
	}

	Position[0] = 0;
	Position[1] = 99.5;
	Position[2] = 0.5;

	for(i = 0; i < 100; i++)
	{
		Position[0] = i+.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[1] = -99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);
		
		Position[1] = 99.5;
		Position[2] = 1.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[1] = -99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[1] = 99.5;
		Position[0] *= -1;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[1] = -99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[2] = .5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);
	
		Position[1] = 99.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);
	}
}

void BuildSingleWall(int x, int y, int length, bool Orientation, 
					 vector<GameObject*> &TheObjects)
{
	GameObject* Wall;
	float Position[3];

	if(Orientation)
	{
		Position[1] = y;

		for(float height = .5; height < 2; height += 1.0)
		{
			Position[2] = height;
			for(int i = x; i < x+length; i++)
			{
				Position[0] = i;
				Wall = new WallObject;
				Wall->SetPosition(Position);
				TheObjects.push_back(Wall);
			}
		}
	}
	else
	{
		Position[0] = x;

		for(float height = .5; height < 2; height += 1.0)
		{
			Position[2] = height;
			for(int i = y; i < y+length; i++)
			{
				Position[1] = i;
				Wall = new WallObject;
				Wall->SetPosition(Position);
				TheObjects.push_back(Wall);
			}
		}
	}
}

void BuildInternalWalls(vector<GameObject*> &TheObjects)
{
	BuildSingleWall(50, 50, 20, true, TheObjects);
	BuildSingleWall(50, 50, 20, false, TheObjects);

	BuildSingleWall(-50, 50, 20, true, TheObjects);
	BuildSingleWall(-30, 50, 20, false, TheObjects);

	BuildSingleWall(50, -30, 20, true, TheObjects);
	BuildSingleWall(50, -50, 20, false, TheObjects);

	BuildSingleWall(-50, -31, 20, true, TheObjects);
	BuildSingleWall(-30, -50, 20, false, TheObjects);

	BuildSingleWall(40, -30, 60, false, TheObjects);
	BuildSingleWall(-40, -30, 60, false, TheObjects);

	BuildSingleWall(-30, -60, 30, true, TheObjects);
	BuildSingleWall(-30, 60, 30, true, TheObjects);

	BuildSingleWall(-40, 0, 50, true, TheObjects);

}

void BuildMaze(vector<GameObject*> &TheObjects)
{
	BuildEdgeWalls(TheObjects);
	BuildInternalWalls(TheObjects);
}

#endif