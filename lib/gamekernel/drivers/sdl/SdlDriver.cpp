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
// Date modified: $Date: 2002-03-28 09:51:29 $
// Version:       $Revision: 1.5 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////

#include "SdlDriver.h"
#include <xdl.h>
#include <string>
//#define SDLDRIVER_DEBUG 1
//Create the drivers that can be probed by the SystemDriverFactory
#ifdef XDL_BUILD_DLL
extern "C" XDL_FUNC gk::ISystemDriver*
createSystemDriver()
{
   return new gk::SdlDriver();
}
#endif // XDL_BUILD_DLL

namespace gk {

SdlDriver::SdlDriver() : mHeight(480), mWidth(640), mBpp(16), mvideoFlags(0), mKernel(NULL), mMouse(NULL), mKeyboard(NULL) //mJoystick(NULL)
{
	misRunning = false;
	mName = "SDL with OpenGL";	
	//We really don't need to do anything other than initialize variables.
}

SdlDriver::~SdlDriver()
{
}

bool SdlDriver::init(IGameKernel *kernel)
{
	if (!kernel)
	{
		std::cerr << "SDL Driver Error:  Invalid Kernel" << std::endl;
		return false;
	}
	mKernel = kernel;
	mApp = kernel->getApp();
	//Initialize SDL.
	#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug:  Callling SDL_Init()" << std::endl;
	#endif
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL Driver Error:  Couldn't Initialize SDL.\nSDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Ask the video card what features it supports.
	const SDL_VideoInfo *videoInfo;
	#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug:  Callling SDLGetVideoInfo()" << std::endl;
	#endif
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
		std::cerr << "SDL Driver Error:  Couldn't Setup the screen.\nSDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Finally, set the title of the window.
	SDL_WM_SetCaption(mName.c_str(), NULL);
	//Update the values of mWidth and mHeight (just in case something weird is happening).
	mWidth = screen->w;
	mHeight = screen->h;
	screen = NULL;
	mMouse = new DeviceHandle<Mouse>("Mouse", mKernel);
	mKeyboard = new DeviceHandle<Keyboard>("Keyboard", mKernel);
	//odds of this happening are pretty slim, but might as well check...
	if (!mMouse)
	{
		std::cerr << "SDL Driver Error:  Couldn't allocate memory for the mouse Device Handle." << std::endl;
		return false;
	}
	if (!mKeyboard)
	{
		std::cerr << "SDL Driver Error:  Couldn't allocate memory for the keyboard Device Handle." << std::endl;
		return false;
	}
	//This enables repeating keybaord events.  These values should be read from somewhere, not hardcoded in.
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	return true;
}

bool SdlDriver::run()
{
	misRunning = true;
#ifdef SDLDRIVER_DEBUG
	std::cerr << "##SDL Driver Debug: Right before onContextInit" << std::endl;
#endif
	mApp->onContextInit();
#ifdef SDLDRIVER_DEBUG
	std::cerr << "##SDL Driver Debug: After onContextInit" << std::endl;
#endif
	
	//SDL does event polling, so we're just going to have to fake an idle loop.
#ifdef SDLDRIVER_DEBUG
	std::cerr << "##SDL Driver Debug: Inside run()" << std::endl;
#endif
	int error = 0;
	do
	{
#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SD Driver Debug: Inside event loop" << std::endl;
#endif
		//TODO:  Support Multiple Windows
		mApp->onPreFrame();
		mApp->onContextDraw(0);
		SDL_GL_SwapBuffers();
		mApp->onPostFrame();	
		error = SDL_WaitEvent(&mEvent);
		if (error == 0)
		{
			std::cerr << "SDL Driver Error:  Error while waiting for events\nSDL Error:  " << SDL_GetError()
					<< std::endl;
		}
		handleEvent();
		mKernel->getInput()->update();
	}while((error != 0) && (misRunning));
	return true;
}	

void SdlDriver::shutdown()
{
	//Cleanup time...
	misRunning = false;
	if (mKeyboard != NULL)
	{
		mKeyboard = NULL;
		delete mKeyboard;
	}
	if (mKeyboard != NULL)
	{
		mKeyboard = NULL;
		delete mKeyboard;
	}
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
				<< " is not supported by this video card.  Leaving the window unchanged." << std::endl;
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

void SdlDriver::handleEvent()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr << "SDL Driver Debug:  Inside handleEvent" << std::endl;
#endif
	switch (mEvent.type)
	{
		case SDL_QUIT:
			shutdown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_VIDEORESIZE:
			setWindowSize(mEvent.resize.w, mEvent.resize.h);
			break;
		case SDL_MOUSEMOTION:
			onMouseMove();
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseDown();
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseUp();
			break;
		default:
			break;
			//unhandled event; we pretty much ignore it.
	}
}

void SdlDriver::onKeyUp()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr << "SDL Driver Debug:  Inside onKeyUp" << std::endl;
#endif
	SDL_keysym key = mEvent.key.keysym;
	std::string keyID = getKeyID(key);
	const DigitalInput::BinaryState state = DigitalInput::OFF;
	Keyboard *kb = mKeyboard->getDevice();
	kb->button(keyID)->setBinaryState(state);
}

void SdlDriver::onKeyDown()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr<<"SDL Driver Debug:  Inside onKeyDown" << std::endl;
#endif
	SDL_keysym key = mEvent.key.keysym;
	std::string keyID = getKeyID(key);
	const DigitalInput::BinaryState state = DigitalInput::ON;
	Keyboard *kb = mKeyboard->getDevice();
	kb->button(keyID)->setBinaryState(state);
}

void SdlDriver::onMouseMove()
{
	Mouse *mouse = mMouse->getDevice();
	float x = static_cast<float>(mEvent.motion.x) / static_cast<float>(mWidth) * 2.0f - 1.0f;
	mouse->axis(0).setData(x);
	float y = static_cast<float>(mEvent.motion.y) / static_cast<float>(mHeight) * 2.0f - 1.0f;
	mouse->axis(1).setData(y);
	mouse = NULL;
}
void SdlDriver::onMouseDown()
{
	Mouse *mouse = mMouse->getDevice();
	Mouse::Button button;
	switch (mEvent.button.button)
	{
		case SDL_BUTTON_LEFT:
			button = Mouse::LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			button = Mouse::MIDDLE;
			break;
		case SDL_BUTTON_RIGHT:
			button = Mouse::RIGHT;
			break;
		default:
			break;
	}
	if (mEvent.button.state == SDL_PRESSED)
	{
		mouse->button(button).setBinaryState(DigitalInput::ON);
	}
	
	mouse->axis(0).setData(mEvent.button.x);
	mouse->axis(1).setData(mEvent.button.y);
}

void SdlDriver::onMouseUp()
{
	Mouse *mouse = mMouse->getDevice();
	Mouse::Button button;
	switch (mEvent.button.button)
	{
		case SDL_BUTTON_LEFT:
			button = Mouse::LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			button = Mouse::MIDDLE;
			break;
		case SDL_BUTTON_RIGHT:
			button = Mouse::RIGHT;
			break;
		default:
			break;
	}
	if (mEvent.button.state == SDL_RELEASED)
	{
		mouse->button(button).setBinaryState(DigitalInput::OFF);
	}

	mouse->axis(0).setData(mEvent.button.x);
	mouse->axis(1).setData(mEvent.button.y);
}

//FIXME:  Yuck!  There has to be a better way...
std::string SdlDriver::getKeyID(SDL_keysym& key)
{
	if (key.sym == SDLK_BACKSPACE)
	{
		return "KEY_BS";
	}
	else if (key.sym == SDLK_TAB)
	{
		return "KEY_TAB";
	}
	else if (key.sym == SDLK_RETURN)
	{
		return "KEY_NEWLINE";
	}
	else if (key.sym == SDLK_ESCAPE)
	{
		return "KEY_ESC";
	}
	else if (key.sym == SDLK_SPACE)
	{
		return "KEY_SPACE";
	}
	else if (key.sym == SDLK_QUOTEDBL)
	{
		return "KEY_DOUBLEQUOTES";
	}
	else if (key.sym == SDLK_HASH)
	{
		return "KEY_HASH";
	}
	else if (key.sym == SDLK_DOLLAR)
	{
		return "KEY_DOLLAR";
	}
	else if (key.sym == SDLK_5 && key.mod == KMOD_SHIFT)
	{
		return "KEY_PERCENT";
	}
	else if (key.sym == SDLK_AMPERSAND)
	{
		return "KEY_AMPERSAND";
	}
	else if (key.sym == SDLK_QUOTE)
	{
		return "KEY_RIGHTQUOTE";
	}
	else if (key.sym == SDLK_LEFTPAREN)
	{
		return "KEY_LEFTPAREN";
	}
	else if (key.sym == SDLK_RIGHTPAREN)
	{
		return "KEY_RIGHTPAREN";
	}
	else if (key.sym == SDLK_ASTERISK)
	{
		return "KEY_ASTERISK";
	}
	else if (key.sym == SDLK_PLUS)
	{
		return "KEY_POS";
	}
	else if (key.sym == SDLK_COMMA)
	{
		return "KEY_COMMA";
	}
	else if (key.sym == SDLK_MINUS)
	{
		return "KEY_NEG";
	}
	else if (key.sym == SDLK_PERIOD)
	{
		return "KEY_PERIOD";
	}
	else if (key.sym == SDLK_SLASH)
	{
		return "KEY_SLASH";
	}
	else if (key.sym == SDLK_0)
	{
		return "KEY_ZERO";
	}
	else if (key.sym == SDLK_1)
	{
		return "KEY_ONE";
	}
	else if (key.sym == SDLK_2)
	{
		return "KEY_TWO";
	}
	else if (key.sym == SDLK_3)
	{
		return "KEY_THREE";
	}
	else if (key.sym == SDLK_4)
	{
		return "KEY_FOUR";
	}
	else if (key.sym == SDLK_5)
	{
		return "KEY_FIVE";
	}
	else if (key.sym == SDLK_6)
	{
		return "KEY_SIX";
	}
	else if (key.sym == SDLK_7)
	{
		return "KEY_SEVEN";
	}
	else if (key.sym == SDLK_8)
	{
		return "KEY_EIGHT";
	}
	else if (key.sym == SDLK_9)
	{
		return "KEY_NINE";
	}
	else if (key.sym == SDLK_COLON)
	{
		return "KEY_COLON";
	}
	else if (key.sym == SDLK_SEMICOLON)
	{
		return "KEY_SEMICOLON";
	}
	else if (key.sym == SDLK_LESS)
	{
		return "KEY_LESSTHAN";
	}
	else if (key.sym == SDLK_GREATER)
	{
		return "KEY_GREATERTHAN";
	}
	else if (key.sym == SDLK_QUESTION)
	{
		return "KEY_QUESTION";
	}
	else if (key.sym == SDLK_AT)
	{
		return "KEY_AT";
	}
	else if (key.sym == SDLK_a)
	{
		return "KEY_A";
	}
	else if (key.sym == SDLK_b)
	{
		return "KEY_B";
	}
	else if (key.sym == SDLK_c)
	{
		return "KEY_C";
	}
	else if (key.sym == SDLK_d)
	{
		return "KEY_D";
	}
	else if (key.sym == SDLK_e)
	{
		return "KEY_E";
	}
	else if (key.sym == SDLK_f)
	{
		return "KEY_F";
	}
	else if (key.sym == SDLK_g)
	{
		return "KEY_G";
	}
	else if (key.sym == SDLK_h)
	{
		return "KEY_H";
	}
	else if (key.sym == SDLK_i)
	{
		return "KEY_I";
	}
	else if (key.sym == SDLK_j)
	{
		return "KEY_J";
	}
	else if (key.sym == SDLK_l)
	{
		return "KEY_L";
	}
	else if (key.sym == SDLK_m)
	{
		return "KEY_M";
	}
	else if (key.sym == SDLK_n)
	{
		return "KEY_N";
	}
	else if (key.sym == SDLK_o)
	{
		return "KEY_O";
	}
	else if (key.sym == SDLK_p)
	{
		return "KEY_P";
	}
	else if (key.sym == SDLK_q)
	{
		return "KEY_Q";
	}
	else if (key.sym == SDLK_r)
	{
		return "KEY_R";
	}
	else if (key.sym == SDLK_s)
	{
		return "KEY_S";
	}
	else if (key.sym == SDLK_t)
	{
		return "KEY_T";
	}
	else if (key.sym == SDLK_u)
	{
		return "KEY_U";
	}
	else if (key.sym == SDLK_v)
	{
		return "KEY_V";
	}
	else if (key.sym == SDLK_w)
	{
		return "KEY_W";
	}
	else if (key.sym == SDLK_x)
	{
		return "KEY_X";
	}
	else if (key.sym == SDLK_y)
	{
		return "KEY_Y";
	}
	else if (key.sym == SDLK_z)
	{
		return "KEY_Z";
	}
	else if (key.sym == SDLK_LEFTBRACKET)
	{
		if (key.mod == KMOD_SHIFT)
		{
			return "KEY_CURLYLEFT";
		}	
		return "KEY_LEFTBRACKET";
	}
	else if (key.sym == SDLK_BACKSLASH)
	{
		if (key.mod == KMOD_SHIFT)
		{
			return "KEY_PIPE";
		}
		return "KEY_BACKSLASH";
	}
	else if (key.sym == SDLK_RIGHTBRACKET)
	{
		if (key.mod == KMOD_SHIFT)
		{
			return "KEY_CURLYRIGHT";
		}
		return "KEY_RIGHTBRACKET";
	}
	else if (key.sym == SDLK_CARET)
	{
		return "KEY_CARET";
	}
	else if (key.sym == SDLK_UNDERSCORE)
	{
		return "KEY_UNDERSCORE";
	}
	else if (key.sym == SDLK_BACKQUOTE)
	{
		if (key.mod == KMOD_SHIFT)
		{
			return "KEY_TILDE";
		}
		return "KEY_LEFTQUOTE";
	}
	else if (key.sym == SDLK_DELETE)
	{
		return "KEY_DELETE";
	}
	else if (key.sym == SDLK_PAGEUP)
	{
		return "KEY_PAGEUP";
	}
	else if (key.sym == SDLK_PAGEDOWN)
	{
		return "KEY_PAGEDOWN";
	}
	else if (key.sym == SDLK_HOME)
	{
		return "KEY_HOME";
	}
	else if (key.sym == SDLK_END)
	{
		return "KEY_END";
	}
	else if (key.sym == SDLK_INSERT)
	{
		return "KEY_INSERT";
	}
	else if (key.sym == SDLK_UP)
	{
		return "KEY_UPARROW";
	}
	else if (key.sym == SDLK_DOWN)
	{
		return "KEY_DOWNARROW";
	}
	else if (key.sym == SDLK_LEFT)
	{
		return "KEY_LEFTARROW";
	}
	else if (key.sym == SDLK_RIGHT)
	{
		return "KEY_RIGHTARROW";
	}
	else if (key.sym == SDLK_CAPSLOCK)
	{
		return "KEY_CAPS";
	}
	else if (key.sym == SDLK_LSHIFT)
	{
		return "KEY_LSHIFT";
	}
	else if (key.sym == SDLK_LCTRL)
	{
		return "KEY_LCTRL";
	}
	else if (key.sym == SDLK_RSHIFT)
	{
		return "KEY_RSHIFT";
	}
	else if (key.sym == SDLK_RCTRL)
	{
		return "KEY_RCTRL";
	}
	else if (key.sym == SDLK_F1)
	{
		return "KEY_F1";
	}
	else if (key.sym == SDLK_F2)
	{
		return "KEY_F2";
	}
	else if (key.sym == SDLK_F3)
	{
		return "KEY_F3";
	}
	else if (key.sym == SDLK_F4)
	{
		return "KEY_F4";
	}
	else if (key.sym == SDLK_F5)
	{
		return "KEY_F5";
	}
	else if (key.sym == SDLK_F6)
	{
		return "KEY_F6";
	}
	else if (key.sym == SDLK_F7)
	{
		return "KEY_F7";
	}
	else if (key.sym == SDLK_F8)
	{
		return "KEY_F8";
	}
	else if (key.sym == SDLK_F9)
	{
		return "KEY_F9";
	}
	else if (key.sym == SDLK_F10)
	{
		return "KEY_F10";
	}
	else if (key.sym == SDLK_F11)
	{
		return "KEY_F11";
	}
	else if (key.sym == SDLK_F12)
	{
		return "KEY_F12";
	}

   assert( false && "SDL Driver Error: Unknown key pressed." );
   return "";
}
		
	
} // namespace gk
