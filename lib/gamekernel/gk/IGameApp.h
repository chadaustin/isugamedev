
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
// Date modified: $Date: 2003-02-09 07:43:03 $
// Version:       $Revision: 1.6 $
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
 *       virtual void onDraw( int context );
 *       virtual void onUpdate();
 *       // other overridden functions ...
 *    };
 * \endcode
 */
class GK_DLL IGameApp : public DLLInterface
{
public:
   /**
    * This is the draw function. 
    * Do rendering calls here.  This and onContextInit are the ONLY
    * functions that it is guarenteed that you have a valid rendering context.
    * Calling GL funcs in update may crash your system, you've been warned.
    *
    * <p>
    * The GameKernel calls this each frame once for each window.  For most 
    * applications, this usually can be ignored except in special apps that 
    * need multiple windows.
    * If there are multiple window contexts currently open, onDraw will be 
    * called once for each context per frame (or using our language, per update).
    *
    * @param context    the current OpenGL context
    */
   virtual void onDraw( int context = 0 ) = 0;

   /**
    * Called immediately before beginning to draw a frame.
    * Do computations here that you want done before a frame is rendered.
    * This function also gives you the most recent input device readings.
    *
    * @see onDraw(int)
    * @see onPostDraw()
    */
   virtual void onPreUpdate() = 0;
   
   /**
    * This is called repeatedly to let your application update it's state. 
    * There is a 1-1 correspondance between onDraw() and onUpdate() calls.
    *
    * <p>
    * NOTE: If you need asyncronous behaviour, then you need to create your own 
    * thread.  There is no reason for gamekernel to provide an asyncronous call
    * back, since the reason GK exists is to provide syncronized callback.
    * Anything asyncronous you need don't need to be here, and can easily be
    * created with your own user level thread.
    *
    * <p>
    * an app should assume that this func is called during draw.
    * Some implementations will call this before, after, or during...
    * Use pre or post frame (update) functions to guarentee ordering...
    *
    * <p>You should do all computation within this function.
    */
   virtual void onUpdate() = 0;
   
   /**
    * Called immediately after a frame has been drawn.
    * Do computations here that you want done after a frame is rendered.
    * This function also gives you the oldest input device readings.
    *
    * @see onPreDraw()
    * @see onDraw(int)
    */
   virtual void onPostUpdate() = 0;

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
   virtual void onAppInit( IGameKernel* kernel ) = 0;

   /**
    * This is called once for each context (window) after the window has been
    * opened, but before the onContextDraw().
    * Create your display lists here using a hash based on the context.
    *
    * @param context    the current OpenGL context
    */
   virtual void onContextInit( int context = 0 ) = 0;

   /**
    * This is called once for each context (window) immediately before the
    * window has been closed.
    * Destroy your display lists here using a hash based on the context.
    *
    * @param context    the current OpenGL context
    */
   virtual void onContextExit( int context = 0 ) = 0;
};

} // namespace gk

#endif
