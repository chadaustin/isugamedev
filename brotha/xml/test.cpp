// test.cpp : Defines the entry point for the console application.
//


//
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>

//
#include <iostream>
#include "xmlpersist.h"
#include "HtmlGen.h"

int main(int argc, char* argv[])
{

	dataxml::load("test.xml");
	//dataxml::b.xMLify(std::cout);
	//reports::request r("2*/2*/2*");
	//r.print(std::cout);
	std::cout << "some examples:<hr>";
	std::cout << "2*/2*/2*<br>";
	std::cout << reports::GenerateReport("2*/2*/2*");
	std::cout << "<hr>1*/1*/1*<hr>";
	std::cout << reports::GenerateReport("1*/1*/1*");
	std::cout << "<hr>0*/2*/2*<hr>";
	std::cout << reports::GenerateReport("0*/2*/2*");
	std::cout << "<hr>0*/2reflect/0*<hr>";
	std::cout << reports::GenerateReport("0*/2reflect/0*");
 	return 0;   
}

