#ifndef PHUI_DRIVER_MANAGER_H
#define PHUI_DRIVER_MANAGER_H

#include "Driver.h"
#include "Debug.h"
#include "Input.h"
#include "RootWidget.h"
#include <loki/FactoryGen.h>
#include <loki/Functor.h>
#include <loki/Singleton.h>
#include <loki/Typelist.h>
#include <string>
#include <vector>

namespace phui
{
   /**
    * Manages the phui low level drivers; this ensures that there is only one
    * driver instance around at once.  The libraries that phui currently uses 
    * for driver implementations all assume that they are only running one 
    * instance per application, so this manager is necessary to ensure that
    * the library is not misused.
    */
   class DriverManager_t
   {
   public:

      /**
       * Registers a new driver with the manager.
       *
       * @param   name     the name of the driver to register.
       * @param   creator  the function that creates the driver.
       */
      void registerDriver( const std::string& name,
            Loki::Functor< Driver*, TYPELIST_1( bool )> creator );

      /**
       * Returns a string containing all of the drivers that this 
       * manager supports.
       *
       * @return     a string containing all the names of the drivers that
       *             are support delimited by spaces.
       */
      const std::string getSupportedDrivers();

      /**
       * Sets the driver manager with the given driver.
       *
       * @param   driver      the name of the driver to use.
       * @param   standalone  run the driver in standalone mode or not?
       */
      void setDriver(const std::string& driver, bool standalone = true);

      // Driver interface functions; these are forwarded to the current driver
      // in use.
      
      void registerRoot(RootWidgetPtr root); 
      void onKeyDown(InputKey key);
      void onKeyUp(InputKey key);
      void onMouseDown(InputButton button, const Point& p);
      void onMouseUp(InputButton button, const Point& p);
      void onMouseMove(const Point& p);
      void start();
      void update();
      bool isStandalone();
      
      friend class Loki::SingletonHolder<DriverManager_t>;
      friend class Loki::CreateUsingNew<DriverManager_t>;
      friend class Loki::DefaultLifetime<DriverManager_t>;
      
   private:

      typedef Loki::FactoryGen< Driver, std::string, TYPELIST_1(bool) > DriverFactory;

      /// The driver that is currently in use.
      Driver*                             mDriver;

      /// The names of the drivers that this manager supports.
      std::vector<std::string>            mDriverNames;

      /// The factory that creates drivers.
      DriverFactory                       mDriverFactory;
      
      // Singleton's cannot be created, copied, destroyed, or assigned.
      DriverManager_t()
         : mDriver(0)
      {
      }

      DriverManager_t(const DriverManager_t& original);

      ~DriverManager_t()
      {
         
         delete mDriver;
         mDriver = 0;
      }

      DriverManager_t& operator=(const DriverManager_t& rhs);
   };

   typedef Loki::SingletonHolder<DriverManager_t> DriverManager;
}

#endif
