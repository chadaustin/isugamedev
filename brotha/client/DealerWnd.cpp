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
 * Date modified: $Date: 2002-05-01 22:57:36 $
 * Version:       $Revision: 1.2 $
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
      add(mBuyBtn);

      mSellBtn = new phui::Button("Sell");
      mSellBtn->setSize(75, 20);
      mSellBtn->setPosition(455, 320);
      mSellBtn->setBackgroundColor(phui::BLACK);
      mSellBtn->setForegroundColor(phui::WHITE);
      add(mSellBtn);

      mDoneBtn = new phui::Button("Done");
      mDoneBtn->setSize(75, 20);
      mDoneBtn->setPosition(455, 350);
      mDoneBtn->setBackgroundColor(phui::BLACK);
      mDoneBtn->setForegroundColor(phui::WHITE);
      mDoneBtn->addActionListener(this);
      add(mDoneBtn);
   }

   DealerWnd::~DealerWnd()
   {}

   void DealerWnd::onAction(const phui::ActionEvent& evt) {
      phui::Widget* src = evt.getSource();
      if (src == mDoneBtn) {
         hide();
      }
   }

   void DealerWnd::onListSelection(const phui::ListSelectionEvent& evt) {
      phui::Widget* src = evt.getSource();
      if (src == mCarsList) {
         std::cout<<"Selected "<<mCarsList->get(evt.getSelectedIndex())<<std::endl;
      }
   }
}
