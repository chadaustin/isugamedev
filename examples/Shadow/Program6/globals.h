#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <gl/glut.h>


#define PI 3.1415926535897f
#define DTOR (PI/180.0f)
#define SQR(x) (x*x)

typedef struct {
	float x,y,z;
	unsigned int color;
	float u, v;
} VERTEX;

extern VERTEX *Vertices;
extern int NumVertices;

#endif