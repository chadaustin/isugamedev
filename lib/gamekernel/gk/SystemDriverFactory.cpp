
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
// File:          $RCSfile: SystemDriverFactory.cpp,v $
// Date modified: $Date: 2002-02-13 08:07:01 $
// Version:       $Revision: 1.1 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "gk/SystemDriverFactory.h"
#include <iostream>

namespace gk {

//------------------------------------------------------------------------------

SystemDriverFactory::SystemDriverFactory()
{
}

//------------------------------------------------------------------------------

SystemDriverFactory::~SystemDriverFactory()
{
}

//------------------------------------------------------------------------------

SystemDriver*
SystemDriverFactory::getDriver( const std::string& name )
{
   // Make sure a driver exists in the registry under the given name
   if ( ! isRegistered( name ) )
   {
      std::cerr<<"No system driver is registered under "<<name.c_str()<<std::endl;
      return NULL;
   }
   return (mRegistry.find( name )->second);
}

//------------------------------------------------------------------------------

void
SystemDriverFactory::registerDriver( const std::string& name,
                                     SystemDriver* driver )
{
   // Check to make sure we don't write over an existing registration
   if ( isRegistered( name ) )
   {
      std::cerr<<"A system driver is already registered under "<<name.c_str()<<std::endl;
      return;
   }
   mRegistry[name] = driver;
}

//------------------------------------------------------------------------------

void
SystemDriverFactory::unregisterDriver( const std::string& name )
{
   // Only unregister if there is something there to remove
   if ( ! isRegistered( name ) )
   {
      std::cerr<<"No system driver is registered under "<<name.c_str()<<std::endl;
      return;
   }
   // erase the item from the map only after we've save the value stored
   std::map<std::string, SystemDriver*>::iterator it;
   it = mRegistry.find( name );
   SystemDriver* driver = it->second;
   mRegistry.erase( it );

   // now free the memory allocated to the driver
   delete driver;
}

//------------------------------------------------------------------------------

bool
SystemDriverFactory::isRegistered( const std::string& name ) const
{
   return ( (mRegistry.find( name ) == mRegistry.end()) ? false : true );
}

//------------------------------------------------------------------------------

unsigned int
SystemDriverFactory::getNumRegistered() const
{
   return mRegistry.size();
}

//------------------------------------------------------------------------------

} // namespace gk
