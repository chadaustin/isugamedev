/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * File:          $RCSfile: DriverManager.cpp,v $
 * Date modified: $Date: 2005-01-25 01:41:59 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "DriverManager.h"

namespace phui
{
   void
   DriverManager_t::registerDriver( const std::string& name, 
                          Loki::Functor< Driver*, TYPELIST_1(bool) > creator )
   {
      phuiDEBUG(phuiDBG_DEBUG)
         << "Attempting to register: '" << name << "'" 
         << std::endl;
      mDriverNames.push_back(name);
      if (!mDriverFactory.Register(name, creator))
      {
         phuiDEBUG(phuiDBG_ERROR) 
            << "Unable to register the driver " << name
            << std::endl;
      }
   }
   
   const std::string
   DriverManager_t::getSupportedDrivers()
   {
      std::string names("");
      std::vector<std::string>::iterator itr;
      for (itr = mDriverNames.begin(); itr != mDriverNames.end(); ++itr)
      {
         names += (*itr);
      }
      return names;
   }

   void
   DriverManager_t::setDriver(const std::string& driver, bool standalone)
   {
      if (!mDriver)
      {
         try
         {
            mDriver = mDriverFactory.CreateObject(driver, standalone);
         }
         catch(const std::exception& e)
         {
            phuiDEBUG(phuiDBG_ERROR) 
               << "Unknown driver type: '" << driver << "'"
               << std::endl;
         }
      }
      else
      {
         phuiDEBUG(phuiDBG_DEBUG)
            << "[WRN] setDriver() called for driver: " << driver
            << " but we are already running the driver " 
            << mDriver->getDriverName()
            << std::endl;
      }
   }

   void 
   DriverManager_t::registerRoot(RootWidgetPtr root)
   {
      if ( mDriver )
      {
         mDriver->registerRoot(root);
      }
   }

   void 
   DriverManager_t::onKeyDown(InputKey key)
   {
      if ( mDriver )
      {
         mDriver->onKeyDown(key);
      }
   }
   
   void 
   DriverManager_t::onMouseDown(InputButton button, const Point& p)
   {
      if ( mDriver )
      {
         mDriver->onMouseDown(button, p);
      }
   }

   void 
   DriverManager_t::onMouseUp(InputButton button, const Point& p)
   {
      if ( mDriver )
      {
         mDriver->onMouseUp(button, p);
      }
   }
   
   void 
   DriverManager_t::onMouseMove(const Point& p)
   {
      if ( mDriver )
      {
         mDriver->onMouseMove(p);
      }
   }

   void 
   DriverManager_t::start()
   {
      if ( mDriver )
      {
         mDriver->start();
      }
   }
   
   void
   DriverManager_t::update()
   {
      if ( mDriver )
      {
         mDriver->update();
      }
   }
}
