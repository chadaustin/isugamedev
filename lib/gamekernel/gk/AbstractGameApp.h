
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
// File:          $RCSfile: AbstractGameApp.h,v $
// Date modified: $Date: 2002-03-30 23:36:16 $
// Version:       $Revision: 1.4 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_ABSTRACTGAMEAPP_H
#define GK_ABSTRACTGAMEAPP_H

#include <gk/gkCommon.h>
#include <gk/IGameApp.h>

namespace gk {

/**
 * Abstract helper class for GameApp implementations. All methods declared by
 * the IGameApp interface are implemented by this class in default manners so
 * that derivations are free to only implement the methods they care about.
 *
 * @see IGameApp
 */
class AbstractGameApp : public DLLImpl< IGameApp >
{
protected:
   /**
    * This class is abstract. You cannot create a new AbstractGameApp. Instead,
    * you should derive your own GameApp type from this instead.
    */
   AbstractGameApp() {}

public:
   /**
    * Destroys this game application object. Implementations should remember to
    * implement a virtual destructor so destruction works correctly.
    */
   virtual ~AbstractGameApp() {}
   /**
    * This is the draw function. The GameKernel calls this each frame once per
    * window. The context is used to support multiple windows such as what you
    * might find in a VR environment. For PC applications, this can be ignored.
    * If there are multiple contexts currently open, onDraw will be called once
    * for each context.
    *
    * @param context    the current OpenGL context
    */
   virtual void onDraw( int context ) {}

   /**
    * This is called repeatedly to let your application update it's state. You
    * cannot rely on a 1-1 correspondance between onDraw() and onUpdate() calls.
    * In a single-threaded GameKernel, onDraw() will always immediately follow
    * onUpdate(). However, in a multi-threaded GameKernel, there may be more
    * than one onUpdate() call per onDraw() call since they will be called from
    * different threads.
    *
    * <p>You should do any application specific processing within this function.
    */
   virtual void onUpdate() {}

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
   virtual void onAppInit( IGameKernel* kernel ) {}

   /**
    * This is called once for each context (window) after the window has been
    * opened, but before the onContextDraw().
    *
    * @param context    the current OpenGL context
    */
   virtual void onContextInit( int context ) {}

   /**
    * This is called once for each context (window) immediately before the
    * window has been closed.
    *
    * @param context    the current OpenGL context
    */
   virtual void onContextExit( int context ) {}
};

} // namespace gk

#endif
