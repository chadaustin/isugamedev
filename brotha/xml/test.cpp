/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: test.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:08 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */
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

	dataxml::load("test.xml");
	//dataxml::b.xMLify(std::cout);
	//reports::request r("2*/2*/2*");
	//r.print(std::cout);
	std::ostringstream zhende;
	std::cout << "enter brothaPath code:";
	std::string a;
	std::cin >> a;
	zhende << reports::inlineStyle();
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

