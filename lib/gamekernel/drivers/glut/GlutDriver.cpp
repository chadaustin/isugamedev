
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
// File:          $RCSfile: GlutDriver.cpp,v $
// Date modified: $Date: 2002-03-19 01:59:21 $
// Version:       $Revision: 1.11 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "GlutDriver.h"
#include <xdl.h>
#include <GL/glut.h>

// Only compile in the create/destroy code if we're building a library
#ifdef XDL_BUILD_DLL
extern "C" XDL_FUNC gk::ISystemDriver*
createSystemDriver()
{
   return new gk::GlutDriver();
}
#endif // XDL_BUILD_DLL

namespace gk {

// init the glut driver instance pointer to NULL
GlutDriver* GlutDriver::sDriver = NULL;

//------------------------------------------------------------------------------

GlutDriver::GlutDriver()
   : mWidth( 320 ), mHeight( 240 ), mCurrentContext( 0 ),
     mMainWin_ContextID( 0 ), mIsStarted( false ), mMouse( NULL ),
     mKeyboard( NULL ), mJoystick( NULL ), mKernel( NULL )
{
   // because of glut's callback scheme we need to be able to get a pointer to
   // the current GLUTDriver instance.
   assert( sDriver == NULL && "initializing a second instance of GlutDriver" );
   sDriver = this;
}
//------------------------------------------------------------------------------

GlutDriver::~GlutDriver()
{
}

//------------------------------------------------------------------------------

bool
GlutDriver::init( IGameKernel* kernel )
{
   assert( kernel != NULL );
   mKernel = kernel;

   // Set the window title
   if ( name() == "" )
   {
      setName( "OpenGL" );
   }


   ::glutInitWindowSize( mWidth, mHeight );
   int argc = 1;
   char* argv[] = { "GameKernel", NULL };
   ::glutInit( &argc, argv );
   ::glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
   mMainWin_ContextID = ::glutCreateWindow( name().c_str() );

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

   // register the our devices with the input manager
   mMouse = new DeviceHandle<Mouse>( "Mouse", mKernel );
   mKeyboard = new DeviceHandle<Keyboard>( "Keyboard", mKernel );

   // check if we've got access to a joystick
   if ( glutDeviceGet( GLUT_HAS_JOYSTICK ) )
   {
      // register glut callback. a poll interval of -1 is used to tell glut that
      // we want to manually poll the joystick using glutForceJoystickFunc()
      // from our idle callback.
      ::glutJoystickFunc( OnJoystick, -1 );

      // add a joystick device
      int numButtons = glutGet( GLUT_JOYSTICK_BUTTONS );
      int numAxes = glutGet( GLUT_JOYSTICK_AXES );
      mJoystick = new DeviceHandle<Joystick>( "Joystick", mKernel );
      mJoystick->getDevice()->setNumButtons( numButtons );
      mJoystick->getDevice()->setNumAxes( numAxes );
   }

   return true;
}

//----------------------------------------------------------------------------//

bool
GlutDriver::run()
{
   mIsStarted = true;

   // Sit and spin.
   ::glutMainLoop();

   return true;
}

//----------------------------------------------------------------------------//

void
GlutDriver::shutdown()
{
   mIsStarted = false;

   // remove our mouse device
   if ( mMouse != NULL )
   {
      delete mMouse;
      mMouse = NULL;
   }

   // remove our keyboard device
   if ( mKeyboard != NULL )
   {
      delete mKeyboard;
      mKeyboard = NULL;
   }

   // remove our joystick device
   if ( mJoystick != NULL )
   {
      delete mJoystick;
      mJoystick = NULL;
   }

   // glut can be so stupid sometimes ...
   exit( 0 );
}

//------------------------------------------------------------------------------

void
GlutDriver::warpMouse( int x, int y )
{
   glutWarpPointer( x, y );
}

//------------------------------------------------------------------------------

void
GlutDriver::showMouse( bool show )
{
   if (show)
      ::glutSetCursor( GLUT_CURSOR_CROSSHAIR );
   else
      ::glutSetCursor( GLUT_CURSOR_NONE );
}

//------------------------------------------------------------------------------

void
GlutDriver::fullscreen( int ctx )
{
   std::cout << "Going fullscreen" << std::endl;
   ::glutFullScreen();
}

//------------------------------------------------------------------------------

void
GlutDriver::getWindowSize( int& width, int& height, int ctx )
{
   width = mWidth;
   height = mHeight;
}

//------------------------------------------------------------------------------

void
GlutDriver::setWindowSize( int width, int height, int ctx )
{
   std::cout << "Resizing window to " << width << ", " << height << std::endl;

   if (mIsStarted)
      ::glutReshapeWindow( width, height );

   mWidth = width;
   mHeight = height;
}

//------------------------------------------------------------------------------

void
GlutDriver::setName( const std::string& name )
{
   mName = name;
}

//------------------------------------------------------------------------------

const std::string&
GlutDriver::name() const
{
   return mName;
}

//------------------------------------------------------------------------------

void
GlutDriver::OnIdle()
{
   postRedisplay();

   IGameKernel* kernel = sDriver->mKernel;
   IGameApp* app = kernel->getApp();

   // do an app frame
   assert( app != NULL && "you can't run a NULL application" );
   kernel->getInput()->update();
   app->onPreFrame();
   app->onIntraFrame();
   app->onPostFrame();

   // force a poll on the joystick
   if ( sDriver->mJoystick != NULL )
   {
      glutForceJoystickFunc();
   }
}

//------------------------------------------------------------------------------

void
GlutDriver::initCurrentContext()
{
   // Initialize the context once and only once for every opengl window.
   bool hasInitialized = oneTimeOnly( mCurrentContext ).truth();
   if ( hasInitialized == false )
   {
      oneTimeOnly( mCurrentContext ).truth() = true;

      // init the app
      assert( mKernel->getApp() != NULL && "you can't run a NULL application" );
      mKernel->getApp()->onContextInit();
   }
}

/**
 * This is called when the window needs to redraw.
 */
void
GlutDriver::OnRedisplay()
{
   sDriver->initCurrentContext();

   // draw the app
   IGameKernel* kernel = sDriver->mKernel;
   assert( kernel->getApp() != NULL && "you can't run a NULL application" );
   kernel->getApp()->onContextDraw( sDriver->mCurrentContext );

   glutSwapBuffers();
}

//------------------------------------------------------------------------------

void
GlutDriver::OnReshape( int w, int h )
{
   sDriver->mWidth = w;
   sDriver->mHeight = h;
   postRedisplay();
}

//------------------------------------------------------------------------------

/**
 * This is called on a Down Keypress.
 */
void
GlutDriver::OnKeyboardDown( unsigned char k, int x, int y )
{
   Keyboard* keyboard = sDriver->mKeyboard->getDevice();
   keyboard->queue().push_back( (Keyboard::Key)(int)k );

   // ignore case
   if ('a' <= k && k <= 'z')
   {
      k -= ('a' - 'A');
   }

   const DigitalInput::BinaryState state = DigitalInput::ON;
   keyboard->button( k ).setBinaryState( state );
}

//------------------------------------------------------------------------------

/**
 * This is called on a Up Keypress.
 */
void
GlutDriver::OnKeyboardUp( unsigned char k, int x, int y )
{
   //GameInput::instance().keyboard().queue().push_back( (Keyboard::Key)(int)k );

   if ('a' <= k && k <= 'z')
   {
      k -= ('a' - 'A');
   }

   const DigitalInput::BinaryState state = DigitalInput::OFF;
   Keyboard* keyboard = sDriver->mKeyboard->getDevice();
   keyboard->button( k ).setBinaryState( state );
}

//------------------------------------------------------------------------------

/**
 * Set Keyboard with the keypress event.
 */
void
GlutDriver::keyboardEvent( const bool& isdown, const int& k, Keyboard& keyboard )
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
   //keyboard.queue().push_back( key );
}

//------------------------------------------------------------------------------

/**
 * This is called on a Down Keypress.
 */
void
GlutDriver::OnSpecialKeyboardDown( int k, int x, int y )
{
   keyboardEvent( true, k, *(sDriver->mKeyboard->getDevice()) );
}

//------------------------------------------------------------------------------

/**
 * This is called on an Up Keypress.
 */
void
GlutDriver::OnSpecialKeyboardUp( int k, int x, int y )
{
   keyboardEvent( false, k, *(sDriver->mKeyboard->getDevice()) );
}


//------------------------------------------------------------------------------

/**
 * This is called when the mouse changes position.
 */
void
GlutDriver::OnMousePos( int x, int y )
{
   Mouse* mouse = sDriver->mMouse->getDevice();

   int width, height;
   sDriver->mKernel->getWindowSize( width, height );
   float normX = ((float)x/(float)width)*2.0f - 1.0f;
   float normY = ((float)y/(float)height)*2.0f - 1.0f;

   mouse->axis( 0 ).setData( normX );
   mouse->axis( 1 ).setData( normY );
}

//------------------------------------------------------------------------------

/**
 * This is called when the mouse is clicked.
 */
void
GlutDriver::OnMouseClick( int button, int state, int x, int y )
{
//   int keyboardModifier = glutGetModifiers();

   Mouse::Button b;
   DigitalInput::BinaryState binaryState;

   switch(button)
   {
   case GLUT_LEFT_BUTTON: b = Mouse::LEFT; break;
   case GLUT_MIDDLE_BUTTON: b = Mouse::MIDDLE; break;
   case GLUT_RIGHT_BUTTON: b = Mouse::RIGHT; break;
   default: b = Mouse::ROLL; break;
   }

   switch(state)
   {
   case GLUT_DOWN: binaryState = DigitalInput::ON; break;
   case GLUT_UP: binaryState = DigitalInput::OFF;  break;
   default: break;
   }

   // Set the mousebutton state and the mouse position
   Mouse* mouse = sDriver->mMouse->getDevice();
   mouse->button( b ).setBinaryState( binaryState );

   int width, height;
   sDriver->mKernel->getWindowSize( width, height );
   float normX = ((float)x/(float)width)*2.0f - 1.0f;
   float normY = ((float)y/(float)height)*2.0f - 1.0f;

   mouse->axis( 0 ).setData( normX );
   mouse->axis( 1 ).setData( normY );
}

//------------------------------------------------------------------------------

/**
 * This is called every time the joystick is polled by glut. Now why the hell
 * did they suddenly decide to poll the joystick and have everything else event
 * based?
 */
void
GlutDriver::OnJoystick( unsigned int buttonMask, int x, int y, int z )
{
   // check if we actually have a joystick device. this should NEVER happen if
   // we're in a glut joystick callback, but just in case ...
   if ( sDriver->mJoystick == NULL )
   {
      return;
   }
   Joystick* joy = sDriver->mJoystick->getDevice();

   // check the buttons
   int numButtons = joy->numButtons();
   // glut only supports a max of 32 buttons
   int maxButtons = ( numButtons > 32 ) ? 32 : numButtons;
   for ( int i = 0; i < maxButtons; ++i )
   {
      // update the state of the current button
      unsigned long mask = 0x00000001 << i;
      joy->button( i ).setBinaryState(
            ( buttonMask & mask ) ?
               DigitalInput::ON :
               DigitalInput::OFF
      );
   }

   // check the axes
   int numAxes = joy->numAxes();
   if ( numAxes > 0 )
   {
      // normalize the data from the axis to [-1,1]
      float normX = ((float)x / 1000.0f)*2.0f - 1.0f;
      joy->axis( 0 ).setData( normX );
   }
   if ( numAxes > 1 )
   {
      // normalize the data from the axis to [-1,1]
      float normY = ((float)y / 1000.0f)*2.0f - 1.0f;
      joy->axis( 1 ).setData( normY );
   }
   if ( numAxes > 2 )
   {
      // normalize the data from the axis to [-1,1]
      float normZ = ((float)z / 1000.0f)*2.0f - 1.0f;
      joy->axis( 2 ).setData( normZ );
   }
}

//------------------------------------------------------------------------------

void
GlutDriver::postRedisplay()
{
   // According to the GLUT specification, the current window is undefined
   // during an idle callback.  So we need to explicitly change it if necessary.
   if ( glutGetWindow() != sDriver->mMainWin_ContextID )
   {
      glutSetWindow( sDriver->mMainWin_ContextID );
   }

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
}

//------------------------------------------------------------------------------

} // namespace gk
