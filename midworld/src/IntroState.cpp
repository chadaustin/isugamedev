/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "IntroState.h"
#include "GameManager.h"
#include "MenuState.h"

namespace mw
{

   IntroState::IntroState()
   {
      mIntroImage = new Texture("intro.jpeg");
      mShouldTransition = false;

      // Start playing the theme song.
      /// @todo Stop. Clear all tracks. Then play the new track.
      Jukebox* jukebox = GameManager::instance().getSoundManager()->getJukebox();
      jukebox->addTrack("music/theme.ogg");
      jukebox->play();
   }

   IntroState::~IntroState()
   {
      delete mIntroImage;
   }

   void
   IntroState::update(float dt)
   {
   }

   void
   IntroState::draw()
   {
      /// @todo  think about GL states

      glEnable(GL_TEXTURE_2D);
      glDisable( GL_DEPTH_TEST );

      glClear(GL_COLOR_BUFFER_BIT);

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, 1, 1, 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      
      glColor3f( 1,1,1 );
      mIntroImage->drawRectangle(0, 0, 1, 1);
   }

   void
   IntroState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         invokeTransition(new MenuState());
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
