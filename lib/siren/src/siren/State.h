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
 * File:          $RCSfile: State.h,v $
 * Date modified: $Date: 2003-02-11 05:01:41 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_STATE_H
#define SIREN_STATE_H

#include <boost/shared_ptr.hpp>
#include <string>
#include <SDL.h>

namespace siren
{
   /**
    * This abstract base class describes a state in the application. This is
    * essentially a subset of the application logic.
    */
   class State
   {
   public:
      /// Creates a new state that will be run in the kernel.
      State();

      /// Destroys (and exits) this state.
      virtual ~State();

      /**
       * Updates this state based on the amount of time that has passed since
       * the last frame.
       *
       * @param dt   the differential in time for this frame in seconds
       */
      virtual void update(float dt) = 0;

      /// Renders this state to the screen.
      virtual void draw() const = 0;

      /**
       * Notifies this state that a key has been pressed or released.
       *
       * @param sym              the ID of the key that was pressed
       * @param down             true if the key is down, false if it is up
       */
      virtual void onKeyPress(SDLKey sym, bool down);

      /**
       * Notifies this state that a mouse button has been pressed or released at
       * the given location relative to the upper left corner of the window.
       *
       * @param button           the ID of the button that was pressed
       * @param down             true if the button is down, false if it is up
       * @param x                the x coordinate of the event
       * @param y                the y coordinate of the event
       */
      virtual void onMousePress(Uint8 button, bool down, int x, int y);

      /**
       * Notifies this state that the mouse has moved to the given location
       * relative to the upper left corner of the window.
       *
       * @param x             the new x coordinate
       * @param y             the new y coordinate
       */
      virtual void onMouseMove(int x, int y);

      /**
       * Notifies this state that the screen size has been changed to the given
       * resolution.
       *
       * @param width         the new width of the window
       * @param height        the new height of the window
       */
      virtual void resize(int width, int height);

      /**
       * Invokes a transition to the state of the given name. The transition
       * will occur at the beginning of the next frame.
       *
       * @param name    the name of the state to transition to
       */
      void invokeTransition(const std::string& name);

      /**
       * Returns the next State object, and makes the state forget about what
       * the next state is.
       */
      boost::shared_ptr<State> getNext();

      /// Gets the width of the window this state is running in.
      int getWidth() const;

      /// Gets the height of the window this state is running in.
      int getHeight() const;

      /**
       * Tells this state that it should quit the application. The next pass
       * through the update loop, the application will exit.
       */
      void quit();

      /// Tests if this state is requesting that the application exits.
      bool isQuitting() const;

   private:
      /// The next state. Used for transitions.
      boost::shared_ptr<State> mNextState;

      /// True if this state is requesting that the application exits.
      bool mIsQuitting;

      /// The width of the window this state is running in.
      int mWidth;

      /// The height of the window this state is running in.
      int mHeight;
   };

   typedef boost::shared_ptr<State> StatePtr;
}

#endif
