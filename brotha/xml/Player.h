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
 * File:          $RCSfile: Player.h,v $
 * Date modified: $Date: 2002-04-28 16:41:08 $
 * Version:       $Revision: 1.6 $
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

#ifndef BDATA_PLAYER_H
#define BDATA_PLAYER_H

#include <iostream>
#include <string>
#include <vector>

namespace dataxml{


class Player{
private:
  std::string name;
  std::string password; //look, it's private so it's secure :)
  carlist cars;
  statlist stats;

public:
  Player(std::string iname, std::string ipasswd){
    name = iname;
    password = ipasswd;
  }

  void changePassword(std::string npw){
     password = npw;
  }

  std::string getName(){
    return name;
  }

  std::string getPassword(){
    return password;
  }

  carlist getCars(){
    return cars;
  }

  statlist getStats(){
	  return stats;
  }

  void addCar(Car* c){
    cars.push_back(c);
  }
  void addStat(Stat* s){
	  stats.push_back(s);
  }

  void xMLify(std::ostream& out){
    out << "    <player name=\"" << name << "\" password=\"" << password << "\">" << std::endl;
    for(unsigned int i = 0; i < cars.size(); i++){
      cars[i]->xMLify(out);
    }
    for(unsigned int i = 0; i < stats.size(); i++){
      stats[i]->xMLify(out);
    }
	out << "   </player>" << std::endl;
  }
  
};

typedef std::vector<Player*> playerlist;
}

#endif
