/////////////////////////////////////
// Copyright Levi VanOort 5-3-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// AIEngine.h
/////////////////////////////////////

#ifndef __AIENGINE_H
#define __AIENGINE_H

#include "GameObject.h"
#include "TankObject.h"
#include <vector>

using namespace std;

class AIEngine
{
public:
	void Init();

	void SetNPCTank(GameObject* NPCTank);

	void SetPlayer(GameObject* Player1);

	void Update(vector<GameObject*> &TheObjects, int dt);

	void RotateToFaceOpponent();

private:

	GameObject* ToKill;
	GameObject* ToControl;
	bool FacingOpponent;
	bool MovingAroundBlock;
	bool Rotate;

};

#endif