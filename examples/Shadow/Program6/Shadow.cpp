//////////////////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort lvanoort@aol.com Released under MIT.
// 
// Shadow.cpp
// 4-4-2002
//////////////////////////////////////////////////////////////////// 


#include "Shadow.h"

extern GLuint grass[1];
extern GLuint clouds[1];

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

void Shadow::AddAObject(GameObject* TheObject)
{
	TheShadowObjects.push_back(TheObject);
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

void Shadow::DrawShadows()
{
	GLfloat floorShadow[4][4];

	glEnable(GL_BLEND);

	glEnable(GL_STENCIL_TEST);
	glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_ALWAYS, 2, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass[0]);
	TheFloor->Draw();
	glDisable(GL_TEXTURE_2D);
 
	/////////////////////////////////
	// Draw shadows
	/////////////////////////////////
	glDisable(GL_LIGHTING);
	glStencilFunc(GL_EQUAL, 2, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);


	for(int index = 0; index < NumLights; index++)
	{
		glPushMatrix();
			ComputeShadowMatrix(floorShadow, GroundPlane, MyLights[index].ThePosition);
			glMultMatrixf((GLfloat *) floorShadow);
			glColor4f(0.5, 0.5, 0.5, 0.5);
			for(int i = 0; i < TheShadowObjects.size(); i++)
				TheShadowObjects[i]->Draw();
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

