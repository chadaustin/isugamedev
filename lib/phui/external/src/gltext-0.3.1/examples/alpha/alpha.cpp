/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/*************************************************************** gltext-cpr beg
 *
 * GLText - OpenGL TrueType Font Renderer
 * GLText is (C) Copyright 2002 by Ben Scott
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
 * File:          $RCSfile: alpha.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:10 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <stdlib.h>  // GLUT complains if exit() isn't predefined in VC7
#include <GL/glut.h>
#include <gltext.h>
#include <iostream>
using namespace gltext;


FontRendererPtr btmRenderer;
FontRendererPtr pxmRenderer;
FontRendererPtr texRenderer;
FontRendererPtr mipRenderer;


void renderText(const FontRendererPtr& renderer, const std::string& name)
{
   const int size = renderer->getFont()->getSize();
   const int dpi  = renderer->getFont()->getDPI();

   std::ostringstream ss;
   ss << "hello world " << name << " AVWAT.  T. S. Lewis "
      << size << "/" << dpi;

   glPushMatrix();
   glColor3f(0, 0, 0);
   renderer->render(ss.str().c_str());
   glTranslatef(-5, -5, 0);
   glColor3f(1, 1, 1);
   renderer->render(ss.str().c_str());
   glPopMatrix();   
}

void display()
{
   glClearColor(0.5f, 0, 0.5f, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(50, 50, 0);
   renderText(btmRenderer, "(btm)");
   glTranslatef(0, 100, 0);
   renderText(pxmRenderer, "(pxm)");
   glTranslatef(0, 100, 0);
   renderText(texRenderer, "(tex)");
   glTranslatef(0, 100, 0);
   renderText(mipRenderer, "(mip)");

   glutSwapBuffers();
}

void reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, width, height, 0);
}

void keydown(unsigned char key, int x, int y)
{
   if (key == 27 || key == 'q')
   {
      exit(0);
   }
}

int
main(int argc, char** argv)
{
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(50, 50);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   glutCreateWindow("Alpha Example");

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keydown);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   FontPtr font = OpenFont("../arial.ttf", 26);
   if (! font)
   {
      std::cerr<<"Couldn't create font!"<<std::endl;
      return 1;
   }

   btmRenderer = CreateRenderer(BITMAP, font);
   if (! btmRenderer)
   {
      std::cerr<<"Couldn't create bitmap font renderer!"<<std::endl;
      return 1;
   }

   pxmRenderer = CreateRenderer(PIXMAP, font);
   if (! pxmRenderer)
   {
      std::cerr<<"Couldn't create pixmap font renderer!"<<std::endl;
      return 1;
   }

   texRenderer = CreateRenderer(TEXTURE, font);
   if (! texRenderer)
   {
      std::cerr<<"Couldn't create texture font renderer!"<<std::endl;
      return 1;
   }

   mipRenderer = CreateRenderer(MIPMAP, font);
   if (! mipRenderer)
   {
      std::cerr<<"Couldn't create mipmap font renderer!"<<std::endl;
      return 1;
   }

   glutMainLoop();
}
