#include <iostream>
#include <iomanip>
#include <sstream>
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
            mFontRenderer->render("Midworld");
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
         glColor4f(0, 1, 0, 1);
         {
            std::stringstream str;
            str << "Health: " << player.getHealth();
            mFontRenderer->render(str.str().c_str());
         }
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

}
