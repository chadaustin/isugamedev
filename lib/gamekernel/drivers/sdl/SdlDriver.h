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
// File:          $RCSfile: SdlDriver.h,v $
// Date modified: $Date: 2002-04-06 22:25:34 $
// Version:       $Revision: 1.8 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_SDLDRIVER_H
#define GK_SDLDRIVER_H

#include "gk/gkCommon.h"
#include "gk/ISystemDriver.h"
#include "gk/IGameKernel.h"
#include "gk/Keyboard.h"
#include "gk/Mouse.h"
#include "gk/ContextData.h"
#include <SDL/SDL.h>
#include <string>
#include <iostream>

namespace gk {

/**
* SDL implementation of the ISystemDriver interface.
*
* @see ISystemDriver
*/
class SdlDriver : public DLLImpl< ISystemDriver >
{
public:
	SdlDriver();
	virtual ~SdlDriver();
	
	/**
    	* Initializes this driver and starts it through its main loop.
    	*
    	* @return  true if successful, false otherwise
    	*/
   	virtual bool init(IGameKernel *kernel);
   	
   	/**
    * Starts the driver through its main loop.
    *
    * @return  true if successful, false otherwise
    */
   	virtual bool run();
   	
	/**
	* Destroys this driver and cleans up all memory allocated to it.
	*/
	virtual void shutdown();

	/**
	* Warps the mouse pointer to the given position
	*
	* @param x	the new x position
	* @param y	the new y position
	*/
	virtual void warpMouse( int x, int y );
	/**
	* Toggles whether the mouse pointer is shown on the screen.
	*
	* @param show	true to show the cursor, false otherwise
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

   //Private Attributes
private:

	std::string mName;					//Name of the window
	int mHeight;						//Height of the window
	int mWidth;						//Width of the window
	int mBpp;							//BitsPerPixel of the window
	Uint32 mvideoFlags;					//Video Flags of the screen.
	bool misRunning;					//Is the SdlDriver running?
	IGameKernel *mKernel;				//The GameKernel that is running this driver.
	IGameApp *mApp;					//The Application that is using this driver.
	DeviceHandle<Mouse>* mMouse;			//Mouse Device
	DeviceHandle<Keyboard>* mKeyboard;		//Keyboard Device
	//DeviceHandle<Joystick>* mJoystick;		//Joystick Device
	SDL_Event mEvent;					//Event Structure
	//bool mPress;					//Hack to work with the DigitalInput devices.	
	//bool mPressDown;					//Hack to work with the DigitalInput devices.
	//Private Methods
	
	//This function determines what kind of event has occurred, 
	//and then calls the appropriate method to handle the event.
	void handleEvent();
	//Called when a is depressed.
	void onKeyUp();
	//Called when a key is pressed.
	void onKeyDown();
	//Called when the mouse is moved.
	void onMouseMove();
	//Called when the mouse is clicked.
	void onMouseDown();
	//Called when the mouse is unclicked.
	void onMouseUp();
	//Yucky function that maps from SDL_KEY types to Keyboard::Key types.
	std::string getKeyID(SDL_keysym &key);
	
	/* TODO:
	   1.	Fix Event Handling.
	   2.	Implement Joystick Control.
	*/
};

} // namespace gk

#endif
