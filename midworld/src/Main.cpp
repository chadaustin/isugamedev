/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Johnathan Gurley, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: Main.cpp,v $
 * Date modified: $Date: 2002-06-10 05:33:46 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <SDL/SDL_opengl.h>
#include "Types.h"
#include "Application.h"

void log(const std::string& message)
{
   std::cerr << message << std::endl;
}


// make a std::string-compatible version of SDL_GetError
std::string GetSDLError()
{
   return SDL_GetError();
}


void ThrowSDLError(const std::string& prefix)
{
   throw std::runtime_error((prefix + ": " + GetSDLError()).c_str());
}


void run()
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

   const int width  = 640;
   const int height = 480;

   if (!SDL_SetVideoMode(width, height, info->vfmt->BitsPerPixel, SDL_OPENGL))
   {
      ThrowSDLError("Setting video mode failed");
   }

   SDL_WM_SetCaption("Midworld", 0);
   std::auto_ptr<mw::Application> app(new mw::Application);
      
   // let the app know what size it is
   app->resize(width, height);
      
   Uint32 last_time = SDL_GetTicks();

   while (!app->shouldQuit())
   {      
      SDL_Event event;
      int result = SDL_PollEvent(&event);
      bool should_quit = false;
      while (result == 1)
      {
         switch (event.type)
         {
            case SDL_VIDEORESIZE:
               app->resize(event.resize.w, event.resize.h);
               break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
               app->onKeyPress(event.key.keysym.sym,
                               event.key.state == SDL_PRESSED);
               break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
               app->onMousePress(event.button.button,
                                 event.button.state == SDL_PRESSED,
                                 event.button.x, event.button.y);
               break;

            case SDL_MOUSEMOTION:
               app->onMouseMove(event.motion.x, event.motion.y);
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
      mw::u64 now = (mw::u64)SDL_GetTicks();
      // convert from ms to us for now
      now *= 2;
      
      // ignore wraparound
      if (now >= last_time)
      {
         app->update(now - last_time);
      }
      last_time = now;
         
      app->draw();
      SDL_GL_SwapBuffers();
   }
   
   SDL_Quit();
}


int main()
{
   try
   {
      run();
   }
   catch (const std::exception& e)
   {
      log(std::string("Caught exception: ") + e.what());
   }
   catch (...)
   {
      log("Caught unknown exception!");
   }
}
