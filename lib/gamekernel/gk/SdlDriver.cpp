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
// File:          $RCSfile: SdlDriver.cpp,v $
// Date modified: $Date: 2002-02-09 21:54:44 $
// Version:       $Revision: 1.2 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////

#include "SdlDriver.h"
#include "gk/GameKernel.h"
#include "gk/GameInput.h"
#include <string>

namespace gk {

SdlDriver::SdlDriver() : mWidth(640), mHeight(480), mBpp(16), mvideoFlags(0) //mMouse(NULL), mKeyboard(NULL), mJoystick(NULL)
{
	misRunning = false;
	mName = "SDL with OpenGL";	
	//We really don't need to do anything other than initialize variables.
}

SdlDriver::~SdlDriver()
{
}

bool SdlDriver::init()
{
	//Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL Driver Error:  Couldn't Initialize SDL.\nSDL Error: " << SDL_GetError() << endl;
		return false;
	}
	//Ask the video card what features it supports.
	const SDL_VideoInfo *videoInfo;
	videoInfo = SDL_GetVideoInfo();
	//Set the features we need.
	mvideoFlags = SDL_OPENGL | SDL_HWPALETTE | SDL_RESIZABLE | SDL_SRCALPHA;
	//Set the extra flags depending upon what the video card supports.
	if (videoInfo->hw_available)
	{
		mvideoFlags |= SDL_HWSURFACE;
	}
	else
	{
		mvideoFlags |= SDL_SWSURFACE;
	}
	if (videoInfo->blit_hw)
	{
		mvideoFlags |= SDL_HWACCEL;
	}
	//Enable Double Buffering for OpenGL (because it's cool :P)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Pointer to the screen.  We don't need to store this because we can always ask SDL to tell us where it is.
	SDL_Surface *screen;
	//Try and setup the screen...
	screen = SDL_SetVideoMode(mWidth, mHeight, mBpp, mvideoFlags);
	if (!screen)
	{
		//Oh boy...
		std::cerr << "SDL Driver Error:  Couldn't Setup the screen.\nSDL Error: " << SDL_GetError() << endl;
		return false;
	}
	//Finally, set the title of the window.
	SDL_WM_SetCaption(mName.c_str(), NULL);
	//Update the values of mWidth and mHeight (just in case something weird is happening).
	mWidth = screen->w;
	mHeight = screen->h;
	screen = NULL;
	return true;
}

bool SdlDriver::run()
{
	misRunning = true;
	return true;
}	

void SdlDriver::shutdown()
{
	//Cleanup time...
	misRunning = false;
	//GameInput::instance().removeDevice("Keyboard");
	//GameInput::instance().removeDevice("Mouse");
	//GameInput::instance().removeDevice("Joystick");
	SDL_Quit();
}

void SdlDriver::warpMouse( int x, int y )
{
	SDL_WarpMouse(x, y);
}

void SdlDriver::showMouse( bool show )
{
	if (show)
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{	
		SDL_ShowCursor(SDL_DISABLE);
	}
}

void SdlDriver::fullscreen(int ctx = 0)
{
	mvideoFlags |= SDL_FULLSCREEN;
	SDL_SetVideoMode(mWidth, mHeight, mBpp, mvideoFlags);
}

void SdlDriver::getWindowSize(int& width, int& height, int ctx = 0)
{
	width = mWidth;
	height = mHeight;
}

void SdlDriver::setWindowSize(int width, int height, int ctx = 0)
{
	//suggested bpp
	int sbpp;
	sbpp = SDL_VideoModeOK(width, height, mBpp, mvideoFlags);
	if (sbpp == 0)
	{
		std::cerr << "SDL Driver Error:  The requested window size of " << width << " by " << height
				<< " is not supported by this video card.  Leaving the window unchanged." << endl;
	}
	else
	{
		SDL_SetVideoMode(width, height, 0, mvideoFlags);
		mWidth = width;
		mHeight = height;
	}
}

void SdlDriver::setName( const std::string& name)
{
	mName = name;
	SDL_WM_SetCaption(mName.c_str(), NULL);
}

const std::string& SdlDriver::name() const
{
	return mName;
}

} // namespace gk
