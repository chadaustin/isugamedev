/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_INTRO_STATE_H
#define MW_INTRO_STATE_H


#include "State.h"
#include "Texture.h"


namespace mw
{

   class IntroState : public State
   {
   public:
      IntroState();
      ~IntroState();

      void update(u64 elapsedTime);
      void draw();
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

   private:
      Texture* mIntroImage;

      bool mShouldTransition;
   };

}


#endif
