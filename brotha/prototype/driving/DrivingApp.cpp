/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: DrivingApp.cpp,v $
 * Date modified: $Date: 2002-03-29 21:29:26 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
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
 ************************************************************ brotha-cpr-end */
#include "DrivingApp.h"
#include <GL/gl.h>
#include <GL/glu.h>


DrivingApp::DrivingApp()
  : mKernel(0)
{
  m_orientation.x = 0;
  m_orientation.y = 0;
  m_orientation.z = 0;
}

DrivingApp::~DrivingApp()
{
}

void DrivingApp::onAppInit( gk::IGameKernel* kernel )
{
  mKernel = kernel;
  mKernel->setName( "Driving Simulation" );
  mQuit.init( "Quit", mKernel );
  mAccelerate.init( "Accelerate", mKernel );
  mBrake.init( "Brake", mKernel );
  mTurnLeft.init( "TurnLeft", mKernel );
  mTurnRight.init( "TurnRight", mKernel );
  mPause.init( "Pause", mKernel );
}

void DrivingApp::onContextInit()
{
  mKernel->setWindowSize( 640, 480 );
}

void DrivingApp::onContextDraw( int context )
{
  int width, height;
  mKernel->getWindowSize( width, height );
  glViewport( 0, 0, width, height );

  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


  // set up the projection matrix
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 90.0f, width / height, 0.01f, 1000.0f );

  // initialize your matrix stack used for transforming your models
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

//  gluLookAt(0.0000, 0, 5, 0, 0, 0, 0, 0, 1);

  gluLookAt(
    m_position.x + 1, m_position.y + 1, 5,
    m_position.x + m_orientation.x * 5,
    m_position.y + m_orientation.y * 5,
    0,
    0, 0, 1);

  glColor3f(1, 1, 1);
  glBegin(GL_LINES);
  for (int i = -50; i <= 50; ++i) {
    glVertex2f(i, -50);
    glVertex2f(i, 50);
    glVertex2f(-50, i);
    glVertex2f(50, i);
  }
  glEnd();
  
  return;

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

void DrivingApp::onPostFrame()
{
  // test for quit
  if (mQuit.getDigitalData() == gk::DigitalInput::DOWN) {
    mKernel->shutdown();
  }

  // un/pause game
  if (mPause.getDigitalData() == gk::DigitalInput::EDGE_DOWN) {
  }

  if (mAccelerate.getDigitalData() == gk::DigitalInput::DOWN) {
    m_position.x += 0.01f;
  }

  if (mBrake.getDigitalData() == gk::DigitalInput::DOWN) {
    m_position.x -= 0.01f;
  }

/*
  // accelerate
  if (mAccelerate.getDigitalData() == gk::DigitalInput::EDGE_DOWN) {
    // accelerate
  } else if (mAccelerate.getDigitalData() == gk::DigitalInput::EDGE_UP) {
    // stop accelerating
  }
*/

/*
      // brake
      if (mBrake.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
        {
          player->setBrake( true );
        }
      else if (mBrake.getDigitalData() == gk::DigitalInput::EDGE_UP)
        {
          player->setBrake( false );
        }

      // turn left
      if (mTurnLeft.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
        {
          player->setTurnLeft( true );
        }
      else if (mTurnLeft.getDigitalData() == gk::DigitalInput::EDGE_UP)
        {
          player->setTurnLeft( false );
        }

      // turn right
      if (mTurnRight.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
        {
          player->setTurnRight( true );
        }
      else if (mTurnRight.getDigitalData() == gk::DigitalInput::EDGE_UP)
        {
          player->setTurnRight( false );
        }
    }
*/
}
