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
 * File:          $RCSfile: GameState.cpp,v $
 * Date modified: $Date: 2002-05-01 19:39:11 $
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

#include <phui/SDLBridge.h>
#include "BrothaApp.h"
#include "GameState.h"
#include <map>



namespace client {
   std::map<std::string, bool> input;

   const float PI = 3.141579f;
   
   template< class T >
   T deg2rad(const T& deg) {
      return deg * PI / T(180);
   }
   
   GameState::GameState() {
      // Setup the scene
      mScene.addObject("tank", "models/hovertank_body.obj");

      mScene.addObject("tank2", "models/hovertank_body.obj");
      mScene.getObject("tank2")->preMult(osg::Matrix::translate(0.5,0,-2));
      mScene.getObject("tank2")->preMult(osg::Matrix::rotate(180.0f, 0,1,0));

      mScene.getCamera().setFollowDist(5);
      mScene.getCamera().setPitch(deg2rad(15.0f));
   }

   GameState::~GameState() {
   }

   void
   GameState::draw() {
      glClear(GL_COLOR_BUFFER_BIT);
      mScene.draw();
   }

   void
   GameState::update(BrothaApp* app, int elapsedTime) {
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

   void
   GameState::onKeyPress(SDLKey sym, bool down) {
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
   }

   void
   GameState::onMousePress(Uint8 button, bool down, int x, int y) {
   }

   void
   GameState::onMouseMove(int x, int y) {
   }
}
