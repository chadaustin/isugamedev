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
 * Date modified: $Date: 2002-05-03 07:33:52 $
 * Version:       $Revision: 1.16 $
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
#include "net/GarageDataMessage.h"
#include "net/RequestGarageDataMessage.h"
#include "net/ChangeLocationMessage.h"
#include "BrothaApp.h"
#include "GarageState.h"
#include "GameState.h"
#include <map>

namespace client {
   const float PI = 3.141579f;
   
   GarageState::GarageState() {
      std::cout<<"Entered Garage state"<<std::endl;

      mRoot = phui::CreateRoot(640,480);

      // main window
      mMainWnd = new phui::Window();
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
      mDealer = new DealerWnd();
      mDealer->setPosition(50, 50);
      mDealer->addWindowListener(this);

      // chop shop window
      mChopShop = new ChopShopWnd();
      mChopShop->setPosition(50, 50);

      // start with the main window
      mRoot->add(mDealer);
      mRoot->add(mChopShop);
      mRoot->add(mMainWnd);

      mMainWnd->setVisible(false);
      mPlayer = NULL;
      mCarTypes = NULL;

      mSubState = Send_Request;
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
      if(mSubState == Send_Request) {
         app->sendMessage(new net::RequestGarageDataMessage());

         mSubState = Wait_For_Data;
      } else if(mSubState == Wait_For_Data) {
         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::GarageData) {
               net::GarageDataMessage* gdMsg = (net::GarageDataMessage*)msg;

               mPlayer = gdMsg->getPlayer();
               mCarTypes = gdMsg->getCarTypes();

               mMainWnd->setVisible(true);

               mDealer->updateData(&mPlayer->getCars(), mCarTypes);

               mSubState = User_Input;
            } else {
               std::cout<<"ERROR: Got the wrong message type"<<std::endl;
               /// @todo raise an error
            }
         }
      } else if (mSubState == Join_Game) {
         app->sendMessage(new net::ChangeLocationMessage(net::ChangeLocationMessage::GAME));
         mSubState = Wait_Join_Game_Ack;
      } else if (mSubState == Wait_Join_Game_Ack) {
         net::Message* msg = NULL;
         if (app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::OK) {
               net::OKMessage* okMsg = (net::OKMessage*)msg;

               // Success ... move to GameState
               if (okMsg->getCode() == net::OKMessage::OKAY) {
                  app->invokeStateTransition(new GameState(app));
               }
               else {
                  std::cout<<"ERROR: failed to change to the game location"<<std::endl;
                  mSubState = User_Input;
               }
            } else {
               std::cout<<"ERROR: Got the wrong message type"<<std::endl;
               /// @todo raise an error
            }
         }
      } else {
         // we'll update child windows, that is all
         mDealer->update(app, elapsedTime);
         mChopShop->update(app, elapsedTime);
      }
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
         mDealer->show();
         mRoot->focus(mDealer);
      } else if (src == mChopShopBtn) {
         mChopShop->show();
         mRoot->focus(mChopShop);
      } else if (src == mJoinGameBtn) {
         mSubState = Join_Game;
      }
   }

   void
   GarageState::onWindowClosed(const phui::WindowEvent& evt) {
      if (evt.getWindow() == mDealer) {
         std::cout<<"Left the mini-dealer."<<std::endl;
      }
      else if (evt.getWindow() == mChopShop) {
         std::cout<<"Left the chop shop."<<std::endl;
      }
   }
}
