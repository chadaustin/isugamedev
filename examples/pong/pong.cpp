#include "pong.h"
#include <math.h>

float toRad(int ang)
{
	return ang * (3.141592/180);
}

float coss(int ang)
{
	return cos(toRad(ang));
}

float sinn(int ang)
{
	return sin(toRad(ang));
}
