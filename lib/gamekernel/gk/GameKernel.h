#ifndef GAME_KERNEL
#define GAME_KERNEL

#include <vector>
#include <GL/glut.h>                   // gl utility library

#include "ContextData.h"
#include "Singleton.h"
#include "GameApp.h"      // the base application type
#include "GameInput.h"
#include "SystemDriver.h"

/**
 * Facade for all system driver interactions. The application should deal
 * directly with this singleton to avoid talking directly to a SystemDriver
 * implementation.
 */
class GameKernel : public kev::Singleton<GameKernel>
{
public:
   GameKernel();

   /**
    * Initializes and runs this kernel with the given system driver.
    *
    * @param driver     the driver that should underlie the kernel
    *
    * @return  true if successful, false otherwise
    */
   bool startup( SystemDriver* driver );
   void shutdown();

   void warpMouse( int x, int y );
   void showMouse( bool show );

   /* go fullscreen
    */
   void fullscreen( int ctx = 0 );

   /* get the window size */
   void getWindowSize( int& width, int& height, int ctx = 0 );

   /* for resize of the window
    * i.e. use this to restore after a full screen
    *      use this to init the window size in OnAppInit
    */
   void setWindowSize( int width, int height, int ctx = 0 );

   void setName( const std::string& name );

   const std::string& name() const;

   std::vector<GameApp*>& applications();

private:
   /**
    * This is the system driver implementation that runs our apps.
    */
   SystemDriver* mDriver;
};

// create an instance of this type to register your application
// delete it to unregister it.
template< class applicationType >
class GameKernelRegister
{
public:
   GameKernelRegister() : mApplication()
   {
      GameKernel::instance().applications().push_back( &mApplication );
      int size = GameKernel::instance().applications().size();
   }
   virtual ~GameKernelRegister()
   {

      std::vector<GameApp*>::iterator it;
      for (it = GameKernel::instance().applications().begin();
           it != GameKernel::instance().applications().end();
           ++it)
      {
         if (&mApplication == (*it))
         {
            GameKernel::instance().applications().erase( it );
            return;
         }
      }

      // if not found, then the list probably was deallocated
      // (because application exited)
      // whatever, there wont be any dangling memory anyway.
   }

   applicationType mApplication;
};

#endif
