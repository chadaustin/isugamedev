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

		Position[2] = 1.5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[0] *= -1;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);

		Position[2] = .5;
		Wall = new WallObject;
		Wall->SetPosition(Position);
		TheObjects.push_back(Wall);
	
	}
}

void BuildMaze(vector<GameObject*> &TheObjects)
{
	BuildEdgeWalls(TheObjects);
}

#endif