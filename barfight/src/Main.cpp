/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* barfight-cpr beg
 *
 * barfight - an all-out brawl in the local pub
 * barfight is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * -----------------------------------------------------------------
 * File:          $RCSfile: Main.cpp,v $
 * Date modified: $Date: 2003-06-02 17:38:45 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ********************************************************** barfight-cpr-end */
#include <stdexcept>
#include <iostream>
#include <Python.h>

int main(int argc, char** argv)
{
   try
   {
      // Init the python interpreter
      Py_Initialize();
      PySys_SetArgv(argc, argv);
      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.path.insert(0, 'lib')");

      // Startup the game
      PyRun_SimpleString("import barfight");
   }
   catch(std::runtime_error& e)
   {
      std::cerr << "Caught exception: " << e.what() << std::endl;
      return 1;
   }

   return 0;
}

#ifdef WIN32
#  include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   return main(__argc, __argv);
}

#endif
