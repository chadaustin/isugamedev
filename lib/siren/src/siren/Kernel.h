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
 * File:          $RCSfile: Kernel.h,v $
 * Date modified: $Date: 2003-02-03 02:54:35 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_KERNEL_H
#define SIREN_KERNEL_H

#include <boost/shared_ptr.hpp>
#include <SDL.h>

namespace siren
{
   class State;
   typedef boost::shared_ptr<State> StatePtr;

   /**
    * The kernel drives the application. It manages the current game state.
    */
   class Kernel
   {
   private:
      Kernel();

      /// Not implemented on purpose. Usage will cause a compile-time error.
      Kernel(const Kernel& kernel);

   public:
      ~Kernel();

   public:
      static Kernel& getInstance();

      /**
       * Updates this kernel based on the amount of time that has passed since
       * the last frame.
       *
       * @param dt   the differential in time for this frame in seconds
       */
      void update(float dt);

      /**
       * Renders the application in its current state.
       */
      void draw() const;

      /**
       * Gets the current state in this kernel.
       *
       * @return  the current state or NULL if there is no current state
       */
      StatePtr getState() const;

      /**
       * Sets the next state to switch to. The transition will occur at the
       * beginning of the next update
       *
       * @param state      the name of the state to switch to
       *
       * @throws std::runtime_error    if there is no state with the given name
       */
      void transitionTo(const std::string& name);

      void resize(int width, int height);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      bool shouldQuit();

      int getWidth() const;
      int getHeight() const;

   private:
      int mWidth;
      int mHeight;

      /// The current state that the kernel is driving.
      StatePtr mState;

      /// The state to switch to the next time the app is updated.
      StatePtr mNextState;

      static Kernel* mInstance;
   };
}

#endif
