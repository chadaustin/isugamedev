//////////////////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort lvanoort@aol.com Released under MIT.
// 
// Shadow.cpp
// 4-4-2002
//////////////////////////////////////////////////////////////////// 


#include "Shadow.h"
#include "GameObject.h"

Shadow::Shadow()
{
	for(int i = 0; i < 4; i++)
	{
		GroundPlane[i] = 0.0;
	}
	NumLights = 0;
}

Shadow::~Shadow()
{
	
}

int Shadow::AddLight(GLfloat TheLightPosition[4])
{
	LightPosition Temp;
	for(int i = 0; i < 4; i++)
	{
		Temp.ThePosition[i] = TheLightPosition[i];
	}

	MyLights.push_back(Temp);
	NumLights++;
	return NumLights-1;
}

void Shadow::SetLightPosition(int Handle, GLfloat TheLightPosition[4])
{
	for(int i = 0; i < 4; i++)
	{
		MyLights[Handle].ThePosition[i] = TheLightPosition[i];
	}

}

void Shadow::SetFloorObject(GameObject* TheObject)
{
	TheFloor = TheObject;
}

void Shadow::SetTheGroundPlane(GLfloat TheGroundPlane[4])
{
	for(int i = 0; i < 4; i++)
	{
		GroundPlane[i] = TheGroundPlane[i];
	}
}

void Shadow::DrawShadows(vector<GameObject*> &TheObjects)
{
	GLfloat floorShadow[4][4];

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 2, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	TheFloor->Draw();
	glDisable(GL_STENCIL_TEST);

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glColor3f(0.5, 0.5, 0.5);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_EQUAL, 2, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

	for(int index = 0; index < NumLights; index++)
	{
		glPushMatrix();
			ComputeShadowMatrix(floorShadow, GroundPlane, MyLights[index].ThePosition);
			glMultMatrixf((GLfloat *) floorShadow);
			glColor4f(0.5, 0.5, 0.5, 0.5);

			int i = 0;
			ObjectType ObjectName;

			if(TheObjects.size() > 0)
			{
				TheObjects[0]->GetCurrentObjectType(ObjectName);
			}

			while(i < TheObjects.size() && ObjectName != WALL)
			{
				TheObjects[i]->GetCurrentObjectType(ObjectName);
				TheObjects[i]->Draw();
				i++;
			}
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	///////////////////////////////////
}

void Shadow::ComputeShadowMatrix(GLfloat shadowMat[4][4], 
							GLfloat groundplane[4],
							GLfloat lightpos[4])
{
  GLfloat dot;

  /* Find dot product between light position vector and ground plane normal. */
  dot = groundplane[X] * lightpos[X] +
    groundplane[Y] * lightpos[Y] +
    groundplane[Z] * lightpos[Z] +
    groundplane[W] * lightpos[W];

  shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
  shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
  shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
  shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

  shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
  shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
  shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
  shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

  shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
  shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
  shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
  shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

  shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
  shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
  shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
  shadowMat[3][3] = dot - lightpos[W] * groundplane[W];

}

