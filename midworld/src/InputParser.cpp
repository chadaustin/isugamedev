/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: InputParser.cpp,v $
 * Date modified: $Date: 2002-11-03 05:32:25 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include <fstream>
#include <utility>
#include <assert.h>
#include "InputParser.h"
#include "InputBinder.h"

namespace mw
{
   InputParser* InputParser::mInstance = NULL;
   
   InputParser* InputParser::instance()
   {
      if (mInstance == NULL)
      {
         mInstance = new InputParser();
      }
      return mInstance;
   }

   void InputParser::parseFile(const std::string &name)
   {
      char cbuffer[80];
      std::string buffer;
//      std::cerr << "Parsing File " << name << std::endl;
      std::ifstream inFile(name.c_str());
      if (inFile)
      {
         while (!inFile.eof())
         {
            inFile.getline(cbuffer, sizeof(cbuffer));
            buffer = cbuffer;
//            std::cerr << "Read: " << buffer << std::endl;
            int index = buffer.find('=');
            std::string skey = buffer.substr(0, index);
            std::string action = buffer.substr(index + 1);
//            std::cerr << "Key: " << skey << std::endl;
//            std::cerr << "Action: " << action << std::endl;
            InputKey key = StringtoISym(skey);
//            std::cerr << "Insterting action: " << action << " key: " << key << std::endl;
            mActionKeys.insert(std::make_pair(action, key));
         }
         bParseFile = true;
      }
   }

   bool InputParser::bindAction(const std::string &name, InputAction *action)
   {
      // Make sure the user didn't give us a bogus action
      assert(action != 0 && "action cannot be NULL");

      //Check to see if we've even read anything.
      if (!bParseFile)
      {
         return false;
      }
      //Check to see if we have an empty list.
      if (mActionKeys.find(name) == mActionKeys.end())
      {
         return false;
      }
      //Make a pair of iterators to get the keys bound to the actions.
      std::pair< std::multimap<std::string, InputKey>::iterator, std::multimap<std::string, InputKey>::iterator > range = mActionKeys.equal_range(name);

      //Get the binder
      InputBinder &binder = InputBinder::instance();

      //Loop through the keys and bind them to the action passed to us.
      for (std::multimap<std::string, InputKey>::iterator itr = range.first; itr != range.second; ++itr)
      {
         std::cerr << "Binding: " << name << " to " << itr->second << std::endl;
         binder.bindAction(action, itr->second);
      }
      return true;
   }
}
