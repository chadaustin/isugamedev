#include <gk/gkCommon.h>
#include <iostream>
#include <string>
#include <cppdom/cppdom.h>

#include <gk/IGameKernel.h>

namespace gk {

bool GK_DLL loadInputConfig( const std::string& filename,
                                    IGameKernel* kernel )
{
   assert( kernel != NULL );
   cppdom::ContextPtr ctx( new cppdom::Context );
   cppdom::Document doc( ctx );

   // load a xml document from a file
   try
   {
      doc.loadFile( filename );
   }
   catch (cppdom::Error e)
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

   cppdom::NodeList nl = doc.getChild( "gameinput" )->getChildren();
   cppdom::NodeListIterator it = nl.begin();
   while (it != nl.end())
   {
      //std::cerr << "in name: " << (*it)->name() << std::endl;
      try
      {
         cppdom::Attributes& attr = (*it)->getAttrMap();
         //std::cout << "attr: " << attr.get( "action" ) << "\n" << std::flush;
         //std::cout << "attr: " << attr.get( "device" ) << "\n" << std::flush;
         //std::cout << "attr: " << attr.get( "input" ) << "\n" << std::flush;
         kernel->getInput()->bind( attr.get( "action" ), attr.get( "device" ), attr.get( "input" ) );
      }
      catch (cppdom::Error e)
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
