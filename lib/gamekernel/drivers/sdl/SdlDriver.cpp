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
// Date modified: $Date: 2003-02-09 08:36:56 $
// Version:       $Revision: 1.15 $
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

SdlDriver::SdlDriver() : mHeight(240), mWidth(320), mBpp(16), mvideoFlags(0), mKernel(NULL), mMouse(NULL), mKeyboard(NULL) //mJoystick(NULL)
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
	mJoystick = new DeviceHandle<Joystick>("Joystick", mKernel);
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
   if (!mJoystick)
	{
		std::cerr << "SDL Driver Error:  Couldn't allocate memory for the joystick Device Handle." << std::endl;
		return false;
	}
	//This enables repeating keybaord events.  These values should be read from somewhere, not hardcoded in.
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
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
	do
	{
#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug: Inside event loop" << std::endl;
#endif
		//TODO:  Support Multiple Windows
#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug: Calling app->onUpdate()" << std::endl;
#endif
		
		
      
#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug: app->onUpdate() Called." << std::endl;
#endif
		if (misRunning)
		{
         // pre frame
         mApp->onPreUpdate();

#ifdef SDLDRIVER_DEBUG
			std::cerr << "##SDL Driver Debug: Calling app->onDraw()" << std::endl;
#endif

         // ---- in the frame now ----
         // draw
			mApp->onDraw(0);
#ifdef SDLDRIVER_DEBUG
			std::cerr << "##SDL Driver Debug: app->onDraw() Called." << std::endl;
#endif
         // intra frame
         mApp->onUpdate();

			SDL_GL_SwapBuffers();

         // post frame
         mApp->onPostUpdate();

			while (SDL_PollEvent(&mEvent) && (misRunning))
			{
				handleEvent();
#ifdef SDLDRIVER_DEBUG
				std::cerr << "##SDL Driver Debug: handleEvent() exited.  misRunning: " << misRunning<<std::endl;
#endif			
			}
		}
	}while(misRunning);
	return true;
}	

void SdlDriver::shutdown()
{
	//Cleanup time...
#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug: Calling Shutdown" << std::endl;
#endif
	misRunning = false;
	if (mKeyboard != NULL)
	{
		delete mKeyboard;
		mKeyboard = NULL;
	}
	if (mMouse != NULL)
	{
		delete mMouse;
		mMouse = NULL;
	}
#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug: Calling SDL_Quit" << std::endl;
#endif
	SDL_Quit();
   exit( 0 ); // hack, should probably clean up displays and such to get rid of the graphics window
#ifdef SDLDRIVER_DEBUG
		std::cerr << "##SDL Driver Debug: SDL_Quit Called" << std::endl;
#endif
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

void SdlDriver::fullscreen(int ctx )
{
	mvideoFlags |= SDL_FULLSCREEN;
	SDL_SetVideoMode(mWidth, mHeight, mBpp, mvideoFlags);
}

void SdlDriver::getWindowSize(int& width, int& height, int ctx)
{
	width = mWidth;
	height = mHeight;
}

void SdlDriver::setWindowSize(int width, int height, int ctx)
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
	mKernel->getInput()->update();	
}

void SdlDriver::onKeyUp()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr << "SDL Driver Debug:  Inside onKeyUp" << std::endl;
#endif
	SDL_keysym key = mEvent.key.keysym;
	//std::string keyID = getKeyID(key);
	const DigitalInput::BinaryState state = DigitalInput::OFF;
	Keyboard *kb = mKeyboard->getDevice();
	//kb->button(keyID)->setBinaryState(state);

   kb->button( getKeyID(key) ).setBinaryState( state );
	//mPressDown = false;
}

void SdlDriver::onKeyDown()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr<<"SDL Driver Debug:  Inside onKeyDown" << std::endl;
#endif
	SDL_keysym key = mEvent.key.keysym;
	//std::string keyID = getKeyID(key);
	const DigitalInput::BinaryState state = DigitalInput::ON;
	Keyboard *kb = mKeyboard->getDevice();
//#ifdef SDLDRIVER_DEBUG
//	std::cerr<<"SDL Driver Debug:  KeyID:  " <<keyID<< std::endl;
//#endif
   Keyboard::Key id = getKeyID(key);//static_cast<Keyboard::Key>(kb->mMap[keyID]);
	kb->queue().push_back(id);
	kb->button( id ).setBinaryState( state );	
}

void SdlDriver::onMouseMove()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr<<"SDL Driver Debug:  Inside onMouseMove" << std::endl;
#endif
	Mouse *mouse = mMouse->getDevice();
	float x = static_cast<float>(mEvent.motion.x) / static_cast<float>(mWidth) * 2.0f - 1.0f;
	mouse->axis(0).setData(x);
	float y = static_cast<float>(mEvent.motion.y) / static_cast<float>(mHeight) * 2.0f - 1.0f;
	mouse->axis(1).setData(y);
	mouse = NULL;
}
void SdlDriver::onMouseDown()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr<<"SDL Driver Debug:  Inside onMouseDown" << std::endl;
#endif
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
	
	float x = static_cast<float>(mEvent.button.x) / static_cast<float>(mWidth) * 2.0f - 1.0f;
	mouse->axis(0).setData(x);
	float y = static_cast<float>(mEvent.button.y) / static_cast<float>(mHeight) * 2.0f - 1.0f;
	mouse->axis(1).setData(y);
}

void SdlDriver::onMouseUp()
{
#ifdef SDLDRIVER_DEBUG
	std::cerr<<"SDL Driver Debug:  Inside onMouseUp" << std::endl;
#endif
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
	float x = static_cast<float>(mEvent.button.x) / static_cast<float>(mWidth) * 2.0f - 1.0f;
	mouse->axis(0).setData(x);
	float y = static_cast<float>(mEvent.button.y) / static_cast<float>(mHeight) * 2.0f - 1.0f;
	mouse->axis(1).setData(y);
}

//FIXME:  Yuck!  There has to be a better way...
Keyboard::Key SdlDriver::getKeyID(SDL_keysym& key)
{
	switch(key.sym)
   {
      case SDLK_BACKSPACE:
	   {
		   return Keyboard::BACKSPACE;
	   }
	   case SDLK_TAB:
	   {
		   return Keyboard::TAB;
	   }
	   case SDLK_RETURN:
	   {
		   return Keyboard::NEWLINE;
	   }
	   case SDLK_ESCAPE:
	   {
		   return Keyboard::ESC;
	   }
	   case SDLK_SPACE:
	   {
		   return Keyboard::SPACE;
	   }
	   case SDLK_QUOTEDBL:
	   {
		   return Keyboard::DOUBLEQUOTES;
	   }
	   case SDLK_HASH:
	   {
		   return Keyboard::HASH;
	   }
	   case SDLK_DOLLAR:
	   {
		   return Keyboard::DOLLAR;
	   }
	   case SDLK_AMPERSAND:
	   {
		   return Keyboard::AMPERSAND;
	   }
	   case SDLK_QUOTE:
	   {
		   return Keyboard::RIGHTQUOTE;
	   }
	   case SDLK_LEFTPAREN:
	   {
		   return Keyboard::LEFTPAREN;
	   }
	   case SDLK_RIGHTPAREN:
	   {
		   return Keyboard::RIGHTPAREN;
	   }
	   case SDLK_ASTERISK:
	   {
		   return Keyboard::ASTERISK;
	   }
	   case SDLK_PLUS:
	   {
		   return Keyboard::POS;
	   }
	   case SDLK_COMMA:
	   {
		   return Keyboard::COMMA;
	   }
	   case SDLK_MINUS:
	   {
		   return Keyboard::NEG;
	   }
	   case SDLK_PERIOD:
	   {
		   return Keyboard::PERIOD;
	   }
	   case SDLK_SLASH:
	   {
		   return Keyboard::SLASH;
	   }
	   case SDLK_0:
	   {
		   return Keyboard::ZERO;
	   }
	   case SDLK_1:
	   {
		   return Keyboard::ONE;
	   }
	   case SDLK_2:
	   {
		   return Keyboard::TWO;
	   }
	   case SDLK_3:
	   {
		   return Keyboard::THREE;
	   }
	   case SDLK_4:
	   {
		   return Keyboard::FOUR;
	   }
	   case SDLK_5:
	   {
         if (key.mod == KMOD_SHIFT)
	         return Keyboard::PERCENT;
	      else
		      return Keyboard::FIVE;
	   }
	   case SDLK_6:
	   {
		   return Keyboard::SIX;
	   }
	   case SDLK_7:
	   {
		   return Keyboard::SEVEN;
	   }
	   case SDLK_8:
	   {
		   return Keyboard::EIGHT;
	   }
	   case SDLK_9:
	   {
		   return Keyboard::NINE;
	   }
	   case SDLK_COLON:
	   {
		   return Keyboard::COLON;
	   }
	   case SDLK_SEMICOLON:
	   {
		   return Keyboard::SEMICOLON;
	   }
	   case SDLK_LESS:
	   {
		   return Keyboard::LESSTHAN;
	   }
	   case SDLK_GREATER:
	   {
		   return Keyboard::GREATERTHAN;
	   }
	   case SDLK_QUESTION:
	   {
		   return Keyboard::QUESTION;
	   }
	   case SDLK_AT:
	   {
		   return Keyboard::AT;
	   }
	   case SDLK_a:
	   {
		   return Keyboard::A;
	   }
	   case SDLK_b:
	   {
		   return Keyboard::B;
	   }
	   case SDLK_c:
	   {
		   return Keyboard::C;
	   }
	   case SDLK_d:
	   {
		   return Keyboard::D;
	   }
	   case SDLK_e:
	   {
		   return Keyboard::E;
	   }
	   case SDLK_f:
	   {
		   return Keyboard::F;
	   }
	   case SDLK_g:
	   {
		   return Keyboard::G;
	   }
	   case SDLK_h:
	   {
		   return Keyboard::H;
	   }
	   case SDLK_i:
	   {
		   return Keyboard::I;
	   }
	   case SDLK_j:
	   {
		   return Keyboard::J;
	   }
      case SDLK_k:
	   {
		   return Keyboard::K;
	   }
	   case SDLK_l:
	   {
		   return Keyboard::L;
	   }
	   case SDLK_m:
	   {
		   return Keyboard::M;
	   }
	   case SDLK_n:
	   {
		   return Keyboard::N;
	   }
	   case SDLK_o:
	   {
		   return Keyboard::O;
	   }
	   case SDLK_p:
	   {
		   return Keyboard::P;
	   }
	   case SDLK_q:
	   {
		   return Keyboard::Q;
	   }
	   case SDLK_r:
	   {
		   return Keyboard::R;
	   }
	   case SDLK_s:
	   {
		   return Keyboard::S;
	   }
	   case SDLK_t:
	   {
		   return Keyboard::T;
	   }
	   case SDLK_u:
	   {
		   return Keyboard::U;
	   }
	   case SDLK_v:
	   {
		   return Keyboard::V;
	   }
	   case SDLK_w:
	   {
		   return Keyboard::W;
	   }
	   case SDLK_x:
	   {
		   return Keyboard::X;
	   }
	   case SDLK_y:
	   {
		   return Keyboard::Y;
	   }
	   case SDLK_z:
	   {
		   return Keyboard::Z;
	   }
      case SDLK_RALT:
	   {
		   return Keyboard::RALT;
	   }
      case SDLK_LALT:
	   {
		   return Keyboard::LALT;
	   }
	   case SDLK_LEFTBRACKET:
	   {
		   if (key.mod == KMOD_SHIFT)
		   {
			   return Keyboard::CURLYLEFT;
		   }	
		   return Keyboard::LEFTBRACKET;
	   }
	   case SDLK_BACKSLASH:
	   {
		   if (key.mod == KMOD_SHIFT)
		   {
			   return Keyboard::PIPE;
		   }
		   return Keyboard::BACKSLASH;
	   }
	   case SDLK_RIGHTBRACKET:
	   {
		   if (key.mod == KMOD_SHIFT)
		   {
			   return Keyboard::CURLYRIGHT;
		   }
		   return Keyboard::RIGHTBRACKET;
	   }
	   case SDLK_CARET:
	   {
		   return Keyboard::CARET;
	   }
	   case SDLK_UNDERSCORE:
	   {
		   return Keyboard::UNDERSCORE;
	   }
	   case SDLK_BACKQUOTE:
	   {
		   if (key.mod == KMOD_SHIFT)
		   {
			   return Keyboard::TILDE;
		   }
		   return Keyboard::LEFTQUOTE;
	   }
	   case SDLK_DELETE:
	   {
		   return Keyboard::DEL;
	   }
	   case SDLK_PAGEUP:
	   {
		   return Keyboard::PAGEUP;
	   }
	   case SDLK_PAGEDOWN:
	   {
		   return Keyboard::PAGEDOWN;
	   }
	   case SDLK_HOME:
	   {
		   return Keyboard::HOME;
	   }
	   case SDLK_END:
	   {
		   return Keyboard::END;
	   }
	   case SDLK_INSERT:
	   {
		   return Keyboard::INSERT;
	   }
	   case SDLK_UP:
	   {
		   return Keyboard::UPARROW;
	   }
	   case SDLK_DOWN:
	   {
		   return Keyboard::DOWNARROW;
	   }
	   case SDLK_LEFT:
	   {
		   return Keyboard::LEFTARROW;
	   }
	   case SDLK_RIGHT:
	   {
		   return Keyboard::RIGHTARROW;
	   }
	   case SDLK_CAPSLOCK:
	   {
		   return Keyboard::CAPS;
	   }
	   case SDLK_LSHIFT:
	   {
		   return Keyboard::LSHIFT;
	   }
	   case SDLK_LCTRL:
	   {
		   return Keyboard::LCTRL;
	   }
	   case SDLK_RSHIFT:
	   {
		   return Keyboard::RSHIFT;
	   }
	   case SDLK_RCTRL:
	   {
		   return Keyboard::RCTRL;
	   }
	   case SDLK_F1:
	   {
		   return Keyboard::F1;
	   }
	   case SDLK_F2:
	   {
		   return Keyboard::F2;
	   }
	   case SDLK_F3:
	   {
		   return Keyboard::F3;
	   }
	   case SDLK_F4:
	   {
		   return Keyboard::F4;
	   }
	   case SDLK_F5:
	   {
		   return Keyboard::F5;
	   }
	   case SDLK_F6:
	   {
		   return Keyboard::F6;
	   }
	   case SDLK_F7:
	   {
		   return Keyboard::F7;
	   }
	   case SDLK_F8:
	   {
		   return Keyboard::F8;
	   }
	   case SDLK_F9:
	   {
		   return Keyboard::F9;
	   }
	   case SDLK_F10:
	   {
		   return Keyboard::F10;
	   }
	   case SDLK_F11:
	   {
		   return Keyboard::F11;
	   }
	   case SDLK_F12:
	   {
		   return Keyboard::F12;
	   }

      default:
	   {
		   std::cerr << "SDL Driver Error:  Unknown/Unhandled Key Pressed." << std::endl;
		   return Keyboard::F12;
	   }
   }
}
   
		
	
} // namespace gk
