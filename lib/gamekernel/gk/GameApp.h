
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
// File:          $RCSfile: GameApp.h,v $
// Date modified: $Date: 2002-02-22 05:14:09 $
// Version:       $Revision: 1.9 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEAPP_H
#define GK_GAMEAPP_H

#include "gk/gkCommon.h"
#include <string>
#include <vector>
#include "gk/Mouse.h"
#include "gk/Keyboard.h"

namespace gk {

/**
 * Base game application class for use with the GameKernel. Application writers
 * should derive a class from this and overload the virtual members.
 *
 * <h4>Example GameApp Derivation</h4>
 * \code
 *    class MyApp : public GameApp
 *    {
 *       virtual ~MyAp();
 *       virtual void OnContextDraw( int context );
 *       virtual void OnPreFrame();
 *       // other overridden functions if necessary...
 *    };
 * \endcode
 */
class GameApp
{
protected:
   /**
    * This class is abstract, you should derive from GameApp instead.
    */
   GameApp() {}

public:
   /**
    * Destroys this game application object. Implementations should remember to
    * implement a virtual destructor so destruction works correctly.
    */
   virtual ~GameApp() {}

   /**
    * This is the draw function. The GameKernel calls this each frame once per
    * window. The context is used to support multiple windows such as what you
    * might find in a VR environment. For PC applications, this can be ignored.
    *
    * @param context    the current OpenGL context
    */
   virtual void OnContextDraw( int context = 0 ) {}

   /**
    * This is called immediately before onContextDraw(). You may do any
    * application specific pre-frame processing within this function.
    */
   virtual void OnPreFrame() {}

   /**
    * This is called during a call to onContextDraw if the GameKernel driver is
    * multi-threaded. Otherwise it's call time is unspecified and may happen
    * either before or after a draw.
    */
   virtual void OnIntraFrame() {}

   /**
    * This is called immediately after onContextDraw(). You may do any
    * application specific post-frame processing within this function.
    */
   virtual void OnPostFrame() {}

// Init methods
public:
   /**
    * This is called by the GameKernel after the system driver is initialized
    * but before it is started. This function is called before any windows are
    * opened, thus it is NOT safe to make any OpenGL calls within this function.
    */
   virtual void OnAppInit() {}

   /**
    * This is called once for each context (window) after the window has been
    * opened, but before the onContextDraw().
    */
   virtual void OnContextInit() {}

   /**
    * This is called once for each context (window) immediately before the
    * window has been closed.
    */
   virtual void OnContextExit() {}
};

} // namespace gk

#endif
