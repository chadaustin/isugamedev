#include "TurretGraphics.h"

TurretGraphics::TurretGraphics()
{
	ambient[0] = 0.2;
	ambient[1] = 0.2;
	ambient[2] = 0.2;
	ambient[3] = 1.0;

	diffuse[0] = 0.3;
	diffuse[1] = 1.0;
	diffuse[2] = 0.2;
	diffuse[3] = 1.0;

	specular[0] = 0.0;
	specular[1] = 0.0;
	specular[2] = 0.0;
	specular[3] = 1.0;

	shininess = 65.0;

	smoothing_angle = 90.0;

   float Rotate[3];
   for(int i = 0; i < 3; i++)
      Rotate[i] = 0.0;

   this->SetRotate(Rotate);

   float Center[3];

   Center[0] = 0.0;
   Center[1] = -0.5;
   Center[2] = 0.0;

   this->SetCenter(Center);
}

void TurretGraphics::Init()
{
	model = glmReadOBJ("models/HoverTankTurret.obj");
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, smoothing_angle);

	model_list = glmList(model, GLM_SMOOTH);
}
void TurretGraphics::Draw()
{
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   glMaterialf(GL_FRONT, GL_SHININESS, shininess);

   float Center[3];
   float Rotate[3];

   this->GetCenter(Center);
   this->GetRotate(Rotate);

   glRotatef(Rotate[2], 0.0, 0.0, 1.0);
   glRotatef(Rotate[1], 0.0, 1.0, 0.0);
   glRotatef(Rotate[0], 1.0, 0.0, 0.0);

   glTranslatef(Center[0], Center[1], Center[2]);

   glCallList(model_list);

}


