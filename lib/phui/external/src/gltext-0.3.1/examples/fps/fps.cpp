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
 * File:          $RCSfile: fps.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:10 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <gltext.h>
using namespace gltext;


class FPSCounter
{
public:
   FPSCounter()
   {
      mFPS = 0;
      mFrameCount = 0;
      mElapsedTime = 0;
   }

   void update(float dt)
   {
      mElapsedTime += dt;
      ++mFrameCount;
      if (mElapsedTime > 1.0f)
      {
         mFPS = mFrameCount;
         mFrameCount = 0;
         mElapsedTime -= 1.0f;
      }
   }

   int getFPS() const
   {
      return mFPS;
   }

private:
   int mFPS;
   int mFrameCount;
   float mElapsedTime;
};


struct Renderer
{
   Renderer(std::string n, const FontRendererPtr& r)
   {
      name = n;
      renderer = r;
   }

   std::string name;
   FontRendererPtr renderer;
};


std::vector<Renderer> gRenderers;
unsigned gCurrentRenderer;
int gLastUpdate;
FPSCounter gFPSCounter;
static const char* gStrings[] =
{
   "The five boxing wizards jump quickly.",
   "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
};
static const unsigned gStringCount = sizeof(gStrings) / sizeof(*gStrings);
unsigned gCurrentString = 0;


void display()
{
   glClearColor(0, 0, 0, 0);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   const std::string& name = gRenderers[gCurrentRenderer].name;
   const FontRendererPtr& renderer = gRenderers[gCurrentRenderer].renderer;

   int fps = gFPSCounter.getFPS();
   std::ostringstream ss;
   ss << "FPS: " << fps << "\n" << "Renderer: " << name << "\n\n";
   for (int i = 0; i < 12; ++i)
   {
      ss << gStrings[gCurrentString] << "\n";
   }

   renderer->render(ss.str().c_str());

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
   else if (key == ' ')
   {
      gCurrentRenderer = (gCurrentRenderer + 1) % gRenderers.size();
   }
   else if (key == 'n')
   {
      gCurrentString = (gCurrentString + 1) % gStringCount;
   }
}


void idle()
{
   int now = glutGet(GLUT_ELAPSED_TIME);
   float dt = (now - gLastUpdate) / 1000.0f;
   gLastUpdate = now;

   gFPSCounter.update(dt);
   glutPostRedisplay();
}


int main(int argc, char** argv)
{
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(50, 50);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   glutCreateWindow("Alpha Example");

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keydown);
   glutIdleFunc(idle);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   FontPtr font = OpenFont("../arial.ttf", 26);
   if (! font)
   {
      std::cerr<<"Couldn't create font!"<<std::endl;
      return 1;
   }

   FontRendererPtr btmRenderer = CreateRenderer(BITMAP, font);
   if (! btmRenderer)
   {
      std::cerr<<"Couldn't create bitmap font renderer!"<<std::endl;
      return 1;
   }

   FontRendererPtr pxmRenderer = CreateRenderer(PIXMAP, font);
   if (! pxmRenderer)
   {
      std::cerr<<"Couldn't create pixmap font renderer!"<<std::endl;
      return 1;
   }

   FontRendererPtr texRenderer = CreateRenderer(TEXTURE, font);
   if (! texRenderer)
   {
      std::cerr<<"Couldn't create texture font renderer!"<<std::endl;
      return 1;
   }

   FontRendererPtr mipRenderer = CreateRenderer(MIPMAP, font);
   if (! mipRenderer)
   {
      std::cerr<<"Couldn't create mipmap font renderer!"<<std::endl;
      return 1;
   }

   gRenderers.push_back(Renderer("bitmap",  btmRenderer));
   gRenderers.push_back(Renderer("pixmap",  pxmRenderer));
   gRenderers.push_back(Renderer("texture", texRenderer));
   gRenderers.push_back(Renderer("mipmap",  mipRenderer));
   gCurrentRenderer = 0;

   gLastUpdate = glutGet(GLUT_ELAPSED_TIME);
   glutMainLoop();
}
