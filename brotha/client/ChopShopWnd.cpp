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
 * File:          $RCSfile: ChopShopWnd.cpp,v $
 * Date modified: $Date: 2002-04-28 22:16:46 $
 * Version:       $Revision: 1.1 $
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
#include "ChopShopWnd.h"

namespace client {
   ChopShopWnd::ChopShopWnd()
      : phui::Window("Chop Shop")
   {
      setSize(540, 380);
      setBackgroundColor(phui::Colorf(0.8f, 0.3f, 0.2f, 0.8f));

      phui::Label* mChopShopTitle = new phui::Label("Chop Shop");
      mChopShopTitle->setSize(100, 20);
      mChopShopTitle->setPosition(10, 10);
      mChopShopTitle->setForegroundColor(phui::BLUE);
      add(mChopShopTitle);

      mModsList = new phui::ListBox();
      mModsList->setSize(250, 280);
      mModsList->setPosition(10, 30);
      mModsList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mModsList->setForegroundColor(phui::WHITE);
      add(mModsList);

      mModsOwnedList = new phui::ListBox();
      mModsOwnedList->setSize(250, 280);
      mModsOwnedList->setPosition(280, 30);
      mModsOwnedList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mModsOwnedList->setForegroundColor(phui::WHITE);
      add(mModsOwnedList);

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

   ChopShopWnd::~ChopShopWnd()
   {}

   void ChopShopWnd::onAction(const phui::ActionEvent& evt)
   {
      phui::Widget* src = evt.getSource();
      if (src == mDoneBtn) {
         hide();
      }
   }

   void ChopShopWnd::onListSelection(const phui::ListSelectionEvent& evt)
   {
      phui::Widget* src = evt.getSource();
      if (src == mModsList) {
         std::cout<<"Selected "<<mModsList->get(evt.getSelectedIndex())<<std::endl;
      }
   }
}
