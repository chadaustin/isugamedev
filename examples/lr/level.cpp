#include "level.h"
#include "player.h"
#include <iostream>
#include <GL/glu.h>
#include <GL/gl.h>



int level::init(){
return 0;
}

level::level(){
	registry = new int[64][15];
	int i,j;
	for(i=0;i<64;i++){
		for(j=0;j<15;j++){
			registry[i][j]=0;
		}
	}
}

level::~level(){
//	delete[] registry;
}

void level::initTexture(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	textures[0].LoadFromFile("Data/brick.bmp");
	textures[1].LoadFromFile("Data/money.bmp");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void level::drawBrick(int left, int right, int height){
	int i,x,y;
	glColor3f(0.85f, 0.0f, 0.0f);
	for(i=left;i<right;i+=10){
		x=i;
		y= height*30+30;
		glEnable(GL_TEXTURE_2D);
		textures[0].SetActive();
		glBegin( GL_QUADS );
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y-30,0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x+10, y-30,0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x+10, y,0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y,0);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}

void level::isMoney(int pos, int height){
	if(checkRegistry(pos, height) ==  MONEY){
		removeMoney(pos,height);
	}
}

void level::removeMoney(int pos, int height){
	if(pos%10!=0)
		pos-=(pos%10);
	pos/=10;
	if(pos>0 && (registry[pos][height]==MONEY))
		registry[pos][height]=0;
	amount--;
}

void level::removeBrick(int pos, int height){
	if(pos%10!=0)
		pos-=(pos%10);
	pos/=10;
	if((pos>0) && (registry[pos][height]==BRICK) && (registry[pos-1][height]==BRICK)){
		registry[pos][height]=0;
		registry[pos-1][height]=0;
	}
}

void level::loadlevel(){


	registerBrick(0,640,0);


	registerBrick(0,640,14);
	registerBrick(10,90,4);
	registerLadder(1,5,90);
	registerWire(110,550,4);
	registerMoney(400,1);
	registerLadder(1,14,550);
	removeBrick(50,0);
	glEnable(GL_TEXTURE_2D);
	
}

void level::drawLadder(int base, int height, int spot){

	
	glColor3f(0.7f,0.7f,0.0f);
	int i=base*30;
	int realh = height*30;
	glBegin(GL_QUADS);
		glVertex2f(spot, i);
		glVertex2f(spot, realh);
		glVertex2f(spot+2, realh);
		glVertex2f(spot+2, i);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(spot+15, i);
		glVertex2f(spot+15, realh);
		glVertex2f(spot+17, realh);
		glVertex2f(spot+17, i);
	glEnd();

	for(i=base*30-2;i<=realh;i+=10){
		glBegin(GL_QUADS);
			glVertex2f(spot, i);
			glVertex2f(spot+15, i);
			glVertex2f(spot+15, i+2);
			glVertex2f(spot, i+2);
		glEnd();
	}




}

void level::drawWire(int left, int right, int height){

	
	int realh = height*30+27;

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(left, realh);
		glVertex2f(right, realh);
	glEnd();
		


}

void level::drawMoneyBag(int pos, int height){
	glColor3f(0.1f, 0.6f, 0.1f);
	
	int realh = height*30;
	glEnable(GL_TEXTURE_2D);
	textures[1].SetActive();
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(pos, realh);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(pos+10, realh);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(pos+10, realh+30);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(pos, realh+30);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}



// Registering functions into database for loading from file
void level::registerBrick(int left, int right, int height){
	if(right%10!=0)
		right-=(right%10);
	if(left%10!=0)
		left-=(left%10);
	left/=10;
	right/=10;
	int i;
	for(i=left;i<right;i++){
		if(registry[i][height]!=0){
			std::cout << "error in adding bricks" << i << std::endl;
			return;
		}else{
			registry[i][height]=1;
		}
	}
}

void level::registerWire(int left, int right, int height){
	if(right%10!=0)
		right-=(right%10);
	if(left%10!=0)
		left-=(left%10);
	left/=10;
	right/=10;
	int i;
	for(i=left;i<right;i++){
		if(registry[i][height]!=0){
			std::cout << "error in adding wire" << i << std::endl;
			return;
		}else{
			registry[i][height]=WIRE;
		}
	}
}

void level::registerLadder(int base, int height, int spot){
	if(spot%10!=0)
		spot-=(spot%10);
	spot/=10;
	int i;
	for(i=base;i<height;i++){
		if(registry[spot][i]!=0 || registry[spot+1][i]!=0){
			std::cout << "error in adding laddar" << i << std::endl;
			return;
		}else{
			registry[spot][i]=LADDER;
			registry[spot+1][i]=LADDER;
		}
	}
}

void level::registerMoney(int pos, int height){
	if(pos%10!=0)
		pos-=(pos%10);
	pos/=10;
	if(registry[pos][height]!=EMPTY){
		std::cout << "error in adding money" << std::endl;
		return;
	}else{
		registry[pos][height]=MONEY;
	}
	amount++;
}


int level::checkRegistry(int pos, int height){
	if(pos%10!=0)
		pos-=(pos%10);
	pos/=10;
	return registry[pos][height];
}


void level::draw(){
	int i, j;
	glDisable(GL_TEXTURE_2D);
	for(i=0;i<15;i++){
		for(j=0;j<64;j++){
			if(registry[j][i]==BRICK){
				drawBrick(j*10,(j+1)*10,i);
			}else if((registry[j][i]==LADDER) && (registry[j-1][i]!=LADDER)){
				drawLadder(i,i+1,j*10);
			}else if(registry[j][i]==WIRE){
				drawWire(j*10,(j+1)*10,i);
			}else if(registry[j][i]==MONEY){
				drawMoneyBag(j*10, i);
			}
		}
	}
	
}

