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
 * File:          $RCSfile: LoginState.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:03 $
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

#include <phui/SDLBridge.h>
#include "BrothaApp.h"
#include "LoginState.h"
#include "GameState.h"
#include "GarageState.h"
#include <map>



namespace client {
   std::map<std::string, bool> input;

   const float PI = 3.141579f;
   
   template< class T >
   T deg2rad(const T& deg) {
      return deg * PI / T(180);
   }

   LoginState::LoginState() {
      /// @todo make this the same size as the game window?  depends
      /// if we want the UI to be resolution-dependent or not...
      mRoot = phui::CreateRoot(640, 480);

      mSubState = User_Input;

      const int border_w = 50;
      const int border_h = 50;

      // main window
      phui::Window* window = new phui::Window();
      window->setPosition(border_w, border_h);
      window->setSize(640 - border_w * 2, 480 - border_h * 2);
      window->setBackgroundColor(phui::Colorf(0.2f, 0.3f, 0.8f, 0.8f));
      window->show();

      mRoot->add(window);

      mUsername = addLabeledField(window, "Username", 1);
      mPassword = addLabeledField(window, "Password", 2);
      mServer   = addLabeledField(window, "Server",   3);
      mPort     = addLabeledField(window, "Port",     4);

      mUsername->setText("aegis");
      mPassword->setText(":)");
      mServer->setText("127.0.0.1");
      mPort->setText("35791");

      mConnect = new phui::Button("Connect");
      mConnect->setPosition(50, 300);
      mConnect->setSize(100, 20);
      mConnect->addActionListener(this);
      window->add(mConnect);

      mQuit = new phui::Button("Quit");
      mQuit->setPosition(200, 300);
      mQuit->setSize(100, 20);
      mQuit->addActionListener(this);
      window->add(mQuit);

      mSpectator = new phui::CheckBox();
      mSpectator->setPosition(50, 250);
      mSpectator->setSize(20, 20);
      mSpectator->show();
      window->add(mSpectator);

      phui::Label* spectatorLbl = new phui::Label("Login as Spectator");
      spectatorLbl->setPosition(80, 250);
      spectatorLbl->setSize(150,20);
      spectatorLbl->show();
      window->add(spectatorLbl);

      mRoot->add(window);

      // Setup the scene
      mScene.addObject("tank", "models/hovertank_body.obj");

      mScene.addObject("tank2", "models/hovertank_body.obj");
      mScene.getObject("tank2")->preMult(osg::Matrix::translate(0.5,0,-2));
      mScene.getObject("tank2")->preMult(osg::Matrix::rotate(180.0f, 0,1,0));

      mScene.getCamera().setFollowDist(5);
      mScene.getCamera().setPitch(deg2rad(15.0f));

      std::cout<<"Entered Login state"<<std::endl;
   }

   LoginState::~LoginState() {
      std::cout<<"Left Login state"<<std::endl;
   }

   void
   LoginState::draw() {
      glClear(GL_COLOR_BUFFER_BIT);
      mScene.draw();
      mRoot->draw();
/*
      glDisable(GL_LIGHTING);
      float extent = 100.0f;
      float inc = 0.1f;
      glColor3f(0,0,1);
      glBegin(GL_LINES);
         for (float i=-extent; i<extent; i+=inc)
         {
            glVertex3f(-extent, 0, i);
            glVertex3f( extent, 0, i);
            glVertex3f( i, 0, -extent);
            glVertex3f( i, 0,  extent);
         }
      glEnd();
      glEnable(GL_LIGHTING);
*/
   }

   void
   LoginState::update(BrothaApp* app, int elapsedTime) {
      if(mSubState == Send_Login) {
         // connect to server
         int port = atoi(mPort->getText().c_str());

         try {
            app->connectToServer(mServer->getText(), port);
         } catch (net::SocketException& e) {
            std::cout<<"Connection to "<<mServer->getText()<<":"<<port<<" failed!"<<std::endl;
            mSubState = User_Input;
            return;
         }

         // send login packet
         app->sendMessage(new net::LoginMessage(mUsername->getText(), mPassword->getText()));

         // we'll need an ack from server
         mSubState = Wait_For_Login_Ack;
      } else if(mSubState == Wait_For_Login_Ack) {
         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::OK) {
               net::OKMessage* okMsg = (net::OKMessage*)msg;

               // check for good login
               if(okMsg->getCode() == net::OKMessage::OKAY) {
                  std::cout<<"Login successful"<<std::endl;
                  // send request to join game
                  if(mSpectator->isChecked()) {
                     app->sendMessage(new net::JoinAsMessage(net::JoinAsMessage::SPECTATOR));
                  } else {
                     app->sendMessage(new net::JoinAsMessage(net::JoinAsMessage::PLAYER));
                  }

                  // go to next state
                  mSubState = Wait_For_Join_Ack;
               } else {
                  std::cout<<"Login failed"<<std::endl;
                  /// @todo raise an error
               }
            } else {
               std::cout<<"ERROR: Got the wrong message type"<<std::endl;
               /// @todo raise an error
            }
         }
      } else if(mSubState == Wait_For_Join_Ack) {
         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::OK) {
               net::OKMessage* okMsg = (net::OKMessage*)msg;

               // check for good join
               if(okMsg->getCode() == net::OKMessage::OKAY) {
                  std::cout<<"Join As successful"<<std::endl;

                  // go to next state
                  mSubState = Wait_For_EnterAs;
               } else {
                  std::cout<<"Join As failed"<<std::endl;
                  /// @todo raise an error
               }
            } else {
               std::cout<<"ERROR: Got the wrong message type"<<std::endl;
               /// @todo raise an error
            }
         }
      } else if(mSubState == Wait_For_EnterAs) {
         net::Message* msg = NULL;
         if(app->getFirstMsg(msg)) {
            // make sure we got the right message type
            if(msg->getType() == net::Enter) {
               net::EnterMessage* entMsg = (net::EnterMessage*)msg;

               // check for good join
               if(entMsg->getCode() == net::EnterMessage::GAME) {
                  std::cout<<"Enter As successful (in game)"<<std::endl;

                  app->invokeStateTransition(new GameState());
               } else if(entMsg->getCode() == net::EnterMessage::GARAGE) {
                  std::cout<<"Enter As successful (in garage)"<<std::endl;

                  app->invokeStateTransition(new GarageState());
               } else {
                  std::cout<<"Enter As failed"<<std::endl;
                  /// @todo raise an error
               }
            } else {
               std::cout<<"ERROR: Got the wrong message type"<<std::endl;
               /// @todo raise an error
            }
         }
      } else { // User_Input
         // don't do anything  ^__^
         float dt = (float)elapsedTime / 1000.0f;

         // Move the tank
         float speed = 3.7f;
         if (input["drive"]) {
            osg::Vec3 forward(0,0,-speed);
            forward *= dt;
            mScene.getObject("tank")->preMult(osg::Matrix::translate(forward));
         }
         if (input["reverse"]) {
            osg::Vec3 backward(0,0,speed);
            backward *= dt;
            mScene.getObject("tank")->preMult(osg::Matrix::translate(backward));
         }
         if (input["turnleft"]) {
            float ang = deg2rad(30.0f) * dt;
            mScene.getObject("tank")->preMult(osg::Matrix::rotate(ang, 0,1,0));
         }
         if (input["turnright"]) {
            float ang = deg2rad(-30.0f) * dt;
            mScene.getObject("tank")->preMult(osg::Matrix::rotate(ang, 0,1,0));
         }

         osg::Quat targetRot;
         targetRot.set(mScene.getObject("tank")->getMatrix());
         osg::Vec3 targetPos = mScene.getObject("tank")->getMatrix().getTrans();
         mScene.getCamera().setTarget(targetPos, targetRot);
         mScene.getCamera().update(dt);
      }
   }

   void
   LoginState::onKeyPress(SDLKey sym, bool down) {
      if (sym == SDLK_w) {
         input["drive"] = down;
      }
      else if (sym == SDLK_s) {
         input["reverse"] = down;
      }
      else if (sym == SDLK_a) {
         input["turnleft"] = down;
      }
      else if (sym == SDLK_d) {
         input["turnright"] = down;
      }
      else if (sym == SDLK_ESCAPE) {
         exit(0);
      }

      if (down) {
         mRoot->onKeyDown(phui::SDLToPhuiKey(sym));
      } else {
         mRoot->onKeyUp(phui::SDLToPhuiKey(sym));
      }
   }

   void
   LoginState::onMousePress(Uint8 button, bool down, int x, int y) {
      phui::Point p(x, y);
      if (down) {
         mRoot->onMouseDown(phui::SDLToPhuiButton(button), p);
      } else {
         mRoot->onMouseUp(phui::SDLToPhuiButton(button), p);
      }
   }

   void
   LoginState::onMouseMove(int x, int y) {
      mRoot->onMouseMove(phui::Point(x, y));
   }

   phui::TextField*
   LoginState::addLabeledField(phui::WidgetContainer* container,
                               const std::string& label,
                               int index)
   {
      phui::Label* labelWidget = new phui::Label(label.c_str());
      labelWidget->setPosition(50, 50 * index);
      labelWidget->setSize(100, 20);
      labelWidget->setBackgroundColor(phui::Colorf(0, 0, 0, 0.1f));
      container->add(labelWidget);

      phui::TextField* textWidget = new phui::TextField;
      textWidget->setPosition(200, 50 * index);
      textWidget->setSize(150, 20);
      container->add(textWidget);
      return textWidget;
   }

   void LoginState::onAction(const phui::ActionEvent& evt) {
      phui::Widget* src = evt.getSource();
      if(src == mConnect) {
         mSubState = Send_Login;
      } else if(src == mQuit) {
         exit(0);
      }
   }
}
