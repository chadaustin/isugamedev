// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "xmlpersist.h"

int _tmain(int argc, _TCHAR* argv[])
{

	dataxml::load("test.xml");
	dataxml::b.xMLify(std::cout);
 	return 0;   
}

