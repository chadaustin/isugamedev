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
 * File:          $RCSfile: Gang.h,v $
 * Date modified: $Date: 2002-05-03 04:13:09 $
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
#ifndef DATA_GANG_H
#define DATA_GANG_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

namespace data {

   class Gang {

   public:

  	  std::string mPic; //image URL
	  std::string mThumbPic; //thumbnail image url
      /// Creates a new gang with the given name.
      Gang(const std::string& name)
         : mName(name)
      {
		 mPic = std::string("");
		 mThumbPic = std::string("");
	  }

      /// Adds the given player to this gang.
      void addPlayer(Player* player) {
         mPlayers.push_back(player);
      }

      PlayerList& getPlayerList() {
         return mPlayers;
      }

      void setInfo(const std::string& info) {
         mInfo = info;
      }

      const std::string& getInfo() const {
         return mInfo;
      }

      const std::string& getName() const {
         return mName;
      }

      Player* getPlayer(const std::string& name) {
         PlayerList::iterator itr;
         for (itr = mPlayers.begin(); itr != mPlayers.end(); ++itr) {
            Player* p = *itr;
            if(p->getName() == name) {
               return p;
            }
         }
         return NULL;
      }

      void xMLify(std::ostream& out) {
         out << "  <gang name=\"" << mName << "\" pic=\"" << mPic << "\" lilpic=\"" << mThumbPic << "\" >" << std::endl;
         out << "    <info>" << mInfo << "</info>" <<std::endl;
         for(unsigned int i = 0; i < mPlayers.size(); i++) {
            mPlayers[i]->xMLify(out);
         }
         out << "  </gang>" <<std::endl;
      }



   private:


      /// The name of this gang.
      std::string mName;

      /// An description of this gang.
      std::string mInfo;

      /// The list of players that are members of this gang.
      PlayerList mPlayers;
   };

   typedef std::vector<Gang*> GangList;

}
#endif
