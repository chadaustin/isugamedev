#include <kernel/Kernel.h>

namespace metro
{
	boost::shared_ptr< Kernel > Kernel::mInstance;

	boost::shared_ptr< Kernel > Kernel::instance(void)
	{
		if ( mInstance == NULL )
			mInstance = boost::shared_ptr< Kernel >( new Kernel() );
		return boost::shared_ptr< Kernel >(mInstance);
	}

	void Kernel::setApp( boost::shared_ptr< App > pApp )
	{
		if ( mApp != NULL )
			return; // for now, fail on hot-swapping apps, because that should be done more carefully

		mApp = pApp;
	}

	bool Kernel::start( void )
	{
		// if the App is null, we fail and return false so the caller knows nothing happened
		if ( mApp == NULL )
			return false;

		// get our app going, and do any of our own non-api init stuff
		mApp->init();

		// init SDL, create a window, etc
		// Initialize SDL for video output
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
			exit( 1 );
		}

		// Create a 640x480 OpenGL screen
		if ( SDL_SetVideoMode( 640, 480, 0, SDL_OPENGL ) == NULL )
		{
			std::cerr << "Unable to create OpenGL screen: " << SDL_GetError() << std::endl;
			SDL_Quit();
			exit( 2 );
		}

		// Set the title bar in environments that support it
		SDL_WM_SetCaption( "Metropolis", NULL );

		// init the opengl context
		glViewport( 0, 0, 640, 480 ); // TODO: base these values off of some config file or something
		glClearColor( 0.0, 0.0, 0.0, 0.0 );
		glClearDepth( 1.0 );
		glDepthFunc( GL_LESS );
		glEnable( GL_DEPTH_TEST );
		glShadeModel( GL_SMOOTH );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		gluPerspective( 45.0f, (GLfloat) 640 / (GLfloat) 480, 0.1, 100.0 );

		glMatrixMode( GL_MODELVIEW );

		// now that SDL and OpenGL are up, let the App do api init work
		mApp->apiInit();

		// prepare to enter the main loop
		mLoop = true;

		mainLoop();
	}

	// TODO: should this even exist in this form? Right now cleanup just happens in mainLoop()
	// after the while( mLoop ) is done, but maybe that should become the stop function instead?
	void Kernel::stop( void )
	{
		mLoop = false;
	}

	Kernel::Kernel( void ) :
		mLoop( false )
	{}

	void Kernel::mainLoop( void )
	{
		while ( mLoop )
		{
			// DRAWING CODE

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glLoadIdentity();

			// update our app
			mApp->preFrame();

			// draw!
			mApp->draw();

			// swap buffers to display, since we're double buffered.
			SDL_GL_SwapBuffers();

			// END DRAWING CODE

			mApp->postFrame();

			// TODO: seperate input out into a input map or something like that
			SDL_Event event;
			while ( SDL_PollEvent( &event ) )
			{
				if ( event.type == SDL_QUIT )
				{
					mLoop = false;
				}
				if ( event.type == SDL_KEYDOWN )
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE )
					{
						mLoop = false;
					}
				}
			}
		} // end while ( mLoop )

		// TODO: put all cleanup calls here, because once this is done the Kernel is stopped.
		// should this be a seperate exit() func?
		mApp->exit();
		SDL_Quit();
	}
}
