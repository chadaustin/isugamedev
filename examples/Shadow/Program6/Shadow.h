#ifndef __SHADOW_H__
#define __SHADOW_H__

#include "GameObject.h"
#include <vector>
#include <gl/glut.h>

using namespace std;

class Shadow
{
public:
	Shadow();

	~Shadow();

	void AddAObject(GameObject* TheObject);

	void SetFloorObject(GameObject* TheObject);

	void SetTheGroundPlane(GLfloat TheGroundPlane[4]);

	void SetTheLightPosition(GLfloat TheLightPosition[4]);

	void DrawShadows();

private:

	GLfloat GroundPlane[4];
	GLfloat LightPosition[4];
	vector<GameObject*> TheShadowObjects;
	GameObject* TheFloor;
	void ComputeShadowMatrix(GLfloat shadowMat[4][4], 
							GLfloat groundplane[4],
							GLfloat lightpos[4]);

	enum {X, Y, Z, W};
	enum {A, B, C, D};
};

#endif