#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <SDL_opengl.h>
#include "HUD.h"


namespace mw
{

   HUD::HUD()
   {
      mFont = 0;
      mFontRenderer = 0;
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (mFont)
      {
         std::cout<<"Font font"<<std::endl;
         mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
         if (mFontRenderer)
         {
            std::cout<<"Created renderer"<<std::endl;
            mFontRenderer->setFont(mFont);
         }
      }
   }

   HUD::~HUD()
   {
      delete mFont;
      delete mFontRenderer;
   }

   void HUD::draw(float width, float height, Player& player, float fps)
   {
      // Draw the HUD
      if (mFontRenderer)
      {
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         gluOrtho2D(0, width, height, 0);

         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         glLoadIdentity();

         glPushMatrix();
            glTranslatef(20, 20.0f+mFont->getAscent(), 0);
            glColor4f(1,0,0,0.8f);
            mFontRenderer->render("Levi Rules");
         glPopMatrix();

         if (!player.weapon().isNull())
         {
            glPushMatrix();
            glTranslatef(550, 480.0f - mFont->getAscent() - mFont->getDescent(), 0);
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
            glTranslatef(20, 480.0f - mFont->getAscent() - mFont->getDescent(), 0);
            glColor4f(1,0,0,1);
            mFontRenderer->render(player.weapon().getName().c_str());
            glPopMatrix();
         }
         
         // player health
         glPushMatrix();
         glTranslatef(300, 20 + mFont->getAscent(), 0);

         /*glColor4f(0, 1, 0, 1);
         {
            std::stringstream str;
            str << "Health: " << player.getHealth();
            mFontRenderer->render(str.str().c_str());
         }*/

         drawTape(100, 20, 100, player.getHealth(), true);
         glPopMatrix();

         // FPS
         glPushMatrix();
         glTranslatef(550, 20.0f+mFont->getAscent(), 0);
         glColor4f(1,1,1,1);
         {
            std::stringstream str;
            str << std::setprecision(4) << fps;
            mFontRenderer->render(str.str().c_str());
         }
         glPopMatrix();

         glPopMatrix();
         glPopMatrix();
      }
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

