/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef APPLICATION_H
#define APPLICATION_H


#include <SDL/SDL.h>
#include "Types.h"


namespace mw {

   class Application {
   public:
      Application();
      ~Application();

      /// elapsedTime is in milliseconds
      void update(u64 elapsedTime);

      void draw();
      void resize(int width, int height);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

   private:
      int mWidth;
      int mHeight;
   };

}


#endif
