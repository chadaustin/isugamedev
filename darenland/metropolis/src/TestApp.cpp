#include <iostream>

#include <kernel/App.h>
#include <reality/World.h>
#include "stdlib.h"	//for srand


class TestApp : public metro::App
{
public:
		virtual void init( void )
		{
			srand(42);
			metro::World::instance().initHardcoded();
			std::cerr << "init running" << std::endl;
		}

		virtual void apiInit( void )
		{
			std::cerr << "apiInit running" << std::endl;
		}

		virtual void exit( void )
		{
			std::cerr << "exit running" << std::endl;
		}

		virtual void preFrame( void )
		{
			metro::World::instance().update(1);
		}

		virtual void postFrame( void )
		{

		}

		virtual void draw( void )
		{
			metro::World::instance().draw();
		}
};
