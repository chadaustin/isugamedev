/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "IntroState.h"
#include "GameState.h"

namespace mw
{

   IntroState::IntroState()
   {
      mIntroImage = new Texture("intro.jpeg");
      mShouldTransition = false;
   }

   IntroState::~IntroState()
   {
      delete mIntroImage;
   }

   void
   IntroState::update(u64 elapsedTime)
   {
   }

   void
   IntroState::draw()
   {
      glEnable(GL_TEXTURE_2D);

      glClear(GL_COLOR_BUFFER_BIT);

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, 1, 1, 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      mIntroImage->drawRectangle(0, 0, 1, 1);
   }

   void
   IntroState::onKeyPress(SDLKey sym, bool down)
   {
      switch (sym)
      {
      case SDLK_ESCAPE: if (down) quit(); break;
      default:
         if (down) this->invokeTransition( new GameState ); 
         break;
      }
   }

   void
   IntroState::onMousePress(Uint8 button, bool down, int x, int y)
   {
   }

   void
   IntroState::onMouseMove(int x, int y)
   {
   }


}
