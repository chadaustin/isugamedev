
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: GameInputConfigure.h,v $
// Date modified: $Date: 2002-05-14 15:52:59 $
// Version:       $Revision: 1.13 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEINPUTCONFIGURE_H
#define GK_GAMEINPUTCONFIGURE_H

#include <gk/gkCommon.h>
#include <iostream>
#include <string>
#include <cppdom/cppdom.h>

#include <gk/IGameKernel.h>

namespace gk {

inline static bool loadInputConfig( const std::string& filename,
                                    IGameKernel* kernel )
{
   assert( kernel != NULL );
   cppdom::XMLContextPtr ctx( new cppdom::XMLContext );
   cppdom::XMLDocument doc( ctx );

   // load a xml document from a file
   try
   {
      doc.loadFile( filename );
   }
   catch (cppdom::XMLError e)
   {
      std::cerr << "Error: " << e.getString() << std::endl;
      if (e.getInfo().size())
      {
         std::cerr << "File: " << e.getInfo() << std::endl;
      }
      if (e.getError() != cppdom::xml_filename_invalid &&
          e.getError() != cppdom::xml_file_access)
      {
         //e.show_error( ctx );
         //e.show_line( ctx, filename );
      }
      return false;
   }

   std::cerr << "Loaded Configuration: " << filename << std::endl;

   cppdom::XMLNodeList nl = doc.getChild( "gameinput" )->getChildren();
   cppdom::XMLNodeListIterator it = nl.begin();
   while (it != nl.end())
   {
      //std::cerr << "in name: " << (*it)->name() << std::endl;
      try
      {
         cppdom::XMLAttributes& attr = (*it)->getAttrMap();
         //std::cout << "attr: " << attr.get( "action" ) << "\n" << std::flush;
         //std::cout << "attr: " << attr.get( "device" ) << "\n" << std::flush;
         //std::cout << "attr: " << attr.get( "input" ) << "\n" << std::flush;
         kernel->getInput()->bind( attr.get( "action" ), attr.get( "device" ), attr.get( "input" ) );
      }
      catch (cppdom::XMLError e)
      {
         std::cerr << "Error: " << e.getString() << std::endl;
         it++;
         continue;
      }
      it++;
   }

   return true;
}

} // namespace gk

#endif
