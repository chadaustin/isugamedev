// Kernel.h
//
// The Kernel is responsible for setting up a Graphics Context and preparing it for
// use. It will take an App subclass and call appropriate functions (preFrame, draw,
// etc...) on it.

#ifndef _METRO_KERNEL_H_
#define _METRO_KERNEL_H_

#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <SDL/SDL.h>

// TODO: delete this
#include <iostream> // temporary for error reporting. Should use throw/catch or something else.

#include <boost/shared_ptr.hpp> // this is what we want to return the instance with

#include <kernel/App.h> // the App interface

namespace metro
{
	class Kernel
	{
	public:
		// return the singleton instance
		static boost::shared_ptr< Kernel > instance( void );

		// set the app that the kernel tries to run
		void setApp( boost::shared_ptr< App > pApp );

		// start the Kernel running. If the current App is NULL, this will return false and fail
		bool start( void );

		// stop the Kernel. This will perform a clean stop, allowing the App to shut down, etc,
		// and then return control to wherever Kernel::start() was called
		void stop( void );

	private:
		// private constructor for singleton
		Kernel( void );
		// the main draw/update loop. A seperate function only for clarity
		void mainLoop( void );
		// singleton instance
		static boost::shared_ptr< Kernel > mInstance;
		// our app
		boost::shared_ptr< App > mApp;
		// whether we are in the main loop
		bool mLoop;
	};
}

#endif
