// test.cpp : Defines the entry point for the console application.
//


/*/
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>

/*/

#include <sstream>
#include <iostream>
#include "xmlpersist.h"
#include "HtmlGen.h"

int main(int argc, char* argv[])
{

	data::load("test.xml");
	//dataxml::b.xMLify(std::cout);
	//reports::request r("2*/2*/2*");
	//r.print(std::cout);
	std::cout << reports::parseHTTPRequest("get /123456790 http/1.0\r\n bla: quag\r\n\r\n") << std::endl;
	std::ostringstream zhende;
	std::cout << "enter brothaPath code:";
	std::string a;
	std::cin >> a;
	zhende << "<font face=verdana><h1>Example:" << a << "</h1>";
	zhende << "<hr><pre>";
	reports::request r(a);
	r.print(zhende);
	zhende << "</pre><hr>";
	zhende << reports::GenerateReport(a);
	std::ofstream f("test.htm");
	f << zhende.str();
	f.close();
 	return 0;   
}

