
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
// File:          $RCSfile: main.cpp,v $
// Date modified: $Date: 2002-05-14 15:28:47 $
// Version:       $Revision: 1.6 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////

#include <gk/gk.h>
#include <GL/gl.h>
#include <GL/glu.h>

/** a very simple application
 *  as you develop your application, you'll probably want to write
 *  it in components used by this low level app object.
 *  otherwise, this class could get pretty huge pretty quickly! :)
 *
 *  @see GameApp
 */
class GkSimpleApp : public gk::AbstractGameApp
{
public:
   GkSimpleApp()
   {
   }
   
   virtual void onAppInit( gk::IGameKernel* kernel )
   {
      mKernel = kernel;
      mKernel->setName( "Simple" );
      mQuitButton.init( "Quit", mKernel );
      mFullscreenButton.init( "Fullscreen", mKernel );
   }

   virtual void onContextInit()
   {
      mKernel->setWindowSize( 640, 480 );
      mFullscreen = false;
   }

   /** make opengl calls here.
    *  these calls are usually driven by the game state data that was 
    *  updated by OnPostFrame, use opengl to draw
    */
   virtual void onDraw( int context = 0 )
   {
      // get the window params...
      int width, height;
      mKernel->getWindowSize( width, height );
      ::glViewport( 0, 0, width, height );
      
      ::glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
      ::glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
      ::glEnable( GL_DEPTH_TEST );

      // enable alpha blending..
      ::glEnable( GL_BLEND );
      ::glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 

      // set up the projection matrix in the proj stack
      ::glMatrixMode( GL_PROJECTION );
         ::glLoadIdentity();                     
         ::gluPerspective( 100.0f, (float)width / (float)height, 0.01f, 1000.0f );

      // initialize the other matrix stack we'll use to transform models
      ::glMatrixMode( GL_MODELVIEW );
         ::glLoadIdentity();      
         
      // draw camera (camera xforms affect model, not you!)
      ::glRotatef( 45.0f, 1.0f, 0.0f, 0.0f ); // 2.) tilt board up toward us
      ::glTranslatef( 0.0f, -4.0f, -10.0f );    // 1.) push board down and out
       
      // draw your game components/models here...
      ::glBegin( GL_TRIANGLE_STRIP );
         ::glColor3f( 1.0f, 0.3f, 0.2f );
         ::glVertex3f( -10.0f, 0.0f, -10.0f );
         ::glColor3f( 0.3f, 1.0f, 0.2f );
         ::glVertex3f( -10.0f, 0.0f,  10.0f );
         ::glColor3f( 0.3f, 0.2f, 1.0f );
         ::glVertex3f(  10.0f, 0.0f, -10.0f );
         ::glColor3f( 0.0f, 0.6f, 0.7f );
         ::glVertex3f(  10.0f, 0.0f,  10.0f );
      ::glEnd();
   }

   /** update your game state data.
    * do your data (non opengl) calculations here 
    */
   virtual void onPreUpdate()
   {
      if (mQuitButton.getDigitalData() == gk::DigitalInput::DOWN)
      {
         mKernel->shutdown();
      }
      
      if (mFullscreenButton.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         if (mFullscreen)
            mKernel->setWindowSize( 640, 480 );
         else
            mKernel->fullscreen();
         mFullscreen = !mFullscreen;
      }
   }

public:
   gk::DigitalInterface mFullscreenButton, mQuitButton;
   bool mFullscreen;
   gk::IGameKernel* mKernel;
};

int main( int argc, char *argv[] )
{
   std::cout<<"Running GameKernel v"<<gk::getVersion()<<std::endl;

   // let our app loose in the Game Kernel
   gk::AbstractGameApp* app = new GkSimpleApp();   
   gk::IGameKernel* kernel = gk::createGameKernel( app );
   if (kernel->config( "config.xml" ))
   {
      kernel->run();
      return 0;
   }
   else
   {
      std::cerr << "Couldn't load config.xml" << std::endl;
   }
   return 1;
}
