/*******************************************************************
 *      Set game - CS352 - Iowa State University
 *      Proffesor: Lynette Kizer
 *      Author: Josh Brow
 *      File: deck.h
 *******************************************************************/

#ifndef DECK
#define DECK

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include "textures.h"
#include "card.h"


/* this is the deck class
 * it is the object that holds all 12 cards on the screen
 */
class deck{
public:
   /* constructor
    * sets all cards to unselected and resets numSelected
    */
   deck(){
      for(int i=0;i<12;i++){
         selectedCards[i]=0;
         numSelected=0;
      }
   };

   /* initialization method
    * pre: none
    * post: initailzes each card in the deck
    */
   void init(){
      int i;
      for(i=0;i<12;i++){
         Cards[i].init();
      }
   }


   /* draw the current deck to the screen
    * pre: card has been initialized
    * post: all cards in deck have been drawn to screnn
    */
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
      glTranslatef(-50,-300,0);
      for(i=0;i<12;i++){
         if(selectedCards[i]==1){
            drawHighlight(i);
         }
      }
   }

   
   /* get the bottom left corner of a card in the deck
    * pre: none
    * post: none
    * args: card is the number of the card we are querying the pos of
    *       x and y are the returned position of the card
    */
   void getCardPos(int const card, int& x, int& y){
      x = cardPos[card].x;
      y = cardPos[card].y;
   }

   // returns the index of the card if we are on a card 
   // else returns -1
   int isACard(int x, int y){
      for(int i=0;i<12;i++){
         if(x>cardPos[i].x && x<(cardPos[i].x+50) && y>cardPos[i].y && y<cardPos[i].y+120){
            return i;
         }
      }
      return -1;
   } 

   
   /* draw a box around the specified card
    * pre: none
    * post: card has been highlighted
    * args: card is the pos of the card we want
    */
   void drawHighlight(int card){
      int tempx, tempy;
      getCardPos(card, tempx, tempy);
      glColor3f(0,.5,0);
      glBegin(GL_LINE_LOOP);
         glVertex3f(tempx-3, tempy-3, 0);
         glVertex3f(tempx-3, tempy+123, 0);
         glVertex3f(tempx+53, tempy+123, 0);
         glVertex3f(tempx+53, tempy-3,0);
      glEnd();
      glutSwapBuffers();
   }
   
   /* query a card in the deck for its' color shape and number
    * pre: none
    * post: color shape and number hold the attrib. of the specified card
    * args: card is the card we want the attr. of
    *       color, shape, and number hold the return values of the method
    */
   void getCardAttribute(int card, int& color, int& shape, int& number){
      color = Cards[card].getColor();
      shape = Cards[card].getShape();
      number = Cards[card].getNumber();
   }      

   /* set a card's color shape and number that is in the deck
    * pre: init has been called
    * post: color shape and number hold the attrib. of the specified card
    * args: card is the card we want the attr. of
    *       color, shape, and number hold the return values of the method
    */
 
   void setCardAttributeRandom(int card){
      Cards[card].setNewAttrib();
   }
   
   /* returns the number of cards currently selected
    */
   int numSel(){
      return numSelected;
   }
  
   /* is true if the specified card is selected
    */
   bool isSelected(int card){
      if(selectedCards[card]==1)
         return true;
      return false;
   }
   
   /* sets the specified card as selected
    */
   void selectCard(int card){
      if(numSelected+1<=3){
         selectedCards[card]=1;
         numSelected++;
      }
   
   }
   
   /* sets the specified card as deselected
    */
   void deselectCard(int card){
      if(numSelected>0){
         selectedCards[card]=0;
         numSelected--;
      }
   }
   
private:
   struct cPos{
      int x, y;
   };
   
   card Cards[12];
   cPos cardPos[12];
   int selectedCards[12];
   int numSelected;
};

#endif
