/*******************************************************************
 *      Set game - CS352 - Iowa State University
 *      Proffesor: Lynette Kizer
 *      Author: Josh Brow
 *      File: card.h
 *******************************************************************/

#ifndef CARD
#define CARD

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include "textures.h"
#include <time.h>


/* defined data types for the attributes of the cards
 * These will be standard for the whole app
 */
#define BLACK  0
#define RED    1
#define BLUE   2
#define GREEN  3

#define SQUARE    0
#define CIRCLE    1
#define TRIANGLE  2
#define SQUIGGLE   3


/* card Class
 * This is a card object.  It holds all data of the card, let's the card
 * draw itself and let's you query for the cards attributes
 */
class card{
public:
   // default constructor
   card(){
      randomize();
   }
   
   /* copy constructor, 
    * pre: none
    * post: a card has been instantiated
    * args: c is the color, s is the shape of the objects, and
    *       n is the number of the objects on the card
    */
   card(int c, int s, int n){
      color=c;
      shape=s;
      number=n;
   }

   /* draw method: draws the card to the screen
    * pre:  an openGl graphics context has been initiallized 
    *       this must get called between draws and have had 
    *       initialize called first
    * post: card has been drawn
    */
   void draw(){
      glColor3f(0,0,0);

      glBegin(GL_LINE_LOOP);
         glVertex3f(0,0,0);
         glVertex3f(50,0,0);
         glVertex3f(50,120,0);
         glVertex3f(0,120,0);
      glEnd();
      for(int k=0;k<number;k++){
         glPushMatrix();
            glTranslatef(0,(4-k)*30,0);
 
            drawPrim();
         glPopMatrix();
      }
   }   
   
   /* initialization method
    * pre: none
    * post: textures for card have been initialized
    */
   void init(){
      if(!initTextures())
         std::cout << "error in texture initialization." << std::endl;
   }

   /* change the cards attributes
    * pre:  none
    * post: card has new attributes
    */
   void setNewAttrib(){
      randomize();
   }

private:

   /* pre: none
    * post: draws the boxes for each card to the screen
    */
   void drawPrim(){
      glPushMatrix();
      glTranslatef(0.0, -30.0, 0.0);
      glEnable(GL_TEXTURE_2D);
      SetTexture();
      glBegin(GL_POLYGON);
         glTexCoord2f(0,0); glVertex3f(5,5,0);
         glTexCoord2f(1,0); glVertex3f(45,5,0);
         glTexCoord2f(1,1); glVertex3f(45,25,0);
         glTexCoord2f(0,1); glVertex3f(5,25,0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();
   }
   
   /* pre: none
    * post: gets a random color shape and number
    */
   void randomize(){
      color = (int)((double)rand()/(double)RAND_MAX * 4);
      shape = (int)((double)rand()/(double)RAND_MAX * 4);
      number = (int)((double)rand()/(double)RAND_MAX * 4+1);
//      std::cout << "c,s,n, rand: " << color << "," << shape << "," << number << "," << rand() << std::endl;
   }
private:

            
   /* pre: init has been called
    * post: textures have been initialized
    */
   bool initTextures(){
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	   textures[0].LoadFromFile("art/black-square.bmp");
	   textures[1].LoadFromFile("art/black-circle.bmp");
      textures[2].LoadFromFile("art/black-triangle.bmp");
      textures[3].LoadFromFile("art/black-squiggle.bmp");
      textures[4].LoadFromFile("art/red-square.bmp");
      textures[5].LoadFromFile("art/red-circle.bmp");
      textures[6].LoadFromFile("art/red-triangle.bmp");
      textures[7].LoadFromFile("art/red-squiggle.bmp");
      textures[8].LoadFromFile("art/blue-square.bmp");
      textures[9].LoadFromFile("art/blue-circle.bmp");
      textures[10].LoadFromFile("art/blue-triangle.bmp");
      textures[11].LoadFromFile("art/blue-squiggle.bmp");
      textures[12].LoadFromFile("art/green-square.bmp");
      textures[13].LoadFromFile("art/green-circle.bmp");
      textures[14].LoadFromFile("art/green-triangle.bmp");
      textures[15].LoadFromFile("art/green-squiggle.bmp");
	   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      return true;
     
   }
   
   /* picks which texture the card should draw
    */
   void SetTexture(){
      if(color==BLACK){
         glColor3f(0,0,0);
         textures[shape].SetActive();
//         std::cout << shape << std::endl;
      }else if(color==RED){
         glColor3f(1,0,0);
         textures[4+shape].SetActive();
//         std::cout << shape << std::endl;

 
      }else if(color==BLUE){
         glColor3f(0,0,1);
         textures[8+shape].SetActive();
//         std::cout << shape << std::endl;

      }else if(color==GREEN){
         glColor3f(0,1,0);
         textures[12+shape].SetActive();
//         std::cout << shape << std::endl;

      }
   }


   // card attributes
   int color;
   int shape;
   int number;

   // allocate storage for textures ids
   COGLTexture textures[16];  

public:

   /* get which color the card has
    */
   int getColor(){
      return color;
   }
   /* get which shape the card has
    */
   int getShape(){
      return shape;
   }
   /* get how many numbers 
    */
   int getNumber(){
      return number;
   }

};


#endif
