#ifndef PONG_H
#define PONG_H


float toRad(int ang);
float coss(int ang);
float sinn(int ang);

struct Vector
{
	int magnitude;
	int angle;			//0 degrees points to the right (I think)
	float x_component;
	float y_component;
};

struct pongball
{
	int x;
	int y;
	int radius;
	Vector vel;
};

#endif