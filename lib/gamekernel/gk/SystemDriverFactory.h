
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
// File:          $RCSfile: SystemDriverFactory.h,v $
// Date modified: $Date: 2002-02-13 08:40:43 $
// Version:       $Revision: 1.2 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_SYSTEMDRIVERFACTORY_H
#define GK_SYSTEMDRIVERFACTORY_H

#include "gk/gkCommon.h"
#include <string>
#include <map>
#include <vector>
#include <xdl.h>
#include "gk/Singleton.h"
#include "gk/SystemDriver.h"

namespace gk {

/**
 * Singleton class which is responsible for instantiating a system driver. It
 * generally also serves as a repository in which system drivers may register
 * themselves.
 */
class SystemDriverFactory : public Singleton<SystemDriverFactory>
{
public:
   /**
    * This is a singleton. Use getInstance() instead.
    */
   SystemDriverFactory();

   virtual ~SystemDriverFactory();

public:
   /**
    * Retrieves the system driver with the given name. Returns NULL if no driver
    * has been registered to that name.
    *
    * @param name    the name of the system driver to retrieve
    */
   SystemDriver* getDriver( const std::string& name );

   /**
    * Registers a system driver under the given name so that it can be retrieved
    * by the application. Once a driver is registered, the factory assumes
    * ownership of the memory aloccated to the driver. In other words, don't
    * delete the driver yourself. Instead, call unregisterDriver(..).
    *
    * @param name    the name under which to register the driver
    * @param driver  the driver instance to register
    * @param library the library through which the driver implementation was
    *                found, or NULL if the library was allocated locally.
    *                defaults to NULL.
    */
   void registerDriver( const std::string& name, SystemDriver* driver,
                        xdl::Library* library = NULL );

   /**
    * Removes the driver previously registered under the given name. Once the
    * driver is unregistered, it can no longer be created through this factory
    * until it is reregistered.
    *
    * @param name    the name of the system drvier.
    */
   void unregisterDriver( const std::string& name );

   /**
    * Checks if a driver has been registered under the given name.
    *
    * @param name    the name of the system driver
    *
    * @return  true if the driver is registered, false otherwise.
    */
   bool isRegistered( const std::string& name ) const;

   /**
    * Gets the number of system drivers registered with this factory.
    *
    * @return  the number of system driveres registered.
    */
   unsigned int getNumRegistered() const;

   /**
    * Probes the given library for a SystemDriver. If a driver does indeed exist
    * in the library, it is instantiated and registered with this factory under
    * the given name.
    *
    * @param library    the system-independent name of the library
    * @param name       the name under which to register the driver
    *
    * @return  true if successful, false otherwise
    */
   bool probe( const std::string& library, const std::string& name );

private:
   /**
    * A map of all registered system drivers keyed by their name. Each value is
    * a pair consisting of the SystemDriver implementation and the library
    * through which it was loaded. The library may be NULL if the driver was
    * allocated locally.
    */
   std::map< std::string, std::pair<SystemDriver*, xdl::Library*> > mRegistry;
};

} // namespace gk

#endif
