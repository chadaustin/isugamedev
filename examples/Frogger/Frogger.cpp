/////////////////////////////////////////////////////
// Copyright 2002 Levi VanOort Released under MIT
//			-- lvanoort@aol.com -- 
//				4/4/2002
//
// Frogger.cpp
/////////////////////////////////////////////////////
#include <stdlib.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "GameWorld.h"


//Globals
enum Movement{NONE = 0, LEFT, RIGHT, UP, DOWN};



// Global externals
int WindowSizeX = 663;
int WindowSizeY = 470;
int LaneSize = 36;
int FrogZone;
int CurrentLevel = 1;
Movement FrogMove = NONE;
///////////////////////


int start_clock_count = SDL_GetTicks();
int temp = 0;

// Game Object
GameWorld Frogger;

void display();


void update()
{
	//Need to fix this being frame locked on 30 fps
	//while(SDL_GetTicks()-start_clock_count < 30)
	//{
	    display();
	//}
	start_clock_count = SDL_GetTicks();
	Frogger.Update();

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Frogger.Draw();
	SDL_GL_SwapBuffers();
}


void init()
{
	glViewport(0,0,(GLsizei) WindowSizeX, (GLsizei) WindowSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble) WindowSizeX, 0.0, (GLdouble) WindowSizeY);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0,0.0,0.0,0.0);
}


int main()
{
    bool quit = false; 
  
    /* Dimensions of our window. */
    int width = 0;
    int height = 0;
    /* Color depth in bits of our window. */
    int bpp = 24;
    /* Flags we will pass into SDL_SetVideoMode. */
    int flags = 0;

    /* First, initialize SDL's video subsystem. */
    SDL_Init(SDL_INIT_VIDEO);

    /*
     * Now, we want to setup our requested
     * window attributes for our OpenGL window.
     * We want *at least* 5 bits of red, green
     * and blue. We also want at least a 16-bit
     * depth buffer.
     *
     * The last thing we do is request a double
     * buffered window. '1' turns on double
     * buffering, '0' turns it off.
     *
     * Note that we do not use SDL_DOUBLEBUF in
     * the flags to SDL_SetVideoMode. That does
     * not affect the GL attribute state, only
     * the standard 2D blitting setup.
     */
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /*
     * We want to request that SDL provide us
     * with an OpenGL window, in a fullscreen
     * video mode.
     *
     * EXERCISE:
     * Make starting windowed an option, and
     * handle the resize events properly with
     * glViewport.
     */
    flags = SDL_OPENGL;

    /*
     * Set the video mode
     */
    SDL_SetVideoMode( WindowSizeX, WindowSizeY, bpp, flags );

    SDL_Event event;
    
    init(); 
    while(!quit)
    {
	while( SDL_PollEvent( &event ) )
	{
	    switch( event.type )
	    {
		case SDL_KEYDOWN:
		/* Check the SDLKey values and move change the coords */
		    switch( event.key.keysym.sym )
		    {
			case SDLK_LEFT:
			    FrogMove = LEFT;
			    break;
			case SDLK_RIGHT:
			    FrogMove = RIGHT;
			    break;
			case SDLK_UP:
			    FrogMove = UP;
			    FrogZone++;
			    break;
			case SDLK_DOWN:
			    if (FrogZone == 0)
			    	FrogMove = NONE;

			    else
			    {
				FrogMove = DOWN;
				FrogZone--;
			    }
			    break;
			case SDLK_ESCAPE:
			    quit = true;
                    default:
                        break;
		    }
		 break;
	
		default:
		    break;
	    }
	}
	update();
    }
    SDL_Quit();
}

