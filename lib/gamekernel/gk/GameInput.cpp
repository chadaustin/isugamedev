
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: GameInput.cpp,v $
// Date modified: $Date: 2003-02-10 05:10:37 $
// Version:       $Revision: 1.3 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "GameInput.h"

namespace gk {

GameInput::GameInput()
{
}

GameInput::~GameInput()
{
}

Input* GameInput::getInput( const std::string& alias )
{
   if (mBindTable.count( alias ) == 0)
      return NULL;

   EventInput& event_input = mBindTable[alias];
   return &event_input;
}

Input* GameInput::getInput( const std::string& device, const std::string& input )
{
   if (mDevices.count( device ) == 0)
      return NULL;

   IDevice* dev = mDevices[device];
   return dev->getInput( input );
}

bool GameInput::addDevice( IDevice* device, const std::string& name )
{
   if (mDevices.count( name ) == 0)
   {
      mDevices[ name ] = device;
      std::cout << "Added device: " << name << std::endl;
      this->refreshEventInputs();
      return true;
   }
   std::cout << "Failed to add device: " << name << std::endl;
   return false;
}

IDevice* GameInput::getDevice( const std::string& name )
{
   std::map< std::string, IDevice* >::iterator itr;
   itr = mDevices.find( name );
   if ( itr != mDevices.end() )
   {
      return itr->second;
   }
   std::cout << "WARNING: cannot lookup device " << name << std::endl;
   return NULL;
}

void GameInput::removeDevice( const std::string& name )
{
   std::map< std::string, IDevice* >::iterator itr;
   itr = mDevices.find( name );
   if ( itr != mDevices.end() )
   {
      mDevices.erase( itr );
      std::cout << "Removed device: " << name << std::endl;
      this->refreshEventInputs();
   }
}

void GameInput::bind( const std::string& alias, const std::string& device,
                      const std::string& input )
{
   Input* in_put = getInput( device, input );
   mBindTable[alias].add( in_put );
   mBindStrings.insert( std::pair<std::string, std::pair<std::string, std::string> >( alias, std::pair<std::string, std::string>(device, input) ) );
   std::cout << "Bound [" << device << ":" << input << "] to [" << alias << "]" << std::endl;
}

void GameInput::update()
{
   std::map<std::string, IDevice*>::iterator itr;
   for( itr = mDevices.begin(); itr != mDevices.end(); ++itr )
   {
      itr->second->update();
   }
}

void GameInput::refreshEventInputs()
{
   // reset each EventInput object (this removes all binding info from them...)
   std::map<std::string, EventInput>::iterator itr;
   for (itr = mBindTable.begin(); itr != mBindTable.end(); ++itr)
   {
      (*itr).second.clear();
   }

   // re-add all binding info to EventInputs based on currently added devices..
   std::multimap<std::string, std::pair<std::string, std::string> >::iterator it;
   for (it = mBindStrings.begin(); it != mBindStrings.end(); ++it)
   {
      Input* in_put = getInput( (*it).second.first, (*it).second.second );
      if (in_put)
      {
         mBindTable[(*it).first].add( in_put );
         //std::cout << "   refresh: " << (*it).first << " " << (*it).second.first << " " << (*it).second.second << std::endl;
      }
   }
}

} // namespace gk
