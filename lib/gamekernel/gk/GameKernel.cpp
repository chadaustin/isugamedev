#include "GameKernel.h"

GameKernel::GameKernel()
   : mDriver( NULL )
{
}

void GameKernel::warpMouse( int x, int y )
{
   mDriver->warpMouse( x, y );
}

void GameKernel::showMouse( bool show )
{
   mDriver->showMouse( show );
}

/* go fullscreen
 */
void GameKernel::fullscreen( int ctx = 0 )
{
   mDriver->fullscreen();
}

/* get the window size */
void GameKernel::getWindowSize( int& width, int& height, int ctx = 0 )
{
   mDriver->getWindowSize( width, height, ctx );
}
/* for resize of the window
 * i.e. use this to restore after a full screen
 *      use this to init the window size in OnAppInit
 */
void GameKernel::setWindowSize( int width, int height, int ctx = 0 )
{
   mDriver->setWindowSize( width, height, ctx );
}

void GameKernel::setName( const std::string& name )
{
   mDriver->setName( name );
}

const std::string& GameKernel::name() const
{
   return mDriver->name();
}

std::vector<GameApp*>& GameKernel::applications()
{
   static std::vector<GameApp*> registered_applications;
   return registered_applications;
}

bool GameKernel::startup( SystemDriver* driver )
{
   assert( (driver != NULL) && "you must pass in a valid system driver!" );
   assert( GameKernel::instance().applications().size() > 0 && "you must register at least one application" );

   // keep a copy of our system driver
   mDriver = driver;

   //Initialize all registered applications, do this before initing glut, in case app
   // needs to set window position and name.
   int x;
   for (x = 0; x < GameKernel::instance().applications().size(); ++x)
   {
      assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
      GameKernel::instance().applications()[x]->OnAppInit();
   }

   return mDriver->startup();
}

void GameKernel::shutdown()
{
   mDriver->shutdown();
   delete mDriver;
   mDriver = NULL;
}



