#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "HUD.h"



   HUD::HUD()
   {
      mFont = 0;
      mFontRenderer = 0;
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (mFont==0)
      {
         throw std::runtime_error("Could not create gltext font: fonts/arial.ttf");
      }
      
      mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
      if (!mFontRenderer)
      {
         delete mFont;
         mFont = 0;
         throw std::runtime_error("Could not create gltext renderer");
      }
      mFontRenderer->setFont(mFont);
   }

   HUD::~HUD()
   {
      delete mFont;
      delete mFontRenderer;
   }

   void HUD::draw(float x, float y)
   {
   
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0, 640, 640, 0);

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
