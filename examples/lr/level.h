#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include <GL/glaux.h>

#ifndef LEVEL
#define LEVEL

// player state information
#define RUN 0
#define CLIMB 1
#define HANG 2
#define FALL 3

// registry state info
#define EMPTY 0
#define BRICK  1
#define LADDER  2
#define WIRE  3
#define MONEY  4



#include "player.h"
#include "textures.h"

class level{
public:

	level();
	~level();


	int init();
protected:	
	void drawBrick(int left, int right, int height);
	void drawLadder(int base, int height, int spot);
	void drawWire(int left, int right, int height);
	void drawMoneyBag(int pos, int height);

public:
	int getAmount(){return amount;}
	void loadlevel();
	void registerBrick(int left, int right, int height);
	void registerLadder(int base, int hieght, int spot);
	void registerWire(int left, int right, int height);
	void registerMoney(int pos, int height);
	void registerguy(int pos, int height);
	int checkRegistry(int pos, int height);
	void removeBrick(int pos, int height);
	void removeMoney(int pos, int height);
	void draw();
	void initTexture();	
	void setFalling();
	void collision();
	void isMoney(int pos, int height);


private:
	int (*registry)[15];	// a 64 by 15 array for the width 
							// by height of everything but people
	bool falling;		// bool set when player is falling
	COGLTexture textures[2];
	int amount;			// number of moneybags;
	

};

#endif