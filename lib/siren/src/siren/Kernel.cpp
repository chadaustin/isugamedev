/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Kernel.cpp,v $
 * Date modified: $Date: 2003-02-03 05:37:01 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <stdexcept>
#include <SDL.h>
#include "Kernel.h"
#include "Types.h"
#include "State.h"
#include "StateFactory.h"
#include "Version.h"

namespace siren
{
   /**
    * A std::string-compatible version of SDL_GetError.
    */
   std::string
   GetSDLError()
   {
      return SDL_GetError();
   }

   /**
    * Throws an exception containing the current SDL error with the given prefix
    * to the exception string.
    *
    * @throws std::runtime_error
    */
   void
   ThrowSDLError(const std::string& prefix)
   {
      throw std::runtime_error((prefix + ": " + GetSDLError()).c_str());
   }

   //--------------------------------------------------------------------------
   // Kernel
   //--------------------------------------------------------------------------

   Kernel::Kernel()
      : mWidth(1024)
      , mHeight(768)
   {}

   Kernel::~Kernel()
   {}

   void
   Kernel::start(StatePtr state)
   {
      // Setup the inital state
      mState = state;

      controlLoop();
   }

   void
   Kernel::transitionTo(const std::string& name)
   {
      mNextState = StateFactory::getInstance().create(name);
   }

   int
   Kernel::getWidth() const
   {
      return mWidth;
   }

   int
   Kernel::getHeight() const
   {
      return mHeight;
   }

   void
   Kernel::controlLoop()
   {
      // initialize SDL
      int init_flags = SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER;
      if (SDL_Init(init_flags) < 0)
      {
         ThrowSDLError("SDL Initialization failed");
      }

      const SDL_VideoInfo* info = SDL_GetVideoInfo();
      if (!info)
      {
         ThrowSDLError("Retrieving video information failed");
      }
      // define our minimum requirements for the GL window
      SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     5);
      SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   5);
      SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    5);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   16);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

      if (!SDL_SetVideoMode(mWidth, mHeight, info->vfmt->BitsPerPixel, SDL_OPENGL))
      {
         ThrowSDLError("Setting video mode failed");
      }

      std::string title = std::string("Siren v") + version;
      SDL_WM_SetCaption(title.c_str(), 0);
      // init the mouse state...
      SDL_WarpMouse(mWidth / 2, mHeight / 2);
      SDL_ShowCursor(SDL_DISABLE);

      // let the app know what size it is
      resize(mWidth, mHeight);
      u64 last_time = SDL_GetTicks();
      while (!shouldQuit())
      {
         SDL_Event event;
         int result = SDL_PollEvent(&event);
         bool should_quit = false;
         while (result == 1)
         {
            switch (event.type)
            {
               case SDL_VIDEORESIZE:
                  resize(event.resize.w, event.resize.h);
                  break;

               case SDL_KEYDOWN:
               case SDL_KEYUP:
                  mState->onKeyPress(event.key.keysym.sym,
                                     event.key.state == SDL_PRESSED);
                  break;

               case SDL_MOUSEBUTTONDOWN:
               case SDL_MOUSEBUTTONUP:
                  mState->onMousePress(event.button.button,
                                       event.button.state == SDL_PRESSED,
                                       event.button.x, event.button.y);
                  break;

               case SDL_MOUSEMOTION:
                  mState->onMouseMove(event.motion.x, event.motion.y);
                  break;

               case SDL_QUIT:
                  should_quit = true;
                  break;
            }

            result = SDL_PollEvent(&event);
         }

         // error or SDL_QUIT message
         if (result < 0 || should_quit)
         {
            break;
         }

         // update and draw application
         /// @todo Use a high-res timer to actually get in us rather than ms
         u64 now = (u64)SDL_GetTicks();

         // ignore wraparound
         if (now >= last_time)
         {
            float dt = (float)(now - last_time) / 1000.0f;
            update(dt);
            draw();
            SDL_GL_SwapBuffers();
         }
         last_time = now;
      }

      SDL_Quit();
      SDL_ShowCursor(SDL_ENABLE);
   }

   void
   Kernel::update(float dt)
   {
      // Check if we need to transition to the next state
      if (mNextState)
      {
         mState = mNextState;
      }

      if (mState)
      {
         // Let the current state do its update
         mState->update(dt);

         // Store the transition to the next state
         mNextState = mState->getNext();
      }
   }

   void
   Kernel::draw() const
   {
      if (mState)
      {
         mState->draw();
      }
   }

   StatePtr
   Kernel::getState() const
   {
      return mState;
   }

   void
   Kernel::resize(int width, int height)
   {
      mWidth  = width;
      mHeight = height;
   }

   void
   Kernel::onKeyPress(SDLKey sym, bool down)
   {
      mState->onKeyPress(sym, down);
   }

   void
   Kernel::onMousePress(Uint8 button, bool down, int x, int y)
   {
      mState->onMousePress(button, down, x, y);
   }

   void
   Kernel::onMouseMove(int x, int y)
   {
      mState->onMouseMove(x, y);
   }

   bool
   Kernel::shouldQuit()
   {
      if (mState)
      {
         return mState->isQuitting();
      }
      return false;
   }
}
