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
 * File:          $RCSfile: BrothaApp.h,v $
 * Date modified: $Date: 2002-03-29 08:33:21 $
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
#ifndef CLIENT_BROTHA_APP_H
#define CLIENT_BROTHA_APP_H

#include <gk/gk.h>   // pull in GameKernel
#include <GL/gl.h>
#include <GL/glu.h>
#include "game/BrothaGame.h"
#include "net/NetMgr.h"

namespace client
{
   /**
    * Warn-a-Brotha interface with GameKernel.
    */
   class BrothaApp : public gk::AbstractGameApp
   {
   public:
      /// Creates a new brotha app.
      BrothaApp();

      /// Cleans up resources used by this app.
      virtual ~BrothaApp();

      /**
       * Called by the game kernel when the application is being initialized,
       * but before the system driver has been started.
       *
       * We initialize the input interfaces here.
       *
       * @param kernel     the IGameKernel initializing this driver
       */
      virtual void onAppInit( gk::IGameKernel* kernel );

      /**
       * Called by the game kernel when the window is initialized.
       */
      virtual void onContextInit();

      /**
       * Called by the game kernel each frame for each window open.
       *
       * @param context    the context of the window being drawn
       */
      virtual void onContextDraw( int context );

      /**
       * Called by the game kernel immediately after each frame is drawn.
       */
      virtual void onPostFrame();

      /**
       * Handles input and acts on the game accordingly.
       */
      void processInput();

   public:
      gk::DigitalInterface
         mAccelerate,
         mBrake,
         mTurnLeft,
         mTurnRight,
         mPause,
         mQuit;

      /// The kernel running this app
      gk::IGameKernel* mKernel;

      /// Our lovely game instance
      game::BrothaGame mGame;

      /// Our gateway to the network interface
      net::NetMgr* mNetMgr;

      /// The connection to the server
      net::NetMgr::ConnID mConnID;
   };
}

#endif
