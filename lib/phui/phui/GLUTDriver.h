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
 * File:          $RCSfile: GLUTDriver.h,v $
 * Date modified: $Date: 2005-01-25 17:28:50 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_GLUT_DRIVER_H
#define PHUI_GLUT_DRIVER_H

#include "Driver.h"
#include <GL/glut.h>

namespace phui
{
   class GLUTDriver : public Driver
   {
   public:

      /**
       * Default Constructor
       * Sets up Windows et al using the glut library if running in
       * standalone mode.
       *
       * @param   standalone     true if we are running in standalone mode,
       *                         false otherwise
       */
      GLUTDriver(bool standalone = true);

      /**
       * Destructor
       * Cleans up everything phui related.
       */
      virtual ~GLUTDriver();

      // Inherited functions.

      std::string getDriverName()
      {
         return "Glut Driver";
      }

      std::string getDriverVersion()
      {
         return "0.0.1";
      }

      void registerRoot(RootWidgetPtr root);
      
      void onKeyDown(InputKey key);

      void onKeyUp(InputKey key);

      void onMouseDown(InputButton button, const Point& p);

      void onMouseUp(InputButton button, const Point& p);

      void onMouseMove(const Point& p);

      void start();

      void update();

      bool isStandalone()
      {
         return mStandalone;
      }

      /**
       * GLUT specific handlers necessary to get around the callback model
       * of GLUT.
       */
      void onReshape(int w, int h);
      void onDisplay();

   private:

      /// Are we running in standalone or module mode?
      bool                    mStandalone;

      /// The root widget of the display, ie, the widget that holds everything.
      WidgetPtr               mRootWidget;

      /// integer representing the argc argument for glutInit
      int                     mDummyArgc;

      /// Can the application quit yet?  (Only meaningful in standalone mode)
      bool                    mCanQuit;
   };
}
#endif
