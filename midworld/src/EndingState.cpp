#include <algorithm>
#include <memory>
#include <iostream>
#include "EndingState.h"
#include "GameManager.h"
#include "Application.h"
#include "StateFactory.h"

namespace mw
{
   namespace
   {
      StateCreatorImpl<EndingState> creator("Ending");
   }

   EndingState::EndingState( Application* a )
      : State( a )
      , mElapsedTime(0)
      , mLeavingState(false)
   {
      mImage = new Texture("images/ending.jpeg");
      // Start playing the theme song.
      Jukebox* jukebox = GameManager::instance().getSoundManager()->getJukebox();
      jukebox->clear();
      jukebox->addTrack("music/theme.ogg");
      jukebox->play();
   }

   EndingState::~EndingState()
   {
      delete mImage;
   }

   void
   EndingState::update(float dt)
   {
      mElapsedTime += dt;

      if (mLeavingState && mElapsedTime > 1)
      {
         invokeTransition("Menu");
      }
      ::SDL_WarpMouse(application().getWidth() / 2, application().getHeight() / 2);
   }

   void
   EndingState::draw()
   {
      /// @todo  think about GL states

      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);

      glClear(GL_COLOR_BUFFER_BIT);

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, 1, 1, 0);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
            
      float fade = (mLeavingState ?
                    1 - mElapsedTime :
                    std::min(mElapsedTime, 1.0f));
      glColor3f(fade, fade, fade);
      mImage->drawRectangle(0, 0, 1, 1);
   }

   void
   EndingState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         startTransition();
      }
   }

   void
   EndingState::onMousePress(Uint8 button, bool down, int x, int y)
   {
      if (down)
      {
         startTransition();
      }
   }

   void
   EndingState::startTransition()
   {
      if (!mLeavingState)
      {
         mLeavingState = true;
         mElapsedTime = std::max(0.0f, 1.0f - mElapsedTime);
      }
   }

}
