// App.h
//
// App is the abstract class whose type Kernel expects to work with.
// To pass an app to the Kernel, you must inherit this App class,
// implement all the functions (at least you'll CONSCIOUSLY be leaving
// them blank if that's how you choose to go), and pass that in to the
// Kernel.

#ifndef _METRO_APP_H_
#define _METRO_APP_H_

namespace metro
{
	class App
	{
	public:
		virtual void init( void ) = 0;
		virtual void apiInit( void ) = 0;
		virtual void exit( void ) = 0;
		virtual void preFrame( void ) = 0;
		virtual void postFrame( void ) = 0;
		virtual void draw( void ) = 0;
	};
}

#endif
