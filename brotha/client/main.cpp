/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: main.cpp,v $
 * Date modified: $Date: 2002-04-24 05:59:04 $
 * Version:       $Revision: 1.12 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
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
 ************************************************************ brotha-cpr-end */
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <SDL/SDL_opengl.h>
#include "client/BrothaApp.h"

void log(const std::string& message) {
   std::cerr << message << std::endl;
}

// make a std::string-compatible version of SDL_GetError
std::string GetSDLError() {
   return SDL_GetError();
}

int BrothaMain(int argc, char *argv[]) {

   // initialize SDL
   int init_flags = SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO |
                    SDL_INIT_TIMER | SDL_INIT_JOYSTICK;
   if (SDL_Init(init_flags) < 0) {
      log("SDL Initialization failed: " + GetSDLError());
      return EXIT_FAILURE;
   }
   
   const SDL_VideoInfo* info = SDL_GetVideoInfo();
   if (!info) {
      log("Retrieving video information failed: " + GetSDLError());
      return EXIT_FAILURE;
   }
   
   // define our minimum requirements for the GL window
   SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     5);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   5);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    5);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   16);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   
   const int width  = 640;
   const int height = 480;
   
   if (!SDL_SetVideoMode(width, height, info->vfmt->BitsPerPixel, SDL_OPENGL)) {
      log("Setting video mode failed: " + GetSDLError());
      return EXIT_FAILURE;
   }
   
   SDL_WM_SetCaption("Warn-a-Brotha", 0);
   
   try {
      std::auto_ptr<client::BrothaApp> app(new client::BrothaApp());
      
      // let the app know what size it is
      app->resize(width, height);
      
      Uint32 last_time = SDL_GetTicks();
      
      while (1) {
      
         SDL_Event event;
         int result = SDL_PollEvent(&event);
         bool should_quit = false;
         while (result == 1) {
            
            switch (event.type) {
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
         if (result < 0 || should_quit) {
            break;
         }
         
         // update and draw application
         
         Uint32 now = SDL_GetTicks();
         // ignore wraparound
         if (now >= last_time) {
            app->update(now - last_time);
         }
         last_time = now;
         
         app->draw();
         SDL_GL_SwapBuffers();
      }
   }
   catch (const std::exception& e) {
      log(std::string("uncaught exception: ") + e.what());
   }
   
   SDL_Quit();
   
   return 0;
}


#ifdef WIN32

// this is actually SDL_main in Windows
int main(int argc, char** argv) {
   return BrothaMain(argc, argv);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
   return BrothaMain(__argc, __argv);
}
#endif
