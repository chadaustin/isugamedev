//////////////////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort lvanoort@aol.com Released under MIT.
// 
// Shadow.h
// 4-4-2002
//////////////////////////////////////////////////////////////////// 


#ifndef __SHADOW_H__
#define __SHADOW_H__

#include "GameObject.h"
#include <vector>
#include <GL/glut.h>

using namespace std;

struct LightPosition
{
	GLfloat ThePosition[4];
};

class Shadow
{
public:
	Shadow();

	~Shadow();

	int AddLight(GLfloat TheLightPosition[4]);

	void SetFloorObject(GameObject* TheObject);

	void SetTheGroundPlane(GLfloat TheGroundPlane[4]);

	void SetLightPosition(int Handle, GLfloat TheLightPosition[4]);

	void DrawShadows(vector<GameObject*> &TheObjects);

private:

	GLfloat GroundPlane[4];
	vector<LightPosition> MyLights;
	GameObject* TheFloor;
	int NumLights;
	void ComputeShadowMatrix(GLfloat shadowMat[4][4], 
							GLfloat groundplane[4],
							GLfloat lightpos[4]);

	enum {X, Y, Z, W};
	enum {A, B, C, D};
};

#endif
