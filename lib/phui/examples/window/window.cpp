/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: window.cpp,v $
 * Date modified: $Date: 2002-02-24 06:21:12 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************** phui-cpr-end */

#include <GL/glut.h>
#include <phui/phui.h>

static int gWidth  = 640;
static int gHeight = 480;
static int mainWin_contextID;
static phui::RootWidget* gUI(NULL);

//-----------------------------------------------------------------------------

void OnRedisplay()
{
   glClearColor( 0, 0, 0, 1 );
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

   // setup projection
   glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( 80.0f, (float)gWidth / (float)gHeight, 0.01f, 1000.0f );

   // setup modelview
   glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();

   // draw a teapot
   glPushMatrix();
      glColor4f( 0,0,1,1 );
      glTranslatef( 0, 0, -50 );
      glutSolidTeapot( 25 );
   glPopMatrix();

   // draw a window
   gUI->draw();

   glutSwapBuffers();
}

void OnReshape( int width, int height )
{
   gWidth = width;
   gHeight = height;

   glViewport( 0, 0, gWidth, gHeight );
   gUI->setSize(width, height);
}

void OnIdle()
{
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != mainWin_contextID )
      glutSetWindow( mainWin_contextID );

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
}

void OnKeyboardDown( unsigned char key, int x, int y )
{
   // ESC or q
   if ( key == 27 || key == 'q' )
   {
      exit(0);
   }
}

int main( int argc, char** argv )
{
   glutInitWindowSize( gWidth, gHeight );
   glutInit( &argc, argv );
   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
   mainWin_contextID = glutCreateWindow( "Window Example" );

   // callbacks
   glutDisplayFunc( OnRedisplay );
   glutReshapeFunc( OnReshape );
   glutIdleFunc( OnIdle );
   glutKeyboardFunc( OnKeyboardDown );

   gUI = phui::CreateRoot( gWidth, gHeight );
   phui::Window* wnd = new phui::Window();
   wnd->setPosition( 150, 75 );
   wnd->setSize( 300, 250 );
   phui::Colorf c = { 1, 0, 0, 0.5 };
   wnd->setBackgroundColor( c );
   gUI->addWidget( wnd );

   glutMainLoop();
}
