#ifndef GAME_KERNEL
#define GAME_KERNEL

#include <vector>
#include <GL/glut.h>                   // gl utility library
#include <ContextData.h>
#include "GameApp.h"      // the base application type
#include "Singleton.h"

class GameKernel : public kev::Singleton<GameKernel>
{
public:
   GameKernel() : currentContext( 0 ), mainWin_contextID( 0 ), mIsStarted( false )
   {
   }

   virtual void startup();
   virtual void shutdown();
   
   virtual void warpMouse( int x, int y )
   {
      glutWarpPointer( x, y );
   }   
   virtual void showMouse( bool show )
   {
      if (show)
         ::glutSetCursor( GLUT_CURSOR_CROSSHAIR );
      else
         ::glutSetCursor( GLUT_CURSOR_NONE );
   }   
   
   /* go fullscreen
    */
   virtual void fullscreen( int ctx = 0 )
   {
      ::glutFullScreen();
   }
   
   /* get the window size */
   virtual void getWindowSize( int& width, int& height, int ctx = 0 )
   {
      width = mWidth;
      height = mHeight;
   }
   /* for resize of the window
    * i.e. use this to restore after a full screen
    *      use this to init the window size in OnAppInit
    */
   virtual void setWindowSize( int width, int height, int ctx = 0 )
   {
      if (mIsStarted)
         ::glutReshapeWindow( width, height );
      
      mWidth = width;
      mHeight = height;
   }
   
   virtual void setName( const std::string& name )
   {
      mName = name;
   }
   
   virtual const std::string& name() const
   {
      return mName;
   }
   
   std::vector<GameApp*>& applications()
   {
      static std::vector<GameApp*> registered_applications;
      return registered_applications;
   }
      
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
   
   static void postredisplay()
   {
      // According to the GLUT specification, the current window is 
      // undefined during an idle callback.  So we need to explicitly change
      // it if necessary
      if ( glutGetWindow() != instance().mainWin_contextID ) 
      {
         glutSetWindow( instance().mainWin_contextID );  
      }

      // tell glut to call redisplay (which then calls OnRedisplay)
      glutPostRedisplay();
   }   
   
   static void OnIdle()
   {
      postredisplay();
        
      int x;
      for (x = 0; x < instance().applications().size(); ++x)
      {
         assert( instance().applications()[x] != NULL && "you registered a NULL application" );
         instance().applications()[x]->keyboard().updateEdgeStates();
         instance().applications()[x]->mouse().update();
         instance().applications()[x]->OnPreFrame();
         instance().applications()[x]->OnIntraFrame();
         instance().applications()[x]->OnPostFrame();
      }
   }

   //////////////////////////////////////////////////
   // This is called when the window needs to redraw  
   //////////////////////////////////////////////////
   static void OnRedisplay() 
   { 
      // Initialize the context once and only once for every opengl window.
      bool hasInitialized = instance().oneTimeOnly( instance().currentContext ).truth();
      if (hasInitialized == false)
      {
         instance().oneTimeOnly( instance().currentContext ).truth() = true;

         // init each application
         int x;
         for (x = 0; x < instance().applications().size(); ++x)
         {
            assert( instance().applications()[x] != NULL && "you registered a NULL application" );
            instance().applications()[x]->OnContextInit( );
         }
         
      }

      // draw each application
      int x;
      for (x = 0; x < instance().applications().size(); ++x)
      {
         assert( instance().applications()[x] != NULL && "you registered a NULL application" );
         instance().applications()[x]->OnContextDraw( instance().currentContext );
      }

      glutSwapBuffers();
   }

   

   /////////////////////////////////////////////
   // This is called on a Resize of the window
   /////////////////////////////////////////////
   static void OnReshape(int w, int h) 
   { 
      instance().mWidth = w;
      instance().mHeight = h;
      postredisplay();
   }

   ////////////////////////////////
   // This is called on a Down Keypress        
   ////////////////////////////////
   static void OnKeyboardDown(unsigned char k, int x, int y) 
   { 
      int a;
      for (a = 0; a < instance().applications().size(); ++a)
      {
         assert( instance().applications()[a] != NULL && "you registered a NULL application" );
         GameApp* app = instance().applications()[a];

         const Keyboard::BinaryState state = Keyboard::ON;
         app->keyboard().binaryState( k ) = state;
         app->keyboard().queue().enqueue( (Keyboard::Key)(int)k );
      }
   }

   ////////////////////////////////
   // This is called on a Up Keypress        
   ////////////////////////////////
   static void OnKeyboardUp(unsigned char k, int x, int y) 
   { 
      int a;
      for (a = 0; a < instance().applications().size(); ++a)
      {
         assert( instance().applications()[a] != NULL && "you registered a NULL application" );
         GameApp* app = instance().applications()[a];

         const Keyboard::BinaryState state = Keyboard::OFF;
         app->keyboard().binaryState( k ) = state;
         app->keyboard().queue().enqueue( (Keyboard::Key)(int)k );
      }
   }

   
   // set Keyboard with the keypress event
   static void keyboardEvent( const bool& isdown, const int& k, Keyboard& keyboard )
   {
      Keyboard::BinaryState state;
      if (isdown)
         state = Keyboard::ON;
      else
         state = Keyboard::OFF;
      
      Keyboard::Key key;
      switch (k)
      {
         case GLUT_KEY_UP: keyboard.binaryState( key = Keyboard::UPARROW ) = state; break;
         case GLUT_KEY_LEFT: keyboard.binaryState( key = Keyboard::LEFTARROW ) = state; break;
         case GLUT_KEY_DOWN: keyboard.binaryState( key = Keyboard::DOWNARROW ) = state; break;
         case GLUT_KEY_RIGHT: keyboard.binaryState( key = Keyboard::RIGHTARROW ) = state; break;
         case GLUT_KEY_F1: keyboard.binaryState( key = Keyboard::F1 ) = state; break;
         case GLUT_KEY_F2: keyboard.binaryState( key = Keyboard::F2 ) = state; break;
         case GLUT_KEY_F3: keyboard.binaryState( key = Keyboard::F3 ) = state; break;
         case GLUT_KEY_F4: keyboard.binaryState( key = Keyboard::F4 ) = state; break;
         case GLUT_KEY_F5: keyboard.binaryState( key = Keyboard::F5 ) = state; break;
         case GLUT_KEY_F6: keyboard.binaryState( key = Keyboard::F6 ) = state; break;
         case GLUT_KEY_F7: keyboard.binaryState( key = Keyboard::F7 ) = state; break;
         case GLUT_KEY_F8: keyboard.binaryState( key = Keyboard::F8 ) = state; break;
         case GLUT_KEY_F9: keyboard.binaryState( key = key = Keyboard::F9 ) = state; break;
         case GLUT_KEY_F10: keyboard.binaryState( key = Keyboard::F10 ) = state; break;
         case GLUT_KEY_F11: keyboard.binaryState( key = Keyboard::F11 ) = state; break;
         case GLUT_KEY_F12: keyboard.binaryState( key = Keyboard::F12 ) = state; break;

         case GLUT_KEY_PAGE_UP: keyboard.binaryState( key = Keyboard::PAGEUP ) = state; break;
         case GLUT_KEY_PAGE_DOWN: keyboard.binaryState( key = Keyboard::PAGEDOWN ) = state; break;
         case GLUT_KEY_HOME: keyboard.binaryState( key = Keyboard::HOME ) = state; break;
         case GLUT_KEY_END: keyboard.binaryState( key = Keyboard::END ) = state; break;
         case GLUT_KEY_INSERT: keyboard.binaryState( key = Keyboard::INSERT ) = state; break;
         default:
            std::cout<<"unrecognized key = "<<(int)k<<"\n"<<std::flush;
            return;
      }   
      //keyboard.updateEdgeStates();
      keyboard.queue().enqueue( key );
   }   
   
   ////////////////////////////////
   // This is called on a Down Keypress        
   ////////////////////////////////
   static void OnSpecialKeyboardDown(int k, int x, int y) 
   {
      int a;
      for (a = 0; a < instance().applications().size(); ++a)
      {
         assert( instance().applications()[a] != NULL && "you registered a NULL application" );
         GameApp* app = instance().applications()[a];
         keyboardEvent( true, k, app->keyboard() );
      }
   }

   ////////////////////////////////
   // This is called on a Up Keypress        
   ////////////////////////////////
   static void OnSpecialKeyboardUp(int k, int x, int y) 
   { 
      int a;
      for (a = 0; a < instance().applications().size(); ++a)
      {
         assert( instance().applications()[a] != NULL && "you registered a NULL application" );
         GameApp* app = instance().applications()[a];
         keyboardEvent( false, k, app->keyboard() );
      }
   }

   ////////////////////////////////
   // This is called when mouse changes position
   ////////////////////////////////
   static void OnMousePos( int x, int y ) 
   { 
      int a;
      for (a = 0; a < instance().applications().size(); ++a)
      {
         assert( instance().applications()[a] != NULL && "you registered a NULL application" );
         GameApp* app = instance().applications()[a];
         app->mouse().setPosition( x, y );
      }
   }

   ////////////////////////////////
   // This is called when mouse clicks
   ////////////////////////////////
   static void OnMouseClick( int button, int state, int x, int y ) 
   { 
      int i;
      for (i = 0; i < instance().applications().size(); ++i)
      {
         assert( instance().applications()[i] != NULL && "you registered a NULL application" );
         GameApp* app = instance().applications()[i];
         
         int keyboardModifier = glutGetModifiers();

          Mouse::Button b;
          Mouse::BinaryState binaryState;

          switch(button)
          {
	      case GLUT_LEFT_BUTTON: b = Mouse::LEFT; break;
	      case GLUT_MIDDLE_BUTTON: b = Mouse::MIDDLE; break;
	      case GLUT_RIGHT_BUTTON: b = Mouse::RIGHT; break;
	      default: assert(false);
          }

          switch(state)
          {
	      case GLUT_DOWN: binaryState = Mouse::ON; break;
	      case GLUT_UP: binaryState = Mouse::OFF;  break;
	      default: assert(false);
          }

          // Set the mousebutton state and the mouse position
          app->mouse().setState(b, binaryState);
          app->mouse().setPosition( x, y );
          //app->mouse().updateEdgeStates();

          //this->OnMouseEvent();
      }
   }
   
   
};

inline void GameKernel::startup()
{
   assert( GameKernel::instance().applications().size() > 0 && "you must register at least one application" );

   //Initialize all registered applications, do this before initing glut, in case app
   // needs to set window position and name.
   int x;
   for (x = 0; x < GameKernel::instance().applications().size(); ++x)
   {
      assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
      GameKernel::instance().applications()[x]->OnAppInit();
   }

   // Set the window position
   int width, height;
   GameKernel::instance().getWindowSize( width, height );
   if ( width == 0 || height == 0)
   {
      width = 320; height = 240;
   }   
   // Set the window title
   if ( GameKernel::instance().name() == "" )
   {
      GameKernel::instance().setName( "OpenGL" );
   }


   ::glutInitWindowSize( width, height );
   int argc = 1;
   char* argv[] = { "GameKernel" };
   ::glutInit( &argc, argv );
   ::glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
   GameKernel::instance().mainWin_contextID = ::glutCreateWindow( GameKernel::instance().name().c_str() );

      // display callbacks.
      ::glutDisplayFunc( GameKernel::OnRedisplay );

         ::glutReshapeFunc( GameKernel::OnReshape );
         ::glutIdleFunc( GameKernel::OnIdle );

         // keyboard callback functions.
         ::glutKeyboardFunc( GameKernel::OnKeyboardDown );
         ::glutKeyboardUpFunc( GameKernel::OnKeyboardUp );
         ::glutSpecialFunc( GameKernel::OnSpecialKeyboardDown );
         ::glutSpecialUpFunc( GameKernel::OnSpecialKeyboardUp );

         // mouse callback functions...
         ::glutMouseFunc( GameKernel::OnMouseClick );
         ::glutMotionFunc( GameKernel::OnMousePos );
         ::glutPassiveMotionFunc( GameKernel::OnMousePos );


      // don't call the keyboard callback repeatedly when holding down a key.
      // (use edge triggering, like the mouse)
      ::glutIgnoreKeyRepeat( 1 );

      mIsStarted = true;
      
   // Sit and spin.
   ::glutMainLoop();
}   

inline void GameKernel::shutdown()
{
   mIsStarted = false;
   exit( 0 );
}

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
