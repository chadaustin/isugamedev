#include <iostream>
#include "IntroState.h"
#include "Application.h"
#include "Texture.h"

namespace lr
{
   IntroState::IntroState( Application* a) : State (a)
   {
      mIntroImage = Texture::create(std::string("intro.png"));
   }

   IntroState::~IntroState()
   {
      delete mIntroImage;
   }

   void IntroState::onKeyPress(SDLKey sym, bool down)
   {
   }
   
   void IntroState::update(float dt)
   {
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


   }

   void IntroState::switchStates()
   {
   }
      
} // end namespace
