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
 * File:          $RCSfile: InputAction.h,v $
 * Date modified: $Date: 2003-02-28 04:10:22 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_INPUT_ACTION_H
#define SIREN_INPUT_ACTION_H

#include <siren/Export.h>

namespace siren
{
   /**
    * An InputAction represents a particular action that the user can provide to
    * the application. In combination with the InputManager, this class provides
    * an insulating layer between the application and the physical devices. The
    * application can work with named actions rather than specific keypresses
    * directly. This class also provides edge state management.
    *
    * @see InputManager
    */
   class SIREN_CLASS InputAction
   {
   public:
      /**
       * Creates a new action that in initialized to off.
       */
      InputAction();

      /**
       * Called by the input manager whenever this application has been
       * activated, "pressed."
       *
       * @param down       true if the action is down; false if up
       */
      void onPress(bool down);

      /**
       * Called by the input manager every update cycle so that the edge state
       * can be accurately maintained.
       *
       * @param dt         time passed since the last update in seconds
       */
      void update(float dt);

      /**
       * Returns true if the relevent key(s) are pressed.
       */
      bool isActive();

      /**
       * Returns the derivative of the "signal".  1 if on a rising edge, -1 if
       * a falling edge, or 0 if steady.
       */
      int getEdgeState();

   private:
      int mPressCount;
      int mLastPressCount;
      int mEdgeState;
   };
}

#endif
