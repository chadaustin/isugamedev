// SkyDome Demo  -  October 2001
//
// Luis R. Sempé
// visual@spheregames.com
// Sphere Games (http://www.spheregames.com)
// 
// You may use, copy, distribute or create derivative software
// for any purpose. If you do, I'd appreciate it if you write me 
// and let me know what you do with it. Thanks!
// Have fun!
////////////////////////////////////////////////////

#include <GL/glut.h>
#include <string.h>
#include <math.h>

#include "SkyDome.h"
#include <stdlib.h>

#define PI 3.1415926535897f
#define DTOR (PI/180.0f)
#define SQR(x) (x*x)

typedef struct {
	float x,y,z;
	unsigned int color;
	float u, v;
} VERTEX;


VERTEX *Vertices;
int NumVertices;

void GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile)
{
	int theta, phi;

	// Make sure our vertex array is clear
	if (Vertices) 
	{
		delete Vertices;
		Vertices = NULL;
		NumVertices = 0;
	}

	// Initialize our Vertex array
	NumVertices = (int)((360/dtheta)*(90/dphi)*4);
	Vertices = new VERTEX[NumVertices];
        memset(Vertices, 0, sizeof(VERTEX)*NumVertices);

	// Used to calculate the UV coordinates
	float vx, vy, vz, mag;

	// Generate the dome
	int n = 0;
	for (phi=0; phi <= 90 - dphi; phi += (int)dphi)
	{
		for (theta=0; theta <= 360 - dtheta; theta += (int)dtheta)
		{
			// Calculate the vertex at phi, theta
			Vertices[n].x = radius * sinf(phi*DTOR) * cosf(DTOR*theta);
			Vertices[n].y = radius * sinf(phi*DTOR) * sinf(DTOR*theta);
			Vertices[n].z = radius * cosf(phi*DTOR);

			// Create a vector from the origin to this vertex
			vx = Vertices[n].x;
			vy = Vertices[n].y;
			vz = Vertices[n].z;

			// Normalize the vector
			mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
			vx /= mag;
			vy /= mag;
			vz /= mag;

			// Calculate the spherical texture coordinates
			Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
			Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;		
			n++;

			// Calculate the vertex at phi+dphi, theta
			Vertices[n].x = radius * sinf((phi+dphi)*DTOR) * cosf(theta*DTOR);
			Vertices[n].y = radius * sinf((phi+dphi)*DTOR) * sinf(theta*DTOR);
			Vertices[n].z = radius * cosf((phi+dphi)*DTOR);
			
			// Calculate the texture coordinates
			vx = Vertices[n].x;
			vy = Vertices[n].y;
			vz = Vertices[n].z;

			mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
			vx /= mag;
			vy /= mag;
			vz /= mag;

			Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
			Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;		
			n++;

			// Calculate the vertex at phi, theta+dtheta
			Vertices[n].x = radius * sinf(DTOR*phi) * cosf(DTOR*(theta+dtheta));
			Vertices[n].y = radius * sinf(DTOR*phi) * sinf(DTOR*(theta+dtheta));
			Vertices[n].z = radius * cosf(DTOR*phi);
			
			// Calculate the texture coordinates
			vx = Vertices[n].x;
			vy = Vertices[n].y;
			vz = Vertices[n].z;

			mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
			vx /= mag;
			vy /= mag;
			vz /= mag;

			Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
			Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;		
			n++;

			if (phi > -90 && phi < 90)
			{
				// Calculate the vertex at phi+dphi, theta+dtheta
				Vertices[n].x = radius * sinf((phi+dphi)*DTOR) * cosf(DTOR*(theta+dtheta));
				Vertices[n].y = radius * sinf((phi+dphi)*DTOR) * sinf(DTOR*(theta+dtheta));
				Vertices[n].z = radius * cosf((phi+dphi)*DTOR);
				
				// Calculate the texture coordinates
				vx = Vertices[n].x;
				vy = Vertices[n].y;
				vz = Vertices[n].z;

				mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
				vx /= mag;
				vy /= mag;
				vz /= mag;

				Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
				Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;		
				n++;
			}
		}
	}

	// Fix the problem at the seam
	for (int i=0; i < NumVertices-3; i++)
	{
		if (Vertices[i].u - Vertices[i+1].u > 0.9f)
			Vertices[i+1].u += 1.0f;

		if (Vertices[i+1].u - Vertices[i].u > 0.9f)
			Vertices[i].u += 1.0f;

		if (Vertices[i].u - Vertices[i+2].u > 0.9f)
			Vertices[i+2].u += 1.0f;

		if (Vertices[i+2].u - Vertices[i].u > 0.9f)
			Vertices[i].u += 1.0f;

		if (Vertices[i+1].u - Vertices[i+2].u > 0.9f)
			Vertices[i+2].u += 1.0f;

		if (Vertices[i+2].u - Vertices[i+1].u > 0.9f)
			Vertices[i+1].u += 1.0f;

		if (Vertices[i].v - Vertices[i+1].v > 0.8f)
			Vertices[i+1].v += 1.0f;

		if (Vertices[i+1].v - Vertices[i].v > 0.8f)
			Vertices[i].v += 1.0f;

		if (Vertices[i].v - Vertices[i+2].v > 0.8f)
			Vertices[i+2].v += 1.0f;

		if (Vertices[i+2].v - Vertices[i].v > 0.8f)
			Vertices[i].v += 1.0f;

		if (Vertices[i+1].v - Vertices[i+2].v > 0.8f)
			Vertices[i+2].v += 1.0f;

		if (Vertices[i+2].v - Vertices[i+1].v > 0.8f)
			Vertices[i+1].v += 1.0f;
	}
}

int RenderSkyDome()
{
	glPushMatrix();
	glTranslatef(0.0f, -100.0f, 0.0f);
	glRotatef(glutGet(GLUT_ELAPSED_TIME)/2000.0f,0.0f, 1.0f, 0.0f);
	glRotatef(270, 1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLE_STRIP);

	for (int i=0; i < NumVertices; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(Vertices[i].u, Vertices[i].v);
		glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
	}

	glEnd();

	glPopMatrix();
	return 1;
}

void ReleaseDome()
{
	if (Vertices)
	{
		delete Vertices;
		Vertices = NULL;
	}
}
