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
 * File:          $RCSfile: simple.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:21 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <iostream>
#include <GL/glut.h>
#include <gltext.h>
using namespace gltext;


FontRendererPtr btmRenderer;
FontRendererPtr pxmRenderer;
FontRendererPtr texRenderer;
FontRendererPtr mipRenderer;


void drawText(const FontRendererPtr& renderer, std::string text)
{
   text += " Hello...\n...World!  ";
   const int size   = renderer->getFont()->getSize();
   const int dpi    = renderer->getFont()->getDPI();
   const int width  = renderer->getWidth(text.c_str());
   const int height = renderer->getHeight(text.c_str());
   GLTEXT_STREAM(renderer) << text << size << "  " << dpi
                           << "  " << width << "*" << height;
}

void display()
{
   glClearColor(0, 0, 0.25f, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glColor4f(0.75f, 0.25f, 0, 1);

   glTranslatef(50, 50, 0);

   drawText(btmRenderer, "(bitmap) ");
   glTranslatef(0, 100, 0);
   drawText(pxmRenderer, "(pixmap) ");
   glTranslatef(0, 100, 0);
   drawText(texRenderer, "(texture)");
   glTranslatef(0, 100, 0);
   drawText(mipRenderer, "(mipmap) ");

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
   glutCreateWindow("Simple Example");

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
