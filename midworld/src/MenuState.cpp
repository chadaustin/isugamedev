/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "MenuState.h"
#include "GameState.h"


namespace mw
{

   MenuState::MenuState()
   {
      mImages.resize(5);
      mImages[0] = new Texture("menu_new_game.png");
      mImages[1] = new Texture("menu_load_game.png");
      mImages[2] = new Texture("menu_options.png");
      mImages[3] = new Texture("menu_credits.png");
      mImages[4] = new Texture("menu_exit.png");

      mCurrentItem = 0;
   }

   MenuState::~MenuState()
   {
      for (int i = 0; i < int(mImages.size()); ++i)
      {
         delete mImages[i];
      }
      mImages.clear();
   }

   void
   MenuState::update(u64 elapsedTime)
   {
      
   }

   void
   MenuState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable( GL_DEPTH_TEST );

      glClear(GL_COLOR_BUFFER_BIT);

      /// @todo  we assume 640x480...  :(

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, 640, 480, 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      for (int i = 0; i < 5; ++i) {
         if (i == mCurrentItem) {
            glColor3f(1, 1, 1);
         } else {
            glColor3f(1, 0, 1);
         }
         mImages[i]->drawRectangle(0, i * 100, 640, (i + 1) * 100);
      }
   }

   void
   MenuState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         switch (sym)
         {
            case SDLK_DOWN:
               mCurrentItem = (mCurrentItem + 1) % 5;
               break;
            case SDLK_UP:
               mCurrentItem = (mCurrentItem + 4) % 5;
               break;
            case SDLK_RETURN:
               switch (mCurrentItem)
               {
                  case 0:
                     invokeTransition(new GameState());
                     break;
                  case 4:
                     quit();
                     break;
               }
               break;
         }
      }
   }

   void
   MenuState::onMousePress(Uint8 button, bool down, int x, int y)
   {
   }

   void
   MenuState::onMouseMove(int x, int y)
   {
      mMouseX = x;
      mMouseY = y;
   }

}
