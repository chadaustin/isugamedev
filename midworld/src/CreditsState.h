/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_CREDITS_STATE_H
#define MW_CREDITS_STATE_H

#include <vector>
#include "State.h"
#include "Texture.h"

namespace mw
{
   class CreditsState : public State
   {
   public:
      CreditsState()
      {
         mImages.push_back(new Texture("credits.jpeg"));
      }

      ~CreditsState()
      {
         std::vector<Texture*>::iterator itr;
         for (itr = mImages.begin(); itr != mImages.end(); ++itr)
         {
            delete *itr;
         }
         mImages.clear();
      }

      void update(float dt) {}

      void draw()
      {
         glEnable(GL_TEXTURE_2D);
         glDisable(GL_DEPTH_TEST);
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

         glClear(GL_COLOR_BUFFER_BIT);

         /// @todo  we assume 640x480...  :(

         // set up projection matrix
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         glOrtho(0, 640, 480, 0, -1, 1);

         // set up view matrix
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();

         glColor4f(1, 1, 1, 1);
         mImages[0]->drawRectangle(0,0,640,480);	// draw background
      }

      void onKeyPress(SDLKey sym, bool down)
      {
         if (down)
         {
            invokeTransition(new MenuState());
         }
      }
      void onMousePress(Uint8 button, bool down, int x, int y) {}
      void onMouseMove(int x, int y) {}

   private:
      std::vector<Texture*> mImages;
   };
}

#endif
