#include "TankGraphics.h"

TankGraphics::TankGraphics()
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
}

void TankGraphics::Init()
{
	model = glmReadOBJ("HoverTankBody.obj");
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, smoothing_angle);

	model_list = glmList(model, GLM_SMOOTH);
}
void TankGraphics::Draw()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glCallList(model_list);

}


