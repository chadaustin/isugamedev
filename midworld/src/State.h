/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_STATE_H
#define MW_STATE_H


#include <SDL.h>
#include "Types.h"


namespace mw
{

   class State
   {
   public:
      State();
      virtual ~State();

      virtual void update(u64 elapsedTime) = 0;
      virtual void draw() = 0;
      virtual void onKeyPress(SDLKey sym, bool down) = 0;
      virtual void onMousePress(Uint8 button, bool down, int x, int y) = 0;
      virtual void onMouseMove(int x, int y) = 0;

      void invokeTransition(State* state);

      /**
       * Returns the next State object, and makes the state forget about what
       * the next state is.
       */
      State* getNext();

      void quit();
      bool isQuitting();

   private:
      State* mNextState;
      bool mIsQuitting;
   };

}


#endif
