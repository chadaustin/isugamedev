#include "badguy.h"
#include <math.h>

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


void badguy::update( float time_delta_in_seconds ){
   
   const float velocity = 40.0f; // 40 pixels per second...
   const float position_change = velocity * time_delta_in_seconds;
   
	if(fabsf(getHeight()-playerHeight) < fabsf(getPos()-playerPos) || usingtarget){
		if(playerPos>getPos()){
			setPosf(getPosf() + position_change);
		}else{
			setPosf(getPosf() - position_change);
		}
	}else{
		usingtarget=true;
		
		if(getPos()!=targetPos){
			if(targetPos<getPos()){
				setPosf(getPosf() + position_change);
			}else{
				setPosf(getPosf() - position_change);
			}
		}else{
			usingtarget=false;
		}
	}
}


void badguy::findLadder(level l){
	for(int i=0;i<640;i+=10){
		if(l.checkRegistry(i, getHeight()/30)==LADDER){
			if(fabsf((i)-getPos())<fabsf(targetPos-getPos())){
				targetPos=i;
			}
		}
	}

}


		


void badguy::findPlayer(player p){
	playerPos = p.getPos();
	playerHeight = p.getHeight();
}
