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
 * File:          $RCSfile: ChopShopWnd.h,v $
 * Date modified: $Date: 2002-05-03 10:32:07 $
 * Version:       $Revision: 1.3 $
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
#ifndef CLIENT_CHOP_SHOP_WND_H
#define CLIENT_CHOP_SHOP_WND_H

#include <phui/phui.h>
#include "xml/Player.h"
#include "xml/CarType.h"
#include "xml/ModType.h"

namespace client {

   class BrothaApp;

   /**
    * Specialized window for the ChopShop.
    */
   class ChopShopWnd : public phui::Window
                            , phui::ActionListener
                            , phui::ListSelectionListener
   {
   public:
      enum SubState {
         Send_Buy_Request, ///< need to send a buy request
         Wait_For_Buy_Response, ///< waiting for ack for the buy request
         Send_Sell_Request, ///< need to send a sell request
         Wait_For_Sell_Response,  ///< waiting for ack for the sell request
         User_Input ///< user input
      };
   public:
      ChopShopWnd();
      ~ChopShopWnd();

      void onAction(const phui::ActionEvent& evt);
      void onListSelection(const phui::ListSelectionEvent& evt);
      void updateData(data::Player* player, data::CarTypeList* allCars, data::ModTypeList* allMods);
      void update(BrothaApp* app, int elapsedTime);
      void updateLists(phui::ListBox* changed = NULL);

   private:
      phui::ListBox* mModLevels;
      phui::ListBox* mModsList;
      phui::ListBox* mModsOwnedList;
      phui::ListBox* mCarsOwnedList;
      phui::Button* mBuyBtn;
      phui::Button* mSellBtn;
      phui::Button* mDoneBtn;

      data::Player* mPlayer;
      data::CarTypeList* mCarTypes;
      data::ModTypeList* mModTypes;

      SubState mSubState;
   };

}

#endif
