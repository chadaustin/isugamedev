
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
// Date modified: $Date: 2002-02-21 18:59:29 $
// Version:       $Revision: 1.10 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEINPUTCONFIGURE_H
#define GK_GAMEINPUTCONFIGURE_H

#include "gk/gkCommon.h"
#include <iostream>
#include <string>
#include "xmlpp/xmlpp.h"

#include "gk/GameInput.h"
#include "gk/GameKernel.h"

namespace gk {

inline static bool loadInputConfig( const std::string& filename,
                                    GameKernel* kernel )
{
   assert( kernel != NULL );
   xmlpp::XMLContextPtr ctx( new xmlpp::XMLContext );
   xmlpp::XMLDocument doc( ctx );

   // load a xml document from a file
   try
   {
      doc.load_file( filename );
   }
   catch (xmlpp::xmlerror e)
   {
      std::cerr << "Error: " << e.get_string() << std::endl;
      if (e.get_info().size())
      {
         std::cerr << "File: " << e.get_info() << std::endl;
      }
      if (e.get_error() != xmlpp::xml_filename_invalid &&
          e.get_error() != xmlpp::xml_file_access)
      {
         //e.show_error( ctx );
         //e.show_line( ctx, filename );
      }
      return false;
   }

   std::cerr << "Loaded Configuration: " << filename << std::endl;

   xmlpp::XMLNodeList nl = doc.getChild( "gameinput" )->getChildren();
   xmlpp::XMLNodeListIterator it = nl.begin();
   while (it != nl.end())
   {
      //std::cerr << "in name: " << (*it)->name() << std::endl;
      try
      {
         xmlpp::XMLAttributes& attr = (*it)->get_attrmap();
         //std::cout << "attr: " << attr.get( "action" ) << "\n" << std::flush;
         //std::cout << "attr: " << attr.get( "device" ) << "\n" << std::flush;
         //std::cout << "attr: " << attr.get( "input" ) << "\n" << std::flush;
         kernel->getInput()->bind( attr.get( "action" ), attr.get( "device" ), attr.get( "input" ) );
      }
      catch (xmlpp::xmlerror e)
      {
         std::cerr << "Error: " << e.get_string() << std::endl;
         it++;
         continue;
      }
      it++;
   }

   return true;
}

} // namespace gk

#endif
