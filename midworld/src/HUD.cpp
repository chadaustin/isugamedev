#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <SDL_opengl.h>
#include "HUD.h"


namespace mw
{

   HUD::HUD()
   {
      mFont = 0;
      mFontRenderer = 0;
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (!mFont)
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

   void HUD::draw(
      float width, float height,
      Player& player, float fps,
      const std::vector<std::string>& perf)
   {
      static const gmtl::Vec4f white(1, 1, 1, 1);
      static const gmtl::Vec4f red  (1, 1, 1, 1);
      static const gmtl::Vec4f green(1, 1, 1, 1);
      static const gmtl::Vec4f blue (1, 1, 1, 1);
   
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      if (!player.weapon().isNull())
      {
         glPushMatrix();
         glTranslatef(550, 768 - mFont->getAscent() - mFont->getDescent(), 0);
         glColor4f(1,0,0,1);
         {
            std::stringstream str;
            str << player.weapon().getAmmoInClip();
            mFontRenderer->render(str.str().c_str());
         }
         glTranslatef(40, 0, 0);
         {
            std::stringstream str;
            str << player.weapon().getAmmoInBag();
            mFontRenderer->render(str.str().c_str());
         }
         glPopMatrix();

         glPushMatrix();
         glTranslatef(20, 768 - mFont->getAscent() - mFont->getDescent(), 0);
         glColor4f(1,0,0,1);
         mFontRenderer->render(player.weapon().getName().c_str());
         glPopMatrix();
      }
      
      // player health
      glPushMatrix();
      glTranslatef(20, 20, 0);
      drawTape(300, 20, 100, player.getHealth(), true);
      glPopMatrix();

      // FPS
      glPushMatrix();
      glTranslatef(924, 20.0f+mFont->getAscent(), 0);
      glColor4f(1,1,1,1);
      {
         std::stringstream str;
         str << std::setprecision(4) << fps;
         mFontRenderer->render(str.str().c_str());
      }
      glPopMatrix();
      
      glColor4f(1, 1, 1, 1);
      for (int i = 0; i < perf.size(); ++i)
      {
         glPushMatrix();
         glTranslatef(800, 100.0f + mFont->getAscent() + i * 20, 0);
         mFontRenderer->render(perf[i].c_str());
         glPopMatrix();
      }

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
    }
    void HUD::drawTape(float width, float height, float maxValue, float currentValue, bool horizontal)
    {
        glColor4f(0,0,1,1);     
        glBegin(GL_LINE_LOOP);
            glVertex3f(0,0,0);
            glVertex3f(width,0,0);
            glVertex3f(width,height,0);
            glVertex3f(0,height,0);
        glEnd();

        float fillwidth = width;
        float fillheight = height;
        if(horizontal)
        {
            fillwidth = width*(currentValue/maxValue);
        }
        else
        {
            fillheight = height*(currentValue/maxValue);
        }
            
        if(currentValue > maxValue*.50)
            glColor4f(0,1,0,1);
        else if(currentValue > maxValue*.25)
            glColor4f(1,1,0,1);
        else
            glColor4f(1,0,0,1);

        glBegin(GL_QUADS);
            glVertex3f(1,fillheight-1,0);
            glVertex3f(fillwidth-1,fillheight-1,0);
            glVertex3f(fillwidth-1,1,0);
            glVertex3f(1,1,0);
        glEnd();
        
    }
}

