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
 * File:          $RCSfile: GarageState.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:03 $
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

#include <phui/SDLBridge.h>
#include "BrothaApp.h"
#include "GarageState.h"
#include <map>

namespace client {
   const float PI = 3.141579f;
   
   GarageState::GarageState() {
      std::cout<<"Entered Garage state"<<std::endl;

      mRoot = phui::CreateRoot(640,480);

      const int border_w = 50;
      const int border_h = 50;

      // main window
      phui::Window* mMainWnd = new phui::Window();
      mMainWnd->setSize(200, 140);
      mMainWnd->setPosition(640/2 - 100,
                            480/2 - 70);
      mMainWnd->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mMainWnd->show();

      mDealerBtn = new phui::Button("Dealer");
      mDealerBtn->setPosition(20, 20);
      mDealerBtn->setSize(160, 20);
      mDealerBtn->addActionListener(this);
      mMainWnd->add(mDealerBtn);

      mChopShopBtn = new phui::Button("Chop Shop");
      mChopShopBtn->setPosition(20, 60);
      mChopShopBtn->setSize(160, 20);
      mChopShopBtn->addActionListener(this);
      mMainWnd->add(mChopShopBtn);

      mJoinGameBtn = new phui::Button("Join Game");
      mJoinGameBtn->setPosition(20, 100);
      mJoinGameBtn->setSize(160, 20);
      mJoinGameBtn->addActionListener(this);
      mMainWnd->add(mJoinGameBtn);

      // dealer window
      mDealerWnd = new phui::Window();
      mDealerWnd->setSize(640 - border_w*2, 480 - border_h*2);
      mDealerWnd->setPosition(border_w, border_h);
      mDealerWnd->setBackgroundColor(phui::Colorf(0.8f, 0.3f, 0.2f, 0.8f));

      phui::Label* mDealerTitle = new phui::Label("Mini-Dealer");
      mDealerTitle->setSize(200, 20);
      mDealerTitle->setPosition(10, 10);
      mDealerTitle->setForegroundColor(phui::RED);
      mDealerWnd->add(mDealerTitle);

      mCarsList = new phui::ListBox();
      mCarsList->setSize((640 - border_w*2 - 40)/2, 480 - border_h*2 - 70);
      mCarsList->setPosition(10, 30);
      mCarsList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mCarsList->setForegroundColor(phui::WHITE);
      mDealerWnd->add(mCarsList);
      mCarsList->add("Road Hummer");

      mCarsOwnedList = new phui::ListBox();
      mCarsOwnedList->setSize((640 - border_w*2 - 40)/2, 480 - border_h*2 - 70);
      mCarsOwnedList->setPosition(20 + (640 - border_w*2 - 40)/2, 30);
      mCarsOwnedList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mCarsOwnedList->setForegroundColor(phui::WHITE);
      mDealerWnd->add(mCarsOwnedList);

      mBuyBtn = new phui::Button("Buy");
      mBuyBtn->setSize(75, 20);
      mBuyBtn->setPosition(10 + (640 - border_w*2 - 40)/2 - 75, 480 - border_h*2 - 30);
      mBuyBtn->setBackgroundColor(phui::BLACK);
      mBuyBtn->setForegroundColor(phui::WHITE);
      mDealerWnd->add(mBuyBtn);

      mSellBtn = new phui::Button("Sell");
      mSellBtn->setSize(75, 20);
      mSellBtn->setPosition(20 + (640 - border_w*2 - 40)/2 + (640 - border_w*2 - 40)/2 - 75, 480 - border_h*2 - 30);
      mSellBtn->setBackgroundColor(phui::BLACK);
      mSellBtn->setForegroundColor(phui::WHITE);
      mDealerWnd->add(mSellBtn);

      // chop shop window
      mChopShopWnd = new phui::Window();
      mChopShopWnd->setSize(640 - border_w*2, 480 - border_h*2);
      mChopShopWnd->setPosition(border_w, border_h);
      mDealerWnd->setBackgroundColor(phui::Colorf(0.3f, 0.8f, 0.2f, 0.8f));

      // start with the main window
      mRoot->add(mDealerWnd);
      mRoot->add(mChopShopWnd);
      mRoot->add(mMainWnd);
   }

   GarageState::~GarageState() {
      std::cout<<"Left Garage state"<<std::endl;
   }

   void
   GarageState::draw() {
      glClear(GL_COLOR_BUFFER_BIT);
      mRoot->draw();
   }

   void
   GarageState::update(BrothaApp* app, int elapsedTime) {
   }

   void
   GarageState::onKeyPress(SDLKey sym, bool down) {
      if (down) {
         mRoot->onKeyDown(phui::SDLToPhuiKey(sym));
      } else {
         mRoot->onKeyUp(phui::SDLToPhuiKey(sym));
      }
   }

   void
   GarageState::onMousePress(Uint8 button, bool down, int x, int y) {
      phui::Point p(x, y);
      if (down) {
         mRoot->onMouseDown(phui::SDLToPhuiButton(button), p);
      } else {
         mRoot->onMouseUp(phui::SDLToPhuiButton(button), p);
      }
   }

   void
   GarageState::onMouseMove(int x, int y) {
      mRoot->onMouseMove(phui::Point(x, y));
   }

   void
   GarageState::onAction(const phui::ActionEvent& evt) {
      phui::Widget* src = evt.getSource();
      if (src == mDealerBtn) {
         mDealerWnd->show();
         mRoot->focus(mDealerWnd);
      }
      else if (src == mChopShopBtn) {
         mChopShopWnd->show();
         mRoot->focus(mChopShopWnd);
      }
   }

   void
   GarageState::onListSelection(const phui::ListSelectionEvent& evt) {
      phui::Widget* src = evt.getSource();
      if (src == mCarsList) {
         std::cout<<"Selected "<<mCarsList->get(evt.getSelectedIndex())<<std::endl;
      }
   }
}
