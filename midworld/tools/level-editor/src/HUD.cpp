#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "HUD.h"



   HUD::HUD()
   {
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (!mFont)
      {
         throw std::runtime_error("Could not create gltext font: fonts/arial.ttf");
      }
      
      mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
      if (!mFontRenderer)
      {
         throw std::runtime_error("Could not create gltext renderer");
      }
      mFontRenderer->setFont(mFont.get());
   }

   HUD::~HUD()
   {}

   void HUD::draw(float x, float y, float width, float height)
   {
   
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

         glPushMatrix();
         glTranslatef(0, 40 - mFont->getAscent() - mFont->getDescent(), 0);
            glColor4f(1,0,0,1);
            std::stringstream str;
            str << "World Coordinates: " <<  x << " : " << y;
            mFontRenderer->render(str.str().c_str());
         
         glPopMatrix();


   }
