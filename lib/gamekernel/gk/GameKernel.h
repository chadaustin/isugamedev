#ifndef GAME_KERNEL
#define GAME_KERNEL

#include <vector>
#include <GL/glut.h>                   // gl utility library

#include "ContextData.h"
#include "Singleton.h"
#include "GameApp.h"      // the base application type
#include "GameInput.h"

class GameKernel : public kev::Singleton<GameKernel>
{
public:
   GameKernel();

   virtual void startup();
   virtual void shutdown();
   
   virtual void warpMouse( int x, int y );
   virtual void showMouse( bool show );
   
   /* go fullscreen
    */
   virtual void fullscreen( int ctx = 0 );
   
   /* get the window size */
   virtual void getWindowSize( int& width, int& height, int ctx = 0 );

   /* for resize of the window
    * i.e. use this to restore after a full screen
    *      use this to init the window size in OnAppInit
    */
   virtual void setWindowSize( int width, int height, int ctx = 0 );
   
   virtual void setName( const std::string& name );
   
   virtual const std::string& name() const;
   
   std::vector<GameApp*>& applications();
      
private:
   int mWidth, mHeight;
   std::string mName;
   int currentContext; //only one context for now...
   int mainWin_contextID; // ID of the main (first) window
   int mIsStarted;
   
   ///////////////////////////////////////////////////////////////////
   class DefaultFalseBool
   {
   private:
      bool _flag;
   public:
      DefaultFalseBool() : _flag(false) {}
      DefaultFalseBool(const bool& flag) : _flag(flag) {}
      inline bool& truth() { return _flag; }
      inline const bool& truth() const { return _flag; }
   };
   ContextData<GameKernel::DefaultFalseBool> oneTimeOnly;

   static void OnIdle();
   static void OnRedisplay();
   static void OnReshape(int w, int h);
   static void OnKeyboardDown(unsigned char k, int x, int y);
   static void OnKeyboardUp(unsigned char k, int x, int y);
   static void keyboardEvent( const bool& isdown, const int& k, Keyboard& keyboard );
   static void OnSpecialKeyboardDown(int k, int x, int y);
   static void OnSpecialKeyboardUp(int k, int x, int y);
   static void OnMousePos( int x, int y );
   static void OnMouseClick( int button, int state, int x, int y );
   static void postredisplay();
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
