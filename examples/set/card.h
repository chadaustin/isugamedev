#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include "textures.h"
#include <gl\gl.h>
#include <gl\glut.h>
#include <gl\glu.h>


#define BLACK  0
#define RED    1
#define BLUE   2
#define GREEN  3

#define SQUARE    0
#define CIRCLE    1
#define TRIANGLE  2
#define SQUIGGLE   3

class card{
public:
   // default constructor
   card(){
      randomize();
   }
   
   // 
   card(int c, int s, int n){
      color=c;
      shape=s;
      number=n;
   }

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
   
   // this is for setting up the textures
   void init(){
      if(!initTextures())
         std::cout << "error in texture initialization." << std::endl;
   }

   

private:
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

   void randomize(){
      color = (int)((double)rand()/(double)RAND_MAX * 4+1);
      shape = (int)((double)rand()/(double)RAND_MAX * 4+1);
      number = (int)((double)rand()/(double)RAND_MAX * 4+1);
      std::cout << "c,s,n, rand: " << color << "," << shape << "," << number << "," << rand() << std::endl;
   }
   

            

   bool initTextures(){
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	   textures[0].LoadFromFile("C:/gamedev/set/art/black-square.bmp");
	   textures[1].LoadFromFile("C:/gamedev/set/art/black-circle.bmp");
      textures[2].LoadFromFile("C:/gamedev/set/art/black-triangle.bmp");
      textures[3].LoadFromFile("C:/gamedev/set/art/black-squiggle.bmp");
      textures[4].LoadFromFile("C:/gamedev/set/art/red-square.bmp");
      textures[5].LoadFromFile("C:/gamedev/set/art/red-circle.bmp");
      textures[6].LoadFromFile("C:/gamedev/set/art/red-triangle.bmp");
      textures[7].LoadFromFile("C:/gamedev/set/art/red-squiggle.bmp");
      textures[8].LoadFromFile("C:/gamedev/set/art/blue-square.bmp");
      textures[9].LoadFromFile("C:/gamedev/set/art/blue-circle.bmp");
      textures[10].LoadFromFile("C:/gamedev/set/art/blue-triangle.bmp");
      textures[11].LoadFromFile("C:/gamedev/set/art/blue-squiggle.bmp");
      textures[12].LoadFromFile("C:/gamedev/set/art/green-square.bmp");
      textures[13].LoadFromFile("C:/gamedev/set/art/green-circle.bmp");
      textures[14].LoadFromFile("C:/gamedev/set/art/green-triangle.bmp");
      textures[15].LoadFromFile("C:/gamedev/set/art/green-squiggle.bmp");
	   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      return true;

   }

   void SetTexture(){
      if(color==BLACK){
         glColor3f(0,0,0);
         textures[shape].SetActive();
         std::cout << shape << std::endl;
      }else if(color==RED){
         glColor3f(1,0,0);
         textures[4+shape].SetActive();
         std::cout << shape << std::endl;

 
      }else if(color==BLUE){
         glColor3f(0,0,1);
         textures[8+shape].SetActive();
         std::cout << shape << std::endl;

      }else if(color==GREEN){
         glColor3f(0,1,0);
         textures[12+shape].SetActive();
         std::cout << shape << std::endl;

      }
   }


   // card attributes
   int color;
   int shape;
   int number;

   // allocate storage for textures ids
   COGLTexture textures[16];  

  
   

};
