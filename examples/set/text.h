/*******************************************************************
 *      Set game - CS352 - Iowa State University
 *      Proffesor: Lynette Kizer
 *      Author: Josh Brow
 *      File: text.h
 *******************************************************************/

#ifndef TEX
#define TEX

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <string>

#include <GL/glut.h>

//Draws text string in specified screen position
void glPrintf(const char* output, int x=0, int y=0, void* font=GLUT_BITMAP_HELVETICA_10)
{

   int size = strlen(output) ;
   glColor3f(0.0, 0.0, 0.0) ;
   
   glRasterPos3f(x, y, 0) ;
   for (int i=0; i < size; i++)
   {
      glutBitmapCharacter( font, output[i]) ;
   }
  
}



#endif
