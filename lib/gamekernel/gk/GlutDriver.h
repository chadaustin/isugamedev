
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
// File:          $RCSfile: GlutDriver.h,v $
// Date modified: $Date: 2002-02-06 22:22:22 $
// Version:       $Revision: 1.5 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GLUTDRIVER_H
#define GLUTDRIVER_H

#include "gk/gkCommon.h"
#include "gk/SystemDriver.h"
#include "gk/Keyboard.h"
#include "gk/ContextData.h"

/**
 * GLUT implementation of the system driver interface.
 *
 * @see SystemDriver
 */
class GlutDriver : public SystemDriver
{
public:
   GlutDriver();
   virtual ~GlutDriver();

   /**
    * Initializes this driver and starts it through its main loop.
    *
    * @return  true if successful, false otherwise
    */
   virtual bool startup();

   /**
    * Destroys this driver and cleans up all memory allocated to it.
    */
   virtual void shutdown();

   /**
    * Warps the mouse pointer to the given position.
    *
    * @param x       the new x position
    * @param y       the new y position
    */
   virtual void warpMouse( int x, int y );

   /**
    * Toggles whether the mouse pointer is shown on the screen.
    *
    * @param show    true to show the cursor, false otherwise
    */
   virtual void showMouse( bool show );

   /**
    * Puts the application in fullscreen. To put the application back in a
    * window, use setWindowSize().
    *
    * @param ctx        currently unused - use the default arg
    *
    * @see setWindowSize( int, int, int )
    */
   virtual void fullscreen( int ctx = 0 );

   /**
    * Gets the size of the window.
    *
    * @param width   [out]    filled with the width of the window
    * @param height  [out]    filled with the height of the window
    * @param ctx     [in]     currently unused - use the default arg
    */
   virtual void getWindowSize( int& width, int& height, int ctx = 0 );

   /**
    * Resizes the window to the given size. Use this to restore after a full
    * screen or to init the window size in onAppInit().
    *
    * @param width      the new width of the window
    * @param height     the new height of the window
    * @param ctx        currently unused - use the default arg
    */
   virtual void setWindowSize( int width, int height, int ctx = 0 );

   /**
    * Sets the name to use as the title for the windows.
    *
    * @param name       the name of this kernel
    */
   virtual void setName( const std::string& name );

   /**
    * Gets the name to use as the title for the windows.
    *
    * @return  the name used for the window titles
    */
   virtual const std::string& name() const;

private:
   /**
    * Initializes the current context if necessary.
    */
   void initCurrentContext();

   //---------------------------------------------------------------------------
   // Glut Callbacks
   //---------------------------------------------------------------------------
   static void OnIdle();
   static void OnRedisplay();
   static void OnReshape( int w, int h );
   static void OnKeyboardDown (unsigned char k, int x, int y );
   static void OnKeyboardUp( unsigned char k, int x, int y );
   static void keyboardEvent( const bool& isdown, const int& k, Keyboard& keyboard );
   static void OnSpecialKeyboardDown (int k, int x, int y );
   static void OnSpecialKeyboardUp( int k, int x, int y );
   static void OnMousePos( int x, int y );
   static void OnMouseClick( int button, int state, int x, int y );
   static void postRedisplay();

private:
   /**
    * The width of the window.
    */
   int mWidth;

   /**
    * The height of the window.
    */
   int mHeight;

   /**
    * The name to use for the window title.
    */
   std::string mName;

   /**
    * The current context. Currently only one context is implemented.
    */
   int mCurrentContext;

   /**
    * Context ID of the main window.
    */
   int mMainWin_ContextID;

   /**
    * Flag for whether the application has started.
    */
   bool mIsStarted;

   /**
    * There should only be 1 GLUT driver at any given time, but we don't want
    * this class to be a singleton. This is a pointer to the current driver
    * instance.
    */
   static GlutDriver* sDriver;

private:
   ///////////////////////////////////////////////////////////////////
   class DefaultFalseBool
   {
   private:
      bool _flag;
   public:
      DefaultFalseBool() : _flag(false) {}
      DefaultFalseBool(const bool& flag) : _flag(flag) {}
      inline bool& truth() { return _flag; }
      inline const bool& truth() const { return _flag; }
   };
   ContextData<DefaultFalseBool> oneTimeOnly;
};

#endif // ! GLUTDRIVER_H
