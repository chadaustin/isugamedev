/*******************************************************************************
 *
 * Copyright (c) 2001 Kevin Meinert, Ben Scott.
 *
 * -----------------------------------------------------------------------------
 * File:          $RCSfile: GlutDriver.cpp,v $
 * Last modified: $Date: 2002-01-30 04:51:47 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------------------
 *
 *******************************************************************************
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA.
 *
 ******************************************************************************/
#include "GlutDriver.h"
#include "GameKernel.h"
#include "GameInput.h"

// init the glut driver instance pointer to NULL
GlutDriver* GlutDriver::sDriver = NULL;

//------------------------------------------------------------------------------

GlutDriver::GlutDriver()
   : mCurrentContext( 0 ), mMainWin_ContextID( 0 ), mIsStarted( false )
{
   // because of glut's callback scheme we need to be able to get a pointer to
   // the current GLUTDriver instance.
   sDriver = this;
}
//------------------------------------------------------------------------------

GlutDriver::~GlutDriver()
{
}

//------------------------------------------------------------------------------

bool
GlutDriver::startup()
{
   // Set the window position
   int width, height;
   getWindowSize( width, height );
   if ( width == 0 || height == 0 )
   {
      width = 320; height = 240;
   }
   // Set the window title
   if ( name() == "" )
   {
      setName( "OpenGL" );
   }


   ::glutInitWindowSize( width, height );
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

   int x;
   for ( x = 0; x < GameKernel::instance().applications().size(); ++x )
   {
      assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
      GameInput::instance().keyboard().update();
      GameInput::instance().mouse().update();
      GameKernel::instance().applications()[x]->OnPreFrame();
      GameKernel::instance().applications()[x]->OnIntraFrame();
      GameKernel::instance().applications()[x]->OnPostFrame();
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

      // init each application
      int x;
      for ( x = 0; x < GameKernel::instance().applications().size(); ++x )
      {
         assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
         GameKernel::instance().applications()[x]->OnContextInit( );
      }
   }
}

/**
 * This is called when the window needs to redraw.
 */
void
GlutDriver::OnRedisplay()
{
   sDriver->initCurrentContext();

   // draw each application
   int x;
   for ( x = 0; x < GameKernel::instance().applications().size(); ++x )
   {
      assert( GameKernel::instance().applications()[x] != NULL && "you registered a NULL application" );
      GameKernel::instance().applications()[x]->OnContextDraw( sDriver->mCurrentContext );
   }

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
   GameInput::instance().keyboard().queue().enqueue( (Keyboard::Key)(int)k );

   // ignore case
   if ('a' <= k && k <= 'z')
   {
      k -= ('a' - 'A');
   }

   const DigitalInput::BinaryState state = DigitalInput::ON;
   GameInput::instance().keyboard().button( k ).setBinaryState( state );
}

//------------------------------------------------------------------------------

/**
 * This is called on a Up Keypress.
 */
void
GlutDriver::OnKeyboardUp( unsigned char k, int x, int y )
{
   GameInput::instance().keyboard().queue().enqueue( (Keyboard::Key)(int)k );

   if ('a' <= k && k <= 'z')
   {
      k -= ('a' - 'A');
   }

   const DigitalInput::BinaryState state = DigitalInput::OFF;
   GameInput::instance().keyboard().button( k ).setBinaryState( state );
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
   keyboard.queue().enqueue( key );
}

//------------------------------------------------------------------------------

/**
 * This is called on a Down Keypress.
 */
void
GlutDriver::OnSpecialKeyboardDown( int k, int x, int y )
{
   keyboardEvent( true, k, GameInput::instance().keyboard() );
}

//------------------------------------------------------------------------------

/**
 * This is called on an Up Keypress.
 */
void
GlutDriver::OnSpecialKeyboardUp( int k, int x, int y )
{
   keyboardEvent( false, k, GameInput::instance().keyboard() );
}


//------------------------------------------------------------------------------

/**
 * This is called when the mouse changes position.
 */
void
GlutDriver::OnMousePos( int x, int y )
{
   GameInput::instance().mouse().setPosition( x, y );
}

//------------------------------------------------------------------------------

/**
 * This is called when the mouse is clicked.
 */
void
GlutDriver::OnMouseClick( int button, int state, int x, int y )
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
