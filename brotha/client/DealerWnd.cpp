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
 * File:          $RCSfile: DealerWnd.cpp,v $
 * Date modified: $Date: 2002-05-03 07:33:52 $
 * Version:       $Revision: 1.4 $
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
#include "DealerWnd.h"
#include "BrothaApp.h"

namespace client {
   DealerWnd::DealerWnd()
      : phui::Window("Mini-Dealer")
   {
      setSize(540, 380);
      setBackgroundColor(phui::Colorf(0.3f, 0.8f, 0.2f, 0.8f));

      phui::Label* mDealerTitle = new phui::Label("Mini-Dealer");
      mDealerTitle->setSize(100, 20);
      mDealerTitle->setPosition(10, 10);
      mDealerTitle->setForegroundColor(phui::RED);
      add(mDealerTitle);

      mCarsList = new phui::ListBox();
      mCarsList->setSize(250, 280);
      mCarsList->setPosition(10, 30);
      mCarsList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mCarsList->setForegroundColor(phui::WHITE);
      add(mCarsList);

      mCarsOwnedList = new phui::ListBox();
      mCarsOwnedList->setSize(250, 280);
      mCarsOwnedList->setPosition(280, 30);
      mCarsOwnedList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mCarsOwnedList->setForegroundColor(phui::WHITE);
      add(mCarsOwnedList);

      mBuyBtn = new phui::Button("Buy");
      mBuyBtn->setSize(75, 20);
      mBuyBtn->setPosition(185, 320);
      mBuyBtn->setBackgroundColor(phui::BLACK);
      mBuyBtn->setForegroundColor(phui::WHITE);
      mBuyBtn->addActionListener(this);
      add(mBuyBtn);

      mSellBtn = new phui::Button("Sell");
      mSellBtn->setSize(75, 20);
      mSellBtn->setPosition(455, 320);
      mSellBtn->setBackgroundColor(phui::BLACK);
      mSellBtn->setForegroundColor(phui::WHITE);
      mSellBtn->addActionListener(this);
      add(mSellBtn);

      mDoneBtn = new phui::Button("Done");
      mDoneBtn->setSize(75, 20);
      mDoneBtn->setPosition(455, 350);
      mDoneBtn->setBackgroundColor(phui::BLACK);
      mDoneBtn->setForegroundColor(phui::WHITE);
      mDoneBtn->addActionListener(this);
      add(mDoneBtn);

      mSubState = User_Input;
   }

   DealerWnd::~DealerWnd()
   {}

   void DealerWnd::onAction(const phui::ActionEvent& evt) {
      phui::Widget* src = evt.getSource();
      if (src == mDoneBtn) {
         hide();
      } else if (src == mBuyBtn) {
         mSubState = Send_Buy_Request;
      } else if (src == mSellBtn) {
         mSubState = Send_Sell_Request;
      }
   }

   void DealerWnd::updateData(data::CarList* playerList, data::CarTypeList* allCars) {
      mCarsList->clear();
      for(unsigned int x=0;x<allCars->size();++x) {
         bool addIt = true;
         for(unsigned int y=0;y<playerList->size();++y) {
            if((*playerList)[y]->getName().compare((*allCars)[x]->getName()) == 0) {
               addIt = false;
            }
         }

         if(addIt) {
            mCarsList->add((*allCars)[x]->getName());
         }
      }

      mCarsOwnedList->clear();
      for(unsigned int x=0;x<playerList->size();++x) {
         mCarsOwnedList->add((*playerList)[x]->getName());
      }
   }

   void DealerWnd::update(BrothaApp* app, int elapsedTime) {
      if(mSubState == Send_Buy_Request) {
         int selectedItem = mCarsList->getSelectedIndex();

         // if an item is selected
         if(selectedItem != -1) {
            // disable the window till further notice
            this->setEnabled(false);

            // request to buy it
            app->sendMessage(new net::BuyCarMessage(mCarsList->get(selectedItem)));
            mSubState = Wait_For_Buy_Response;
         } else {
            // go back to waiting
            mSubState = User_Input;
         }
      } else if(mSubState == Send_Sell_Request) {
         int selectedItem = mCarsOwnedList->getSelectedIndex();

         // if an item is selected
         if(selectedItem != -1) {
            // disable the window till further notice
            this->setEnabled(false);

            // request to sell it
            app->sendMessage(new net::SellCarMessage(mCarsOwnedList->get(selectedItem)));
            mSubState = Wait_For_Sell_Response;
         } else {
            // go back to waiting
            mSubState = User_Input;
         }
      } else if(mSubState == Wait_For_Buy_Response) {
         int selectedItem = mCarsList->getSelectedIndex();

         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::OK) {
               net::OKMessage* okMsg = (net::OKMessage*)msg;

               if(okMsg->getCode() == net::OKMessage::OKAY) {
                  // if the purchase was successful

                  // add it to the list of owned cars
                  mCarsOwnedList->add(mCarsList->get(selectedItem));
                  // remove it from the list we can buy from
                  mCarsList->remove(selectedItem);
               } else {
                  // if the purchace wasn't successful
                  /// @todo tell user: we need a MessageBox type phui thing
               }
            } else {
               std::cout<<"ERROR: Got the wrong message type"<<std::endl;
               /// @todo raise an error
            }
            // enable input again
            this->setEnabled(true);

            // go back to waiting
            mSubState = User_Input;
         }
      } else if(mSubState == Wait_For_Sell_Response) {
         int selectedItem = mCarsOwnedList->getSelectedIndex();

         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::OK) {
               net::OKMessage* okMsg = (net::OKMessage*)msg;

               if(okMsg->getCode() == net::OKMessage::OKAY) {
                  // if the purchase was successful

                  // add it to the list we can buy from
                  mCarsList->add(mCarsOwnedList->get(selectedItem));
                  // remove it from the list of owned cars
                  mCarsOwnedList->remove(selectedItem);
               } else {
                  // if the purchace wasn't successful
                  /// @todo tell user: we need a MessageBox type phui thing
               }
            } else {
               std::cout<<"ERROR: Got the wrong message type"<<std::endl;
               /// @todo raise an error
            }
            // enable input again
            this->setEnabled(true);

            // go back to waiting
            mSubState = User_Input;
         }
      } else {
         // do nothing :)
      }
   }
}
