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
 * File:          $RCSfile: main.cpp,v $
 * Date modified: $Date: 2005-01-25 23:12:54 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <GL/glut.h>
#include <phui/phui.h>
#include <phui/GLUTBridge.h>

namespace
{
   phui::RootWidgetPtr gRoot;
   int gContext; /// GLUT context
}


void idle()
{
   if (glutGetWindow() != gContext)
   {
      glutSetWindow(gContext);
   }
   glutPostRedisplay();
}

void display()
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   gRoot->draw();
   glutSwapBuffers();
}

void reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   gRoot->setSize(phui::Size(width, height));
}

int main(int argc, char** argv)
{
   try
   {
      glutInitWindowSize(640, 480);
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

      gContext = glutCreateWindow("Event Example");

      glutIdleFunc(idle);
      glutDisplayFunc(display);
      glutReshapeFunc(reshape);

      glutSetCursor(GLUT_CURSOR_NONE);

      // create our root widget
      gRoot = phui::CreateRoot(
         glutGet(GLUT_WINDOW_WIDTH),
         glutGet(GLUT_WINDOW_HEIGHT));

      // register it with glut
      phui::glutRegisterRoot(gRoot);

      phui::LayoutCodec codec;
      phui::WidgetPtr w = codec.decode("example.layout");
      if (w.get() != 0)
      {
         gRoot->add(w);
      }

      glutMainLoop();
   }
   catch (std::exception& e)
   {
      std::cerr << "caught exception: " << e.what() << std::endl;
   }
}
