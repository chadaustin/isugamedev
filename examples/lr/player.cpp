#include "player.h"
#include "textures.h"

void player::initTexture(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	textures[0].LoadFromFile("Data/lr1.bmp");
	textures[1].LoadFromFile("Data/lr2.bmp");
	textures[2].LoadFromFile("Data/lr-climb1.bmp");
	textures[3].LoadFromFile("Data/lr-climb2.bmp");
	textures[4].LoadFromFile("Data/lr-hang1.bmp");
	textures[5].LoadFromFile("Data/lr-hang2.bmp");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void player::draw(){
    int realh = (int)height;
	int gameh = (int)((height+29.0f)/30.0f);
	int p = (int)(pos/10.0f);
	
//	glColor3f(1.0f, 0.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
	textures[getTexState()].SetActive();

	glBegin(GL_POLYGON);
		glTexCoord2f(0,0); glVertex2f(pos, realh);
		glTexCoord2f(1,0); glVertex2f(pos+10, realh);
		glTexCoord2f(1,1); glVertex2f(pos+10, realh+30);
		glTexCoord2f(0,1); glVertex2f(pos, realh+30);
	glEnd();
		


}

player::player(){
	height = 1;
	pos = 0;
	state = 0;
	falling = false;
	texState = 0;
}

