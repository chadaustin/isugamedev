#ifndef DECK
#define DECK

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include "textures.h"
#include "card.h"


class deck{
public:
   // constructor
   deck(){};

   void init(){
      int i;
      for(i=0;i<12;i++){
         Cards[i].init();
      }
   }


   // draw the current deck to the screen
   void draw(){
      int count=0, i, j, xpos=0, ypos=0;
      glLoadIdentity();									// Reset The View
   	glTranslatef(50, 300, 0);
      xpos +=50; ypos +=300;
	   for(i=0;i<4;i++){
	      for(j=0;j<3;j++){
	         glPushMatrix();
	         glTranslatef(i*100+95, ((3-j)*130)-390,0);
            xpos+=(i*100+95); ypos+=(((3-j)*130)-390);
            Cards[count++].draw();
            cardPos[count-1].x = xpos;
            cardPos[count-1].y = ypos;
	         glPopMatrix();
            xpos=50;ypos=300;
	      }
	   }
	   count=0;
   }

   void test(){
      for(int i=0;i<12;i++){
         std::cout << "card " << i << " :" << cardPos[i].x << ":" << cardPos[i].y << std::endl;
      }
   }
   
   void getCardPos(int const card, int& x, int& y){
      x = cardPos[card].x;
      y = cardPos[card].y;
   }

   // returns the index of the card if we are on a card 
   // else returns -1
   int isACard(int x, int y){
      
   }  

   void getCardAttribute(int card){
   }      
   
private:
   struct cPos{
      int x, y;
   };
   
   card Cards[12];
   cPos cardPos[12];
};

#endif
