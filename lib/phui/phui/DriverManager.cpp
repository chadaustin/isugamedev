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
