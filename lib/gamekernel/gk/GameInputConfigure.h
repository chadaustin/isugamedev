#ifndef GAMEINPUT_CONFIGURE
#define GAMEINPUT_CONFIGURE

#include "gk/gkCommon.h"
#include <iostream>
#include <string>
#include "xmlpp.h"

#include "gk/GameInput.h"

namespace gk
{
   inline static bool loadInputConfig( const std::string& filename ) 
   {
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
            e.show_error( ctx );
            e.show_line( ctx, filename );
         }
         return false;
      }

      std::cerr << "Loaded Configuration: " << filename << std::endl;

      xmlpp::XMLNodeList nl = doc.firstchild( "gameinput" )->children();
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
            GameInput::instance().bind( attr.get( "action" ), attr.get( "device" ), attr.get( "input" ) );
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
} // end namespace

#endif
