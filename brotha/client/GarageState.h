/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
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
 * File:          $RCSfile: GarageState.h,v $
 * Date modified: $Date: 2002-05-03 10:32:07 $
 * Version:       $Revision: 1.13 $
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
#ifndef CLIENT_GARAGE_STATE_H
#define CLIENT_GARAGE_STATE_H

#include <phui/phui.h>
#include "xml/Player.h"
#include "xml/CarType.h"
#include "State.h"
#include "DealerWnd.h"
#include "ChopShopWnd.h"

namespace client {

   class GarageState : public State
                            , phui::ActionListener
                            , phui::WindowAdapter
   {
   public:
      enum SubState {
         Send_Request, ///< need to send data request
         Wait_For_Data, ///< waiting for data
         User_Input, ///< user input
         Join_Game,  ///< join game button pressed
         Wait_Join_Game_Ack ///< wait for ack from server
      };
   public:
      GarageState();
      ~GarageState();

      void draw();
      void update(BrothaApp* app, int elapsedTime);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      virtual void onAction(const phui::ActionEvent& evt);
      virtual void onWindowClosed(const phui::WindowEvent& evt);

   private:
      phui::RootWidget* mRoot;
      phui::Window* mMainWnd;
      phui::Button* mDealerBtn;
      phui::Button* mChopShopBtn;
      phui::Button* mJoinGameBtn;

      /// The mini-dealer window.
      DealerWnd* mDealer;
      ChopShopWnd* mChopShop;

      data::Player* mPlayer;
      data::CarTypeList* mCarTypes;
      data::ModTypeList* mModTypes;

      SubState mSubState;
   };

}


#endif
