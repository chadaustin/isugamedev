#include "dirlist.h"
#include <iostream>

int main( int argc, char** argv )
{
   if ( argc != 2 ) {
      std::cerr<<"Syntax: dirlist_test directory"<<std::endl;
      return 1;
   }

   std::vector<std::string> files;
   if ( ! xdl::dirlist( argv[1], files )) {
      std::cerr<<"Directory listing failed"<<std::endl;
      return 1;
   }

   std::cout<<argv[1]<<" has "<<files.size()<<" files."<<std::endl;
   for( int i=0; i<files.size(); i++ ) {
      std::cout<<files[i]<<std::endl;
   }
   return 0;
}
