/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* barfight-cpr beg
 *
 * barfight - a slapstick drag-out brawl at the local pub
 * barfight is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * -----------------------------------------------------------------
 * File:          $RCSfile: GameState.h,v $
 * Date modified: $Date: 2003-02-25 06:39:39 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** barfight-cpr-end */
#include <string>
#include <vector>
#include <siren/siren.h>

namespace bar
{
   /**
    * This great state is where the game is played.
    */
   class GameState : public siren::State
   {
   public:
      GameState();
      ~GameState();

      void draw() const;

      void update(float dt);
      void onKeyPress(SDLKey sym, bool down);
      void onMouseMove(int x, int y);

   private:
      /**
       * Blends the motion blur texture onto the scene.
       */
      void drawMotionBlur() const;

      /**
       * Draws the scene. This is separate to allow for multi-pass rendering
       * techniques such as motion blur.
       */
      void drawScene() const;

   private:
      siren::Avatar* mPlayer;
      std::vector<siren::Avatar*> mNPCs;

      unsigned int mAnim;
      std::vector<std::string> mAnims;

      /// Percentage of drunkenness. Clamped [0,1].
      float mDrunkAmount;

      /// The texture containg the motion blur affect.
      siren::Texture* mBlurTexture;

      /// Do we need to ignore the next mouse move because of the mouse warp?
      bool mIgnoreMouseMove;

      float mFPS;
      int   mNumFrames;
      float mFrameTime;
      siren::Camera mCamera;
   };
}
