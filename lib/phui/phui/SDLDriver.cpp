/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * File:          $RCSfile: SDLDriver.cpp,v $
 * Date modified: $Date: 2005-01-25 17:28:51 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <phui/SDLDriver.h>
#include <phui/Debug.h>
#include <phui/DriverManager.h>
#include <SDL/SDLInclude.h>
#include <iostream>
#include <cstdlib>

namespace phui
{
   // Register ourselves with the driver manager.
   // We do this by creating a dummy class that registers ourself with
   // the DriverManager in its constructor in an anonymous namespace.
   namespace
   {
      // This is the creator function that the driver manager will use to
      // create SDLDrivers.
      Driver* create(bool standalone)
      {
         return new SDLDriver(standalone);
      }
      
      class SDLDriverRegistrator
      {
      public:

         SDLDriverRegistrator()
         {
            DriverManager::Instance().registerDriver( "SDL", &create );
         }
      };
      
      static SDLDriverRegistrator register_sdl_driver;
   }
   
   SDLDriver::SDLDriver(bool standalone)
      : mStandalone(standalone)
   {
      if (mStandalone)
      {
         // Setup SDL
         int result(0);
         result = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | 
                           SDL_INIT_NOPARACHUTE | SDL_INIT_EVENTTHREAD);
         if (-1 == result)
         {
            phuiDEBUG(phuiDBG_ERROR) 
               << "[SDLDriver] Unable to initialize SDL." << std::endl;
            exit(1);
         }
         atexit(SDL_Quit);
      }
   }

   SDLDriver::~SDLDriver()
   {

   }

   void
   SDLDriver::registerRoot(RootWidgetPtr root)
   {
      if (mStandalone)
      {
         // Create a display through SDL.
         SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
         const Size s = root->getSize();
         SDL_Surface* screen = SDL_SetVideoMode(s.getWidth(), s.getHeight(), 0,
                                                SDL_HWSURFACE | SDL_HWPALETTE |
                                                SDL_OPENGL);
         if (!screen)
         {
            phuiDEBUG(phuiDBG_ERROR)
               << "[SDLDriver] Unable to create a display surface."
               << std::endl;
            exit(2);
         }
         glClearColor(0.0, 0.0, 0.0, 0.0);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT |
                 GL_STENCIL_BUFFER_BIT);
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         gluOrtho2D(0, s.getWidth(), s.getHeight(), 0);

         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
      }
      mRootWidget = root;
   }

   void
   SDLDriver::onKeyDown(InputKey key)
   {
      mRootWidget->onKeyDown(key);
   }

   void
   SDLDriver::onKeyUp(InputKey key)
   {
      mRootWidget->onKeyUp(key);
   }

   void
   SDLDriver::onMouseDown(InputButton button, const Point& p)
   {
      mRootWidget->onMouseDown(button, p);
   }

   void
   SDLDriver::onMouseUp(InputButton button, const Point& p)
   {
      mRootWidget->onMouseUp(button, p);
   }

   void
   SDLDriver::onMouseMove(const Point& p)
   {
      mRootWidget->onMouseMove(p);
   }

   void
   SDLDriver::start()
   {
      // Start is only meaningful in standalone mode.
      if (!mStandalone)
      {
         phuiDEBUG(phuiDBG_DEBUG)
            << "[SDLDriver] start() called, but the driver is in module "
            << "mode." << std::endl;
         return;
      }
      
      bool quit(false);
      while (!quit)
      {
         SDL_Event event;
         InputButton button;
         InputKey key;
         Point point;
         while(SDL_PollEvent(&event))
         {
            switch(event.type)
            {
               case SDL_QUIT:
                  quit = true;
                  break;
               case SDL_MOUSEBUTTONDOWN:
                  sdlMouseButtonToPhui(event.button, button, point);
                  onMouseDown(button, point);
                  break;
               case SDL_MOUSEBUTTONUP:
                  sdlMouseButtonToPhui(event.button, button, point);
                  onMouseUp(button, point);
                  break;
               case SDL_MOUSEMOTION:
                  sdlMouseMotionToPhui(event.motion, point);
                  onMouseMove(point);
                  break;
               case SDL_KEYDOWN:
                  sdlKeyToPhui(event.key, key);
                  onKeyDown(key);
                  break;
               case SDL_KEYUP:
                  sdlKeyToPhui(event.key, key);
                  onKeyUp(key);
                  break;
               default:
                  break;
            }
         }
         mRootWidget->draw();
         SDL_GL_SwapBuffers();
      }
   }

   void
   SDLDriver::update()
   {
      if (mStandalone)
      {
         phuiDEBUG(phuiDBG_DEBUG)
            << "[SDLDriver] update() called, but the driver is in"
            << " standalone mode." << std::endl;
         return;
      }
      SDL_Event* events(0);
      int event_cnt = SDL_PeepEvents(events, 10, SDL_GETEVENT, 
                                     SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP |
                                     SDL_MOUSEMOTION | SDL_KEYDOWN | SDL_KEYUP);
      if (-1 == event_cnt)
      {
         phuiDEBUG(phuiDBG_ERROR)
            << "[SDLDriver] Error retrieving events off of the SDL Event queue."
            << std::endl;
         return;
      }
      if (event_cnt > 0)
      {
         InputButton button;
         Point point;
         InputKey key;
         for (int i = 0; i < event_cnt; ++i)
         {
            switch(events[i].type)
            {
               case SDL_MOUSEBUTTONDOWN:
                  sdlMouseButtonToPhui(events[i].button, button, point);
                  onMouseDown(button, point);
                  break;
               case SDL_MOUSEBUTTONUP:
                  sdlMouseButtonToPhui(events[i].button, button, point);
                  onMouseUp(button, point);
                  break;
               case SDL_MOUSEMOTION:
                  sdlMouseMotionToPhui(events[i].motion, point);
                  onMouseMove(point);
                  break;
               case SDL_KEYDOWN:
                  sdlKeyToPhui(events[i].key, key);
                  onKeyDown(key);
                  break;
               case SDL_KEYUP:
                  sdlKeyToPhui(events[i].key, key);
                  onKeyUp(key);
                  break;
               default:
                  phuiDEBUG(phuiDBG_ERROR)
                     << "[SDLDriver] Unknown SDL Event." << std::endl;
                  break;
            }
         }
      }
   }

   void
   SDLDriver::sdlMouseMotionToPhui(const SDL_MouseMotionEvent& event,
                                   Point& point)
   {
      point.x = event.x;
      point.y = event.y;
   }

   void
   SDLDriver::sdlMouseButtonToPhui(const SDL_MouseButtonEvent& event,
                                   InputButton& button,
                                   Point& point)
   {
      switch(event.button)
      {
         case SDL_BUTTON_LEFT:
            button = BUTTON_LEFT;
            break;
         case SDL_BUTTON_RIGHT:
            button = BUTTON_RIGHT;
            break;
         case SDL_BUTTON_MIDDLE:
            button = BUTTON_MIDDLE;
            break;
         case SDL_BUTTON_WHEELUP:
            button = BUTTON_WHEEL_UP;
            break;
         case SDL_BUTTON_WHEELDOWN:
            button = BUTTON_WHEEL_DOWN;
            break;
         default:
            button = BUTTON_UNKNOWN;
            break;
      }
      point.x = event.x;
      point.y = event.y;
   }

   void
   SDLDriver::sdlKeyToPhui(const SDL_KeyboardEvent& event,
                           InputKey& key)
   {
      switch(event.keysym.sym)
      {
         case SDLK_BACKSPACE:
            key = KEY_BACKSPACE;
            break;
         case SDLK_TAB:
            key = KEY_TAB;
            break;
         case SDLK_RETURN:
            key = KEY_ENTER;
            break;
         case SDLK_PAUSE:
            key = KEY_PAUSE;
            break;
         case SDLK_ESCAPE:
            key = KEY_ESCAPE;
            break;
         case SDLK_SPACE:
            key = KEY_SPACE;
            break;
         case SDLK_QUOTE:
            key = KEY_APOSTROPHE;
            break;
         case SDLK_COMMA:
            key = KEY_COMMA;
            break;
         case SDLK_MINUS:
            key = KEY_MINUS;
            break;
         case SDLK_PERIOD:
            key = KEY_PERIOD;
            break;
         case SDLK_SLASH:
            key = KEY_SLASH;
            break;
         case SDLK_0:
            key = KEY_0;
            break;
         case SDLK_1:
            key = KEY_1;
            break;
         case SDLK_2:
            key = KEY_2;
            break;
         case SDLK_3:
            key = KEY_3;
            break;
         case SDLK_4:
            key = KEY_4;
            break;
         case SDLK_5:
            key = KEY_5;
            break;
         case SDLK_6:
            key = KEY_6;
            break;
         case SDLK_7:
            key = KEY_7;
            break;
         case SDLK_8:
            key = KEY_8;
            break;
         case SDLK_9:
            key = KEY_9;
            break;
         case SDLK_SEMICOLON:
            key = KEY_SEMICOLON;
            break;
         case SDLK_EQUALS:
            key = KEY_EQUALS;
            break;
         case SDLK_LEFTBRACKET:
            key = KEY_OPENBRACE;
            break;
         case SDLK_BACKSLASH:
            key = KEY_BACKSLASH;
            break;
         case SDLK_RIGHTBRACKET:
            key = KEY_CLOSEBRACE;
            break;
         case SDLK_BACKQUOTE:
            key = KEY_TILDE;
            break;
         case SDLK_a:
            key = KEY_A;
            break;
         case SDLK_b:
            key = KEY_B;
            break;
         case SDLK_c:
            key = KEY_C;
            break;
         case SDLK_d:
            key = KEY_D;
            break;
         case SDLK_e:
            key = KEY_E;
            break;
         case SDLK_f:
            key = KEY_F;
            break;
         case SDLK_g:
            key = KEY_G;
            break;
         case SDLK_h:
            key = KEY_H;
            break;
         case SDLK_i:
            key = KEY_I;
            break;
         case SDLK_j:
            key = KEY_J;
            break;
         case SDLK_k:
            key = KEY_K;
            break;
         case SDLK_l:
            key = KEY_L;
            break;
         case SDLK_m:
            key = KEY_M;
            break;
         case SDLK_n:
            key = KEY_N;
            break;
         case SDLK_o:
            key = KEY_O;
            break;
         case SDLK_p:
            key = KEY_P;
            break;
         case SDLK_q:
            key = KEY_Q;
            break;
         case SDLK_r:
            key = KEY_R;
            break;
         case SDLK_s:
            key = KEY_S;
            break;
         case SDLK_t:
            key = KEY_T;
            break;
         case SDLK_u:
            key = KEY_U;
            break;
         case SDLK_v:
            key = KEY_V;
            break;
         case SDLK_x:
            key = KEY_X;
            break;
         case SDLK_y:
            key = KEY_Y;
            break;
         case SDLK_z:
            key = KEY_Z;
            break;
         case SDLK_DELETE:
            key = KEY_DELETE;
            break;
         case SDLK_KP0:
            key = KEY_KEYPAD_0;
            break;
         case SDLK_KP1:
            key = KEY_KEYPAD_1;
            break;
         case SDLK_KP2:
            key = KEY_KEYPAD_2;
            break;
         case SDLK_KP3:
            key = KEY_KEYPAD_3;
            break;
         case SDLK_KP4:
            key = KEY_KEYPAD_4;
            break;
         case SDLK_KP5:
            key = KEY_KEYPAD_5;
            break;
         case SDLK_KP6:
            key = KEY_KEYPAD_6;
            break;
         case SDLK_KP7:
            key = KEY_KEYPAD_7;
            break;
         case SDLK_KP8:
            key = KEY_KEYPAD_8;
            break;
         case SDLK_KP9:
            key = KEY_KEYPAD_9;
            break;
         case SDLK_KP_PERIOD:
            key = KEY_KEYPAD_PERIOD;
            break;
         case SDLK_KP_DIVIDE:
            key = KEY_KEYPAD_DIVIDE;
            break;
         case SDLK_KP_MULTIPLY:
            key = KEY_KEYPAD_MULTIPLY;
            break;
         case SDLK_KP_MINUS:
            key = KEY_KEYPAD_MINUS;
            break;
         case SDLK_KP_PLUS:
            key = KEY_KEYPAD_PLUS;
            break;
         case SDLK_KP_ENTER:
            key = KEY_KEYPAD_ENTER;
            break;
         case SDLK_KP_EQUALS:
            key = KEY_KEYPAD_EQUALS;
            break;
         case SDLK_UP:
            key = KEY_UP;
            break;
         case SDLK_DOWN:
            key = KEY_DOWN;
            break;
         case SDLK_RIGHT:
            key = KEY_RIGHT;
            break;
         case SDLK_LEFT:
            key = KEY_LEFT;
            break;
         case SDLK_INSERT:
            key = KEY_INSERT;
            break;
         case SDLK_HOME:
            key = KEY_HOME;
            break;
         case SDLK_END:
            key = KEY_END;
            break;
         case SDLK_PAGEUP:
            key = KEY_PAGE_UP;
            break;
         case SDLK_PAGEDOWN:
            key = KEY_PAGE_DOWN;
            break;
         case SDLK_F1:
            key = KEY_F1;
            break;
         case SDLK_F2:
            key = KEY_F2;
            break;
         case SDLK_F3:
            key = KEY_F3;
            break;
         case SDLK_F4:
            key = KEY_F4;
            break;
         case SDLK_F5:
            key = KEY_F5;
            break;
         case SDLK_F6:
            key = KEY_F6;
            break;
         case SDLK_F7:
            key = KEY_F7;
            break;
         case SDLK_F8:
            key = KEY_F8;
            break;
         case SDLK_F9:
            key = KEY_F9;
            break;
         case SDLK_F10:
            key = KEY_F10;
            break;
         case SDLK_F11:
            key = KEY_F11;
            break;
         case SDLK_F12:
            key = KEY_F12;
            break;
         case SDLK_F13:
            key = KEY_F13;
            break;
         case SDLK_F14:
            key = KEY_F14;
            break;
         case SDLK_F15:
            key = KEY_F15;
            break;
         case SDLK_RSHIFT:
            key = KEY_SHIFT;
            break;
         case SDLK_LSHIFT:
            key = KEY_SHIFT;
            break;
         case SDLK_RCTRL:
            key = KEY_CTRL;
            break;
         case SDLK_LCTRL:
            key = KEY_CTRL;
            break;
         case SDLK_RALT:
            key = KEY_ALT;
            break;
         case SDLK_LALT:
            key = KEY_ALT;
            break;
         case SDLK_LSUPER:
            key = KEY_WINDOWS;
            break;
         case SDLK_RSUPER:
            key = KEY_WINDOWS;
            break;
         case SDLK_PRINT:
            key = KEY_PRINTSCREEN;
            break;
         default:
            key = KEY_UNKNOWN;
            break;
      }
   }
}
