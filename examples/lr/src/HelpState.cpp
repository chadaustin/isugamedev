#include <iostream>
#include "HelpState.h"
#include "Application.h"
#include "Texture.h"

namespace lr
{
   HelpState::HelpState( Application* a) : State (a)
   {
      mHelpImage = Texture::create(std::string("help.png"));

      transition =  false;
   }

   HelpState::~HelpState()
   {
      delete mHelpImage;
   }

   void HelpState::onKeyPress(SDLKey sym, bool down)
   {
      if(sym == SDLK_RETURN && down)
      {
         transition = true;
      }
   }
   
   void HelpState::update(float dt)
   {
      
   }

   void HelpState::draw()
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
      mHelpImage->drawRectangle(0,0,this->getApp().getWidth(), this->getApp().getHeight());
      
      transition = false;
   }

   int HelpState::switchStates()
   {
      if (transition)
         return 1;
   }
      
} // end namespace
