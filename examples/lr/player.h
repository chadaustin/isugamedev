#ifndef PLAYER
#define PLAYER



#ifdef WIN32
#include <windows.h>  // make the app win32 friendly. :)
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include <GL/glaux.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "textures.h"

class player{
public:
	player();
	player(int Pheight, int Ppos, int Pstate, bool fall){
		height = Pheight;
		pos = Ppos;
		state = Pstate;
		falling = fall;
		texState =0;
	}
	virtual void draw();
	virtual void setState(int st){state = st;}
	virtual int getState(){return state;}
	virtual void setPos(int p){pos = p;}
	virtual void setHeight(int h){height = h;}
	virtual int getPos(){return pos;}
	virtual int getHeight(){return height;}
	virtual void initTexture();
	virtual void setFalling(){falling=true;}
	virtual void setNotFalling(){falling = false;}
	virtual bool isFalling(){ return falling;}
	virtual int getTexState(){return texState;}
	virtual void setTexState(int state){texState = state;}

protected:
	int pos;			// players horizontal position on a scale of 1 to 640
	int height;		// players height by 10;
	int state;			// players current state either hang1,2, climb1,2, or run1,2,
	COGLTexture textures[6];
	bool falling;
	int texState;		//: state to flip textures around
						//  0 = running
						//  1 = running
						//  2 = climbing
						//  3 = climbing
						//  4 = hanging
						//  5 = hanging
	
};

#endif