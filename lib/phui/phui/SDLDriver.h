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
 * File:          $RCSfile: SDLDriver.h,v $
 * Date modified: $Date: 2005-01-25 17:28:51 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_SDL_DRIVER_H
#define PHUI_SDL_DRIVER_H

#include <phui/Driver.h>
#include <SDL/SDLInclude.h>
#include <string>

namespace phui
{
   class SDLDriver : public Driver
   {
   public:
      
      /**
       * Default Constructor
       * Sets up the SDL subsystems if running
       * in standalone mode.
       *
       * @param   standalone     true if we are running in standalone mode,
       *                         false otherwise.
       */
      SDLDriver(bool standalone = true);

      /**
       * Destructor
       * Cleans up everything phui related.
       */
      virtual ~SDLDriver();

      virtual std::string getDriverName()
      {
         return "SDL Driver";
      }

      virtual std::string getDriverVersion()
      {
         return "0.0.1";
      }

      virtual void registerRoot(RootWidgetPtr root);

      virtual void onKeyDown(InputKey key);

      virtual void onKeyUp(InputKey key);

      virtual void onMouseDown(InputButton button, const Point& p);

      virtual void onMouseUp(InputButton button, const Point& p);

      virtual void onMouseMove(const Point& p);

      virtual void start();

      /**
       * Updates phui by retrieving events from the event queue.
       * This driver will only pull events off of the queue that it is
       * interested in (keyboard/mouse); all other events will be left
       * on the event queue.
       */
      virtual void update();

      virtual bool isStandalone()
      {
         return mStandalone;
      }
 
   private:

      /// Are we running in standalone or module mode?
      bool                 mStandalone;
      
      /// The root widget.
      WidgetPtr            mRootWidget;

      /**
       * Converts an SDL_MOUSEMOTION event into a phui::Point.
       *
       * @param   event    the mouse motion event to convert.
       * @param   point    the point that will contain the mouse motion event.
       */
      void sdlMouseMotionToPhui(const SDL_MouseMotionEvent& event,
                                Point& point);

      /**
       * Converts an SDL_MOUSEBUTTON event into a phui::InputButton and
       * phui::Point.
       *
       * @param   event    the mouse button event to convert.
       * @param   button   the phui::Button.
       * @param   point    the phui::Point.
       */
      void sdlMouseButtonToPhui(const SDL_MouseButtonEvent& event,
                                InputButton& button,
                                Point& point);

      /**
       * Converts and SDL_KEY event into a phui::InputKey.
       *
       * @param   event    the key event to convert.
       * @param   key      the phui::InputKey to contain the result.
       */
      void sdlKeyToPhui(const SDL_KeyboardEvent& event,
                        InputKey& key);
   };
}

#endif
