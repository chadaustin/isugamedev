/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * -----------------------------------------------------------------
 * File:          $RCSfile: window.cpp,v $
 * Date modified: $Date: 2003-01-05 02:19:15 $
 * Version:       $Revision: 1.22 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <GL/glut.h>
#include <phui/phui.h>
#include <phui/GLUTBridge.h>

static int gWidth  = 640;
static int gHeight = 480;
static int mainWin_contextID;
static phui::RootWidgetPtr gUI;
static phui::WindowPtr gWnd;

//-----------------------------------------------------------------------------

void OnRedisplay()
{
   glClearColor(0, 0, 0, 1);
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // setup projection
   glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(80.0f, (float)gWidth / (float)gHeight, 0.01f, 1000.0f);

   // setup modelview
   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   // draw a teapot
   glPushMatrix();
      glColor4f(0,0,1,1);
      glTranslatef(0, 0, -50);
      glutSolidTeapot(25);
   glPopMatrix();

   // draw a window
   gUI->draw();

   glutSwapBuffers();
}

void OnReshape(int width, int height)
{
   gWidth = width;
   gHeight = height;

   glViewport(0, 0, gWidth, gHeight);
   gUI->setSize(width, height);
}

void OnIdle()
{
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if (glutGetWindow() != mainWin_contextID)
   {
      glutSetWindow(mainWin_contextID);
   }

   // tell glut to call redisplay (which then calls OnRedisplay)
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   try
   {
      glutInitWindowSize(gWidth, gHeight);
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
      mainWin_contextID = glutCreateWindow("Window Example");

      // callbacks
      glutIdleFunc(OnIdle);
      glutDisplayFunc(OnRedisplay);
      glutReshapeFunc(OnReshape);

      glutSetCursor(GLUT_CURSOR_NONE);

      // Create our root widget
      gUI = phui::CreateRoot(
            glutGet(GLUT_WINDOW_WIDTH),
            glutGet(GLUT_WINDOW_HEIGHT));

      // Register it with glut
      phui::glutRegisterRoot(gUI);

      gWnd = phui::Window::create("my contacts blow");
      gWnd->setPosition(150, 75);
      gWnd->setSize(300, 250);
      gWnd->show();
      gWnd->setBackgroundColor(phui::Colorf(1, 0, 0, 0.75f));

      phui::WindowPtr window(phui::Window::create("other window"));
      window->setPosition(250, 175);
      window->setSize(300, 250);
      window->show();
      window->setBackgroundColor(phui::Colorf(0, 0, 1, 0.75f));

      phui::ButtonPtr btn(phui::Button::create(
                            "This is a really long string Push me!"));
      btn->setPosition(10, 10);
      btn->setSize(75, 30);
      btn->show();
      btn->setBackgroundColor(phui::Colorf(0,0,1,0.7));
      gWnd->add(btn);

      phui::LabelPtr lbl(phui::Label::create("Label me!"));
      lbl->setPosition(75, 10);
      lbl->setSize(100, 45);
      lbl->show();
      lbl->setBackgroundColor(phui::Colorf(0,1,1,0.7));
      gWnd->add(lbl);

      gUI->add(gWnd);
      gUI->add(window);

      glutMainLoop();
   }
   catch (std::exception& e)
   {
      std::cerr << "caught exception: " << e.what() << std::endl;
   }
}
