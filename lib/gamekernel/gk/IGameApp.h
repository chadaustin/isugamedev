
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
// File:          $RCSfile: IGameApp.h,v $
// Date modified: $Date: 2002-03-18 06:34:55 $
// Version:       $Revision: 1.1 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_IGAMEAPP_H
#define GK_IGAMEAPP_H

#include <gk/gkCommon.h>
#include <gk/DLLInterface.h>

namespace gk {
class IGameKernel;

/**
 * Interface for an application that may be managed by the GameKernel system.
 * Application writers should implement this interface. It is recommended that
 * you not actually derive from this interface directly, but instead through
 * AbstractGameApp which gives default implementations for all methods in the
 * interface. Thus you only have to override the methods you care about.
 *
 * <h3>Example: Declaring your app</h3>
 * \code
 *    class MyApp : public AbstractGameApp
 *    {
 *       virtual ~MyApp();
 *       virtual void onContextDraw( int context );
 *       virtual void onPreFrame();
 *       // other overridden functions ...
 *    };
 * \endcode
 */
class IGameApp : public Private::DLLInterface
{
public:
   /**
    * This is the draw function. The GameKernel calls this each frame once per
    * window. The context is used to support multiple windows such as what you
    * might find in a VR environment. For PC applications, this can be ignored.
    *
    * @param context    the current OpenGL context
    */
   virtual void onContextDraw( int context = 0 ) = 0;

   /**
    * This is called immediately before onContextDraw(). You may do any
    * application specific pre-frame processing within this function.
    */
   virtual void onPreFrame() = 0;

   /**
    * This is called during a call to onContextDraw if the GameKernel driver is
    * multi-threaded. Otherwise it's call time is unspecified and may happen
    * either before or after a draw.
    */
   virtual void onIntraFrame() = 0;

   /**
    * This is called immediately after onContextDraw(). You may do any
    * application specific post-frame processing within this function.
    */
   virtual void onPostFrame() = 0;

// Init methods
public:
   /**
    * This is called by the GameKernel after the system driver is initialized
    * but before it is started. This function is called before any windows are
    * opened, thus it is NOT safe to make any OpenGL calls within this function.
    * For convenience a pointer to the GameKernel managing this app is passed
    * through this function.
    *
    * @param kernel     the IGameKernel instance running this app
    */
   virtual void onAppInit( IGameKernel* kernel) = 0;

   /**
    * This is called once for each context (window) after the window has been
    * opened, but before the onContextDraw().
    */
   virtual void onContextInit() = 0;

   /**
    * This is called once for each context (window) immediately before the
    * window has been closed.
    */
   virtual void onContextExit() = 0;
};

} // namespace gk

#endif
