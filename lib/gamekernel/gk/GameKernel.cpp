#include "GameKernel.h"

   GameKernel::GameKernel() : currentContext( 0 ), mainWin_contextID( 0 ), 
                              mIsStarted( false )
   {
   }

   void GameKernel::warpMouse( int x, int y )
   {
      glutWarpPointer( x, y );
   }   
   void GameKernel::showMouse( bool show )
   {
      if (show)
         ::glutSetCursor( GLUT_CURSOR_CROSSHAIR );
      else
         ::glutSetCursor( GLUT_CURSOR_NONE );
   }   
   
   /* go fullscreen
    */
   void GameKernel::fullscreen( int ctx = 0 )
   {
      ::glutFullScreen();
   }
   
   /* get the window size */
   void GameKernel::getWindowSize( int& width, int& height, int ctx = 0 )
   {
      width = mWidth;
      height = mHeight;
   }
   /* for resize of the window
    * i.e. use this to restore after a full screen
    *      use this to init the window size in OnAppInit
    */
   void GameKernel::setWindowSize( int width, int height, int ctx = 0 )
   {
      if (mIsStarted)
         ::glutReshapeWindow( width, height );
      
      mWidth = width;
      mHeight = height;
   }
   
   void GameKernel::setName( const std::string& name )
   {
      mName = name;
   }
   
   const std::string& GameKernel::name() const
   {
      return mName;
   }
   
   std::vector<GameApp*>& GameKernel::applications()
   {
      static std::vector<GameApp*> registered_applications;
      return registered_applications;
   }
   
///////////////////////////////////////////////////////////////////////////

   
   void GameKernel::postredisplay()
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
   
   void GameKernel::OnIdle()
   {
      postredisplay();
        
      int x;
      for (x = 0; x < GameKernel::instance().applications().size(); ++x)
      {
         assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
         GameInput::instance().keyboard().update();
         GameInput::instance().mouse().update();
         GameKernel::instance().applications()[x]->OnPreFrame();
         GameKernel::instance().applications()[x]->OnIntraFrame();
         GameKernel::instance().applications()[x]->OnPostFrame();
      }
   }

   //////////////////////////////////////////////////
   // This is called when the window needs to redraw  
   //////////////////////////////////////////////////
   void GameKernel::OnRedisplay() 
   { 
      // Initialize the context once and only once for every opengl window.
      bool hasInitialized = GameKernel::instance().oneTimeOnly( GameKernel::instance().currentContext ).truth();
      if (hasInitialized == false)
      {
         GameKernel::instance().oneTimeOnly( GameKernel::instance().currentContext ).truth() = true;

         // init each application
         int x;
         for (x = 0; x < GameKernel::instance().applications().size(); ++x)
         {
            assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
            GameKernel::instance().applications()[x]->OnContextInit( );
         }
         
      }

      // draw each application
      int x;
      for (x = 0; x < GameKernel::instance().applications().size(); ++x)
      {
         assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
         GameKernel::instance().applications()[x]->OnContextDraw( GameKernel::instance().currentContext );
      }

      glutSwapBuffers();
   }

   

   /////////////////////////////////////////////
   // This is called on a Resize of the window
   /////////////////////////////////////////////
   void GameKernel::OnReshape(int w, int h) 
   { 
      GameKernel::instance().mWidth = w;
      GameKernel::instance().mHeight = h;
      postredisplay();
   }

   ////////////////////////////////
   // This is called on a Down Keypress        
   ////////////////////////////////
   void GameKernel::OnKeyboardDown(unsigned char k, int x, int y) 
   { 
      if ('a' <= k && k <= 'z')
         k -= ('a' - 'A');

      const DigitalInput::BinaryState state = DigitalInput::ON;
      GameInput::instance().keyboard().button( k ).setBinaryState( state );
      GameInput::instance().keyboard().queue().enqueue( (Keyboard::Key)(int)k );
   }

   ////////////////////////////////
   // This is called on a Up Keypress        
   ////////////////////////////////
   void GameKernel::OnKeyboardUp(unsigned char k, int x, int y) 
   { 
      if ('a' <= k && k <= 'z')
         k -= ('a' - 'A');
      
      const DigitalInput::BinaryState state = DigitalInput::OFF;
      GameInput::instance().keyboard().button( k ).setBinaryState( state );
      GameInput::instance().keyboard().queue().enqueue( (Keyboard::Key)(int)k );
   }

   
   // set Keyboard with the keypress event
   void GameKernel::keyboardEvent( const bool& isdown, const int& k, Keyboard& keyboard )
   {
      DigitalInput::BinaryState state;
      if (isdown)
         state = DigitalInput::ON;
      else
         state = DigitalInput::OFF;
      
      Keyboard::Key key;
      switch (k)
      {
         case GLUT_KEY_UP: keyboard.button( key = Keyboard::UPARROW ).setBinaryState( state ); break;
         case GLUT_KEY_LEFT: keyboard.button( key = Keyboard::LEFTARROW ).setBinaryState( state ); break;
         case GLUT_KEY_DOWN: keyboard.button( key = Keyboard::DOWNARROW ).setBinaryState( state ); break;
         case GLUT_KEY_RIGHT: keyboard.button( key = Keyboard::RIGHTARROW ).setBinaryState( state ); break;
         case GLUT_KEY_F1: keyboard.button( key = Keyboard::F1 ).setBinaryState( state ); break;
         case GLUT_KEY_F2: keyboard.button( key = Keyboard::F2 ).setBinaryState( state ); break;
         case GLUT_KEY_F3: keyboard.button( key = Keyboard::F3 ).setBinaryState( state ); break;
         case GLUT_KEY_F4: keyboard.button( key = Keyboard::F4 ).setBinaryState( state ); break;
         case GLUT_KEY_F5: keyboard.button( key = Keyboard::F5 ).setBinaryState( state ); break;
         case GLUT_KEY_F6: keyboard.button( key = Keyboard::F6 ).setBinaryState( state ); break;
         case GLUT_KEY_F7: keyboard.button( key = Keyboard::F7 ).setBinaryState( state ); break;
         case GLUT_KEY_F8: keyboard.button( key = Keyboard::F8 ).setBinaryState( state ); break;
         case GLUT_KEY_F9: keyboard.button( key = key = Keyboard::F9 ).setBinaryState( state ); break;
         case GLUT_KEY_F10: keyboard.button( key = Keyboard::F10 ).setBinaryState( state ); break;
         case GLUT_KEY_F11: keyboard.button( key = Keyboard::F11 ).setBinaryState( state ); break;
         case GLUT_KEY_F12: keyboard.button( key = Keyboard::F12 ).setBinaryState( state ); break;

         case GLUT_KEY_PAGE_UP: keyboard.button( key = Keyboard::PAGEUP ).setBinaryState( state ); break;
         case GLUT_KEY_PAGE_DOWN: keyboard.button( key = Keyboard::PAGEDOWN ).setBinaryState( state ); break;
         case GLUT_KEY_HOME: keyboard.button( key = Keyboard::HOME ).setBinaryState( state ); break;
         case GLUT_KEY_END: keyboard.button( key = Keyboard::END ).setBinaryState( state ); break;
         case GLUT_KEY_INSERT: keyboard.button( key = Keyboard::INSERT ).setBinaryState( state ); break;
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
   void GameKernel::OnSpecialKeyboardDown(int k, int x, int y) 
   {
      keyboardEvent( true, k, GameInput::instance().keyboard() );
   }

   ////////////////////////////////
   // This is called on a Up Keypress        
   ////////////////////////////////
   void GameKernel::OnSpecialKeyboardUp(int k, int x, int y) 
   { 
      keyboardEvent( false, k, GameInput::instance().keyboard() );
   }

   ////////////////////////////////
   // This is called when mouse changes position
   ////////////////////////////////
   void GameKernel::OnMousePos( int x, int y ) 
   { 
      GameInput::instance().mouse().setPosition( x, y );
   }

   ////////////////////////////////
   // This is called when mouse clicks
   ////////////////////////////////
   void GameKernel::OnMouseClick( int button, int state, int x, int y ) 
   {  
       int keyboardModifier = glutGetModifiers();

       Mouse::Button b;
       DigitalInput::BinaryState binaryState;

       switch(button)
       {
	   case GLUT_LEFT_BUTTON: b = Mouse::LEFT; break;
	   case GLUT_MIDDLE_BUTTON: b = Mouse::MIDDLE; break;
	   case GLUT_RIGHT_BUTTON: b = Mouse::RIGHT; break;
	   default: assert(false);
       }

       switch(state)
       {
	   case GLUT_DOWN: binaryState = DigitalInput::ON; break;
	   case GLUT_UP: binaryState = DigitalInput::OFF;  break;
	   default: assert(false);
       }

       // Set the mousebutton state and the mouse position
       GameInput::instance().mouse().button( b ).setBinaryState( binaryState );
       GameInput::instance().mouse().setPosition( x, y );
   }


void GameKernel::startup()
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
      ::glutDisplayFunc( OnRedisplay );

         ::glutReshapeFunc( OnReshape );
         ::glutIdleFunc( OnIdle );

         // keyboard callback functions.
         ::glutKeyboardFunc( OnKeyboardDown );
         ::glutKeyboardUpFunc( OnKeyboardUp );
         ::glutSpecialFunc( OnSpecialKeyboardDown );
         ::glutSpecialUpFunc( OnSpecialKeyboardUp );

         // mouse callback functions...
         ::glutMouseFunc( OnMouseClick );
         ::glutMotionFunc( OnMousePos );
         ::glutPassiveMotionFunc( OnMousePos );


      // don't call the keyboard callback repeatedly when holding down a key.
      // (use edge triggering, like the mouse)
      ::glutIgnoreKeyRepeat( 1 );

      mIsStarted = true;
      
   // Sit and spin.
   ::glutMainLoop();
}   

void GameKernel::shutdown()
{
   mIsStarted = false;
   exit( 0 );
}



