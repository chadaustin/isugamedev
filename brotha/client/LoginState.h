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
 * File:          $RCSfile: LoginState.h,v $
 * Date modified: $Date: 2002-04-28 16:41:03 $
 * Version:       $Revision: 1.7 $
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
#ifndef CLIENT_LOGIN_STATE_H
#define CLIENT_LOGIN_STATE_H


#include <phui/phui.h>
#include <phui/ActionListener.h>
#include "State.h"
#include "Scene.h"


namespace client {

   class LoginState : public State, public phui::ActionListener {
   public:
      enum SubState {
         User_Input, ///< waiting for user to click connect
         Send_Login, ///< need to send login
         Wait_For_Login_Ack, ///< wait for login ack
         Wait_For_Join_Ack, ///< wait for join ack
         Wait_For_EnterAs, ///< wait for enter msg
      };
   public:
      LoginState();
      ~LoginState();

      void draw();
      void update(BrothaApp* app, int elapsedTime);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      virtual void onAction(const phui::ActionEvent& evt);
   private:
      phui::TextField* addLabeledField(phui::WidgetContainer* container,
                                       const std::string& label,
                                       int index);

      phui::RootWidget* mRoot;
      phui::TextField*  mUsername;
      phui::TextField*  mPassword;
      phui::TextField*  mServer;
      phui::TextField*  mPort;
      phui::Button* mConnect;
      phui::Button* mQuit;
      phui::CheckBox* mSpectator;

      Scene mScene;

      SubState mSubState;
   };

}


#endif
