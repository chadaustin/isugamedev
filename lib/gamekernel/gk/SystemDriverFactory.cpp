
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
// Date modified: $Date: 2003-02-08 21:27:45 $
// Version:       $Revision: 1.8 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "SystemDriverFactory.h"
#include <iostream>
#include <fstream>

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

ISystemDriver*
SystemDriverFactory::getDriver( const std::string& name )
{
   // Make sure a driver exists in the registry under the given name
   if ( ! isRegistered( name ) )
   {
      std::cerr<<"No system driver is registered under "<<name.c_str()<<std::endl;
      return NULL;
   }
   return (mRegistry.find( name )->second.first);
}

//------------------------------------------------------------------------------

void
SystemDriverFactory::registerDriver( const std::string& name,
                                     ISystemDriver* driver,
                                     xdl::Library* library )
{
   // Check to make sure we don't write over an existing registration
   if ( isRegistered( name ) )
   {
      std::cerr<<"A system driver is already registered under "<<name.c_str()<<std::endl;
      return;
   }
   mRegistry[name] = std::pair<ISystemDriver*, xdl::Library*>( driver, library );
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
   std::map<std::string, std::pair<ISystemDriver*, xdl::Library*> >::iterator it;
   it = mRegistry.find( name );
   ISystemDriver* driver = it->second.first;
   xdl::Library* lib = it->second.second;
   mRegistry.erase( it );

   // now free the memory allocated to the driver
   delete driver;
   if ( lib != NULL )
   {
      // this driver was alloc'd within a library - close it.
      lib->close();
      delete lib;
   }
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

bool
SystemDriverFactory::probe( const std::string& library,
                            const std::string& name )
{
   // tweak the library name
   std::string libFile = library + ".gkd";

   std::cout << "Probing " << libFile << " for a system driver ... ";

   // try to open the library
   xdl::Library* lib = new xdl::Library();
   if ( ! lib->open( libFile.c_str() ) )
   {
      std::cout<<" - library open failed!"<<std::endl;
      // oops ... the file probably doesn't exist
      std::fstream test_exist( libFile.c_str() );
      if (test_exist.is_open())
         std::cout << " - file named " << libFile << " exists, but isn't a library" << std::endl;
      else
         std::cout << " - file named " << libFile << " doesn't exist " << std::endl;
      delete lib;
      return false;
   }

   // grab a pointer to the query function
   typedef ISystemDriver* (*createfunc_t)();
   createfunc_t createFunc = (createfunc_t)lib->lookup("createSystemDriver");
   if ( createFunc == NULL )
   {
      std::cout<<"can't find createSystemDriver func"<<std::endl;
      // the library probably isn't really a gk driver DLL
      std::cout << "failed" << std::endl;
      lib->close();
      delete lib;
      return false;
   }

   // get a pointer to the driver
   ISystemDriver* driver = (*createFunc)();
   if ( driver == NULL )
   {
      // some error in the library perhaps?
      std::cout << "failed" << std::endl;
      lib->close();
      delete lib;
      return false;
   }
   std::cout << "successful" <<std::endl;

   registerDriver( name, driver, lib );
   return true;
}

//------------------------------------------------------------------------------

} // namespace gk
