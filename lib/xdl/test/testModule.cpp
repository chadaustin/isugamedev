#include <iostream>
#include "xdl.h"

// need to do the extern or the func will be exported with a mangled name...
extern "C"
{

XDL_FUNC void* createInterface()
{
   std::cout<<"executing createInterface()\n"<<std::flush;
   // return junk
   return new char[512];
}

};
