/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * Date modified: $Date: 2002-10-26 05:35:11 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_INPUT_ACTION_H
#define MW_INPUT_ACTION_H

namespace mw
{
   /**
    * States of the action
    */
   enum EdgeState
   {
      DOWN, UP, EDGE_DOWN, EDGE_UP
   };
 
   /**
    * An action representing something that is input from the user.
    */
   class InputAction
   {
   public:
      /**
       * The UID data type.
       */
      typedef unsigned long UID;

      /**
       * Creates a new InputAction.
       */
      InputAction();

      /**
       * Destroys this InputAction, releasing the UID it had reserved.
       */
      ~InputAction();
      
      /**
       * Gets the unique ID for this action
       */
      const UID& getUID() const;

      /**
       * Gets the present state of this action
       * @return the state of this action
       */
      EdgeState getState() const;

      /**
       * Sets the state of this action
       * @param state the new state
       */
      void setState(EdgeState state);

      /**
       * Compares the unique ID of the objects.
       *
       * @param action the action to compare to.
       * 
       * @return true if equal, false if not
       */
      bool operator==(const InputAction& action);

   private:
      /// The unique ID for this action
      UID mUID;

      ///The present state of this action
      EdgeState mState;
   };

}

#endif
