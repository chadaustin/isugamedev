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
#include "ChopShopWnd.h"
#include "BrothaApp.h"

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
      mModsList->setSize(250, 135);
      mModsList->setPosition(10, 30);
      mModsList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mModsList->setForegroundColor(phui::WHITE);
      mModsList->addListSelectionListener(this);
      add(mModsList);

      mModLevels = new phui::ListBox();
      mModLevels->setSize(250, 135);
      mModLevels->setPosition(10, 170);
      mModLevels->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mModLevels->setForegroundColor(phui::WHITE);
      mModLevels->addListSelectionListener(this);
      add(mModLevels);

      mCarsOwnedList = new phui::ListBox();
      mCarsOwnedList->setSize(250, 135);
      mCarsOwnedList->setPosition(280, 30);
      mCarsOwnedList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mCarsOwnedList->setForegroundColor(phui::WHITE);
      mCarsOwnedList->addListSelectionListener(this);
      add(mCarsOwnedList);

      mModsOwnedList = new phui::ListBox();
      mModsOwnedList->setSize(250, 135);
      mModsOwnedList->setPosition(280, 170);
      mModsOwnedList->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      mModsOwnedList->setForegroundColor(phui::WHITE);
      mModsOwnedList->addListSelectionListener(this);
      add(mModsOwnedList);

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

   ChopShopWnd::~ChopShopWnd()
   {}

   void ChopShopWnd::onAction(const phui::ActionEvent& evt)
   {
      phui::Widget* src = evt.getSource();
      if (src == mDoneBtn) {
         hide();
      } else if (src == mBuyBtn) {
         mSubState = Send_Buy_Request;
      } else if (src == mSellBtn) {
         mSubState = Send_Sell_Request;
      }
   }

   void ChopShopWnd::onListSelection(const phui::ListSelectionEvent& evt)
   {
      phui::Widget* src = evt.getSource();
      updateLists((phui::ListBox*)src);
   }

   void ChopShopWnd::updateData(data::Player* player,
                                data::CarTypeList* allCars,
                                data::ModTypeList* allMods) {
      mPlayer = player;
      mCarTypes = allCars;
      mModTypes = allMods;

      updateLists(); // no args = update all
   }

   void ChopShopWnd::updateLists(phui::ListBox* changed /*=NULL*/) {
      // only update car and mod list if are updating all of the boxes
      if(changed == NULL) {
         // update car list
         mCarsOwnedList->clear();

         data::CarList* carlist = &mPlayer->getCars();
         for(unsigned int x=0;x<carlist->size();++x) {
            mCarsOwnedList->add((*carlist)[x]->getName());
         }

         // update mod list
         mModsList->clear();

         for(unsigned int x=0;x<mModTypes->size();++x) {
            mModsList->add((*mModTypes)[x]->getName());
         }

         // since we updated the car list
         changed = mCarsOwnedList;
      }

      // car box was changed, update mod list else
      if(changed == mCarsOwnedList) {
         // update mod list
         mModsOwnedList->clear();

         int selectedItem = mCarsOwnedList->getSelectedIndex();
         // if something is selected in the car
         if(selectedItem != -1) {
            // determine which Car is selected
            std::string carName = mCarsOwnedList->get(selectedItem);
            data::CarList* carlist = &mPlayer->getCars();
            data::Car* selectedCar = NULL;
            for(unsigned int x=0;x<carlist->size();++x) {
               if((*carlist)[x]->getName() == carName) {
                  selectedCar = (*carlist)[x];
                  break;
               }
            }

            // now add the mods for this car
            if(selectedCar != NULL) {
               data::ModList* modlist = &selectedCar->getMods();
               for(unsigned int x=0;x<modlist->size();++x) {
                  char buf[7];
                  sprintf(buf, "%d", (*modlist)[x]->getLevel());
                  mModsOwnedList->add((*modlist)[x]->getName()+" ("+std::string(buf)+")");
               }
            }
         }

         // since we updated the mod list
         changed = mModsOwnedList;
      }

      // mod list box was changed
      if(changed == mModsOwnedList) {
         // not really much to do
      }

      // mods list updated, let's update the level
      if(changed == mModsList) {
         // update mod list
         mModLevels->clear();

         int selectedItem = mModsList->getSelectedIndex();
         // if something is selected in the mod list
         if(selectedItem != -1) {
            // determine which mod is selected
            std::string modName = mModsList->get(selectedItem);
            data::ModType* selectedModType = NULL;
            for(unsigned int x=0;x<mModTypes->size();++x) {
               if((*mModTypes)[x]->getName() == modName) {
                  selectedModType = (*mModTypes)[x];
                  break;
               }
            }

            if(selectedModType != NULL) {
               for(int x=selectedModType->getMin();x<=selectedModType->getMax();++x) {
                  char buf[7];
                  sprintf(buf, "%d", x);
                  mModLevels->add(std::string(buf));
               }
            }
         }
      }
   }

   void ChopShopWnd::update(BrothaApp* app, int elapsedTime) {
      if(mSubState == Send_Buy_Request) {
         int selectedMod = mModsList->getSelectedIndex();
         int selectedLevel = mModLevels->getSelectedIndex();
         int selectedCar = mCarsOwnedList->getSelectedIndex();

         // if an item is selected
         if(selectedMod != -1 && selectedLevel != -1 && selectedCar != -1) {
            // disable the window till further notice
            this->setEnabled(false);

            // request to buy it
            app->sendMessage(new net::BuyModMessage(mCarsOwnedList->get(selectedCar),
                                                    mModsList->get(selectedMod),
                                                    atoi(mModLevels->get(selectedLevel).c_str())));
            mSubState = Wait_For_Buy_Response;
         } else {
            // go back to waiting
            mSubState = User_Input;
         }
      } else if(mSubState == Send_Sell_Request) {
         int selectedMod = mModsOwnedList->getSelectedIndex();
         int selectedCar = mCarsOwnedList->getSelectedIndex();

         // if an item is selected
         if(selectedMod != -1 && selectedCar != -1) {
            // disable the window till further notice
            this->setEnabled(false);

            // request to sell it
            std::string modName = mModsOwnedList->get(selectedMod);
            app->sendMessage(new net::SellModMessage(mCarsOwnedList->get(selectedCar),
                                                     modName.substr(0,modName.length()-4)));
            mSubState = Wait_For_Sell_Response;
         } else {
            // go back to waiting
            mSubState = User_Input;
         }
      } else if(mSubState == Wait_For_Buy_Response) {
         int selectedMod = mModsList->getSelectedIndex();
         int selectedLevel = mModLevels->getSelectedIndex();
         int selectedCar = mCarsOwnedList->getSelectedIndex();

         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::OK) {
               net::OKMessage* okMsg = (net::OKMessage*)msg;

               if(okMsg->getCode() == net::OKMessage::OKAY) {
                  // if the purchase was successful

                  std::string carName = mCarsOwnedList->get(selectedCar);
                  std::string modName = mModsList->get(selectedMod);
                  int modLevel = atoi(mModLevels->get(selectedLevel).c_str());

                  data::Car* car = mPlayer->getCar(carName);
                  if(car != NULL) {
                     data::Mod* mod = car->getMod(modName);
                     if(mod == NULL) {
                        car->addMod(new data::Mod(modName, modLevel));
                     } else {
                        mod->setLevel(modLevel);
                     }
                  }
                  updateLists(mCarsOwnedList);
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
         int selectedMod = mModsOwnedList->getSelectedIndex();
         int selectedCar = mCarsOwnedList->getSelectedIndex();

         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::OK) {
               net::OKMessage* okMsg = (net::OKMessage*)msg;

               if(okMsg->getCode() == net::OKMessage::OKAY) {
                  // if the purchase was successful

                  std::string carName = mCarsOwnedList->get(selectedCar);
                  std::string modName = mModsOwnedList->get(selectedMod);

                  data::Car* car = mPlayer->getCar(carName);
                  if(car != NULL) {
                     car->removeMod(modName.substr(0,modName.length()-4));
                  }
                  updateLists(mCarsOwnedList);
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
