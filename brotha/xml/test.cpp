// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "xmlpersist.h"
#include "HtmlGen.h"

int _tmain(int argc, _TCHAR* argv[])
{

	dataxml::load("test.xml");
	dataxml::b.xMLify(std::cout);
	reports::request r("3reflect/3*/2hohoma");
	r.print(std::cout);
 	return 0;   
}

