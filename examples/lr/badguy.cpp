#include "badguy.h"

void badguy::initTexture(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	textures[0].LoadFromFile("Data/lr-badguy1.bmp");
	textures[1].LoadFromFile("Data/lr-badguy2.bmp");
	textures[2].LoadFromFile("Data/lr-badguy1.bmp");
	textures[3].LoadFromFile("Data/lr-badguy2.bmp");
	textures[4].LoadFromFile("Data/lr-badguy1.bmp");
	textures[5].LoadFromFile("Data/lr-badguy2.bmp");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	usingtarget=false;
}


void badguy::update(){
	if(abs(getHeight()-playerHeight) < abs(getPos()-playerPos) || usingtarget){
		if(playerPos>getPos()){
			setPos(getPos()+5);
		}else{
			setPos(getPos()-5);
		}
	}else{
		usingtarget=true;
		
		if(getPos()!=targetPos){
			if(targetPos<getPos()){
				setPos(getPos()+5);
			}else{
				setPos(getPos()-5);
			}
		}else{
			usingtarget=false;
		}
	}
}


void badguy::findLadder(level l){
	for(int i=0;i<640;i+=10){
		if(l.checkRegistry(i, getHeight()/30)==LADDER){
			if(abs((i)-getPos())<abs(targetPos-getPos())){
				targetPos=i;
			}
		}
	}

}


		


void badguy::findPlayer(player p){
	playerPos = p.getPos();
	playerHeight = p.getHeight();
}