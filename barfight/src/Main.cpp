/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* barfight-cpr beg
 *
 * barfight - a slapstick drag-out brawl at the local pub
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
 * Date modified: $Date: 2003-02-24 00:43:33 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** barfight-cpr-end */
#include <memory>
#include <stdexcept>
#include <siren/siren.h>

#include "GameState.h"

int
main(int argc, char** argv)
{
   try
   {
      // Register the states
      new siren::StateCreatorImpl<bar::GameState>("Game");

      // Create the kernel and get it going
      std::auto_ptr<siren::Kernel> kernel(new siren::Kernel());
      kernel->start("Game");
   }
   catch(std::runtime_error& e)
   {
      std::cerr << "Caught Exception: " << e.what() << std::endl;
   }

   return 0;
}


#ifdef WIN32

#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   return main(__argc, __argv);
}

#endif
