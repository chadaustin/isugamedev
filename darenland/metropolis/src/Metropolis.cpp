// Metropolis.cpp
//
// This file will have our main() func, and that's about it.

#include <iostream>

#include <boost/shared_ptr.hpp>

#include <kernel/Kernel.h>
#include <kernel/App.h>

#include "TestApp.cpp"

int main( int *argc, char **argv )
{

	std::cout << "Metropolis runs!" << std::endl;

	metro::Kernel::instance()->setApp( boost::shared_ptr< metro::App >( new TestApp() ) );
	metro::Kernel::instance()->start();

	return 0;
}
