/*************************************************************************/
/*                                                                       */
/*  Regexx - Regular Expressions C++ solution.                           */
/*                                                                       */
/*  http://projects.nn.com.br/                                           */
/*                                                                       */
/*  Copyright (C) 2000 Gustavo Niemeyer <gustavo@nn.com.br>              */
/*                                                                       */
/*  This library is free software; you can redistribute it and/or        */
/*  modify it under the terms of the GNU Library General Public          */
/*  License as published by the Free Software Foundation; either         */
/*  version 2 of the License, or (at your option) any later version.     */
/*                                                                       */
/*  This library is distributed in the hope that it will be useful,      */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    */
/*  Library General Public License for more details.                     */
/*                                                                       */
/*  You should have received a copy of the GNU Library General Public    */
/*  License along with this library; if not, write to the                */
/*  Free Software Foundation, Inc., 59 Temple Place - Suite 330,         */
/*  Boston, MA  02111-1307, USA.                                         */
/*                                                                       */
/*************************************************************************/

// $Revision: 1.1 $
// $Date: 2001-09-20 03:41:36 $

#include <iostream>
#include <regexx.hh>

using namespace regexx;

//
// This is the function to pass to replace() in
// example 6. It must accept a RegexxMatch as the
// only parameter and return the string to replace.
//
std::string invert(const RegexxMatch& _match)
{
  if(_match == "free")
    return "expensive";
  else
    return "free";
}

int main()
{
  Regexx rxx;

  try {

    // 1 - Replacing strings with atom substitution:
    
    std::cout << "1: ";
    std::cout << rxx.replace("I love expensive software!","expensive (soft[a-z]*)",
			"free %0");
    std::cout << std::endl;


    // 2 - Atom retrieving:

    std::cout << "2: ";
    rxx.exec("http://distro.conectiva.com/projetos/32/","http://([-1-9a-zA-Z\\.]*)/");
    if(rxx.match.size() > 0 && rxx.match[0].atom.size() > 0)
      std::cout << "Regexx's host is " << rxx.match[0].atom[0] << "." << std::endl;
    else
      std::cout << "Oops, no hosts found!" << std::endl;


    // 3 - Patern matching:

    std::cout << "3: ";
    if(rxx.exec("gnu@gnu.org",".+@gnu\\.org$"))
      std::cout << "Yeah! It's from gnu.org!" << std::endl;
    else
      std::cout << "No, it's not from gnu.org." << std::endl;


    // 4 - Counting occurrences:

    std::cout << "4: ";
    std::cout << "There are "
	 << rxx.exec("There are n 'a's in this phrase.",
		     "a",Regexx::global|Regexx::nomatch)
	 << " 'a's in this phrase." << std::endl;


    // 5 - Removing HTML tags:

    std::cout << "5: ";
    std::cout << rxx.replace("<B>Please, <STRIKE>no</STRIKE> tags.</B>",
			"</?[a-z]+( [^>]*)*>", "",
			Regexx::global|Regexx::nocase|Regexx::study);
    std::cout << std::endl;


    // 6 - Customizing replaces

    std::cout << "6: ";
    std::cout << rxx.replacef("Turn your free software into expensive software.",
			 "free|expensive", invert, Regexx::global);
    std::cout << std::endl;


    // 7 - One-line regular expressions using constructors

    std::cout << "7: ";
    if(Regexx("Using constructor!","constructor"))
      std::cout << "I've found the 'constructor' word!" << std::endl;
    else
      std::cout << "I haven't found the 'constructor' word!" << std::endl;

  }
  catch(Regexx::CompileException &e) {
    std::cerr << e.message() << std::endl;
  }
  return 0;
}
