#include <iostream>
#include "IntroState.h"
#include "Application.h"
#include "Texture.h"

namespace lr
{
   IntroState::IntroState( Application* a) : State (a)
   {
      mIntroImage = Texture::create(std::string("intro.png"));
      guy1 = Texture::create(std::string("lr-climb1.png"));
      guy2 = Texture::create(std::string("lr-climb2.png"));
      select = Texture::create(std::string("menu_selection.png"));

      currentTexture = guy1;
      initTime = offset = 0;
      keyup = keydown = transition =  false;
   }

   IntroState::~IntroState()
   {
      delete mIntroImage;
      delete guy1;
      delete guy2;
      delete select;
   }

   void IntroState::onKeyPress(SDLKey sym, bool down)
   {
      if(sym == SDLK_DOWN && down)
      {
         keydown = true;
         
      }else if(sym == SDLK_UP && down)
      {
         keyup = true;
      }else if(sym == SDLK_DOWN && !down)
      {
         keydown = false;
      }else if(sym == SDLK_UP && !down)
      {
         keyup = false;
      }else if(sym == SDLK_RETURN && down)
      {
         transition = true;
      }
   }
   
   void IntroState::update(float dt)
   {
      if((initTime+=dt)>.08 && (keyup || keydown))
      {
         if(currentTexture == guy1){
            currentTexture = guy2;
         }else{
            currentTexture = guy1;
         }
         initTime=0;
      }
      if(keydown && offset<50)
         offset++;
      if(keyup && offset>0)
         offset--;
   }

   void IntroState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_CULL_FACE);

      glClear(GL_COLOR_BUFFER_BIT);

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, this->getApp().getWidth(), this->getApp().getHeight(), 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      // draw background
      glColor4f(1, 1, 1, 1);
      mIntroImage->drawRectangle(0,0,this->getApp().getWidth(), this->getApp().getHeight());
      
      glTranslatef(295,400+offset,0);
      currentTexture->drawRectangle(0,0,16,32);
      glTranslatef(-295,-(400+offset),0);
      if(offset==0)
      {
         select->drawRectangle(325,380,550,440);
      }
      if(offset==50)
      {
         select->drawRectangle(325,440,550,490);
      }
   }

   bool IntroState::switchStates()
   {
      if (transition)
         return true;
      else
         return false;
   }
      
} // end namespace
