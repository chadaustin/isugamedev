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
 * File:          $RCSfile: sizes.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:22 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <iostream>
#include <map>
#include <GL/glut.h>
#include <gltext.h>
using namespace gltext;


std::map<int, FontRendererPtr> gRendererCache;


FontRendererPtr getRenderer(int size) {
   if (gRendererCache.count(size))
   {
      return gRendererCache[size];
   }
   else
   {
      FontPtr font = OpenFont("../arial.ttf", size);
      if (!font)
      {
         std::cerr << "Can't open font!" << std::endl;
         exit(1);
      }
      
      FontRendererPtr renderer = CreateRenderer(TEXTURE, font);
      if (!renderer)
      {
         std::cerr << "Can't create renderer!" << std::endl;
         exit(1);
      }
      
      gRendererCache[size] = renderer;
      return renderer;
   }
}


void display()
{
   glClearColor(0,0,0,1);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   glColor4f(0,0,1,1);
   int size = 2;
   int y = 0;
   while (y < 480)
   {
      FontRendererPtr renderer = getRenderer(size);
      FontPtr font = renderer->getFont();
   
      glPushMatrix();
      glTranslatef(0, y, 0);
      renderer->render("The quick, brown fox jumped over the lazy dog.");
      glPopMatrix();

      y += (font->getAscent() + font->getDescent() + font->getLineGap());
      size += 2;
   }

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
   glutCreateWindow("Sizes Example");

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keydown);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glutMainLoop();
}
