/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "InputParser.h"
#include "InputBinder.h"
#include "InputManager.h"
#include <iostream>
#include <fstream>
#include <utility>

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
      std::cerr << "Parsing File " << name << std::endl;
      std::ifstream inFile(name.c_str());
      if (inFile)
      {
         while (!inFile.eof())
         {
            inFile.getline(cbuffer, sizeof(cbuffer));
            buffer = cbuffer;
            std::cerr << "Read: " << buffer << std::endl;
            int index = buffer.find('=');
            std::string skey = buffer.substr(0, index);
            std::string action = buffer.substr(index + 1);
            std::cerr << "Key: " << skey << std::endl;
            std::cerr << "Action: " << action << std::endl;
            InputKey key = StringtoISym(skey);
            std::cerr << "Insterting action: " << action << " key: " << key << std::endl;
			mActionKeys.insert(std::make_pair(action, key));
         }
         bParseFile = true;
      }
   }

   bool InputParser::bindAction(const std::string &name, InputAction *action)
   {
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
      InputBinder *binder = InputBinder::instance();
      if (!action)
      {
         //User gave us an unallocated action
         action = InputManager::instance()->createAction();
      }
      //Loop through the keys and bind them to the action passed to us.
      for (std::multimap<std::string, InputKey>::iterator itr = range.first; itr != range.second; ++itr)
      {
         std::cerr << "Binding: " << name << " to " << itr->second << std::endl;
         binder->bindAction(action, itr->second);
      }
      return true;
   }
      

}//end of namespace mw
