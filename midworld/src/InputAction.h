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
 * Date modified: $Date: 2002-11-26 11:23:04 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_INPUT_ACTION_H
#define MW_INPUT_ACTION_H


namespace mw
{
   class InputAction
   {
   public:
      InputAction();
      
      void onPress(bool down);
      
      /// Called once per frame.
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
