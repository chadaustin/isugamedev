#include "xdl.h"

typedef void* (*MyFunc)();

#ifdef USE_WIN32
const char* testLib = "test.dll";
#elif USE_UNIX
const char* testLib = "test.so";
#endif

int main()
{
   xdl::Library lib;

   if (lib.open( testLib ))
   {
      void* func = lib.lookup( "createInterface" );
      if (func != NULL)
      {
         MyFunc createInterface = (MyFunc)func;
         char* memory = (char*)createInterface();
         delete [] memory;
      } else {
         std::cout<<"symbol lookup failed"<<std::endl;
      }

      lib.close();
   }
   else
   {
      std::cout<<"couldn't open\n"<<std::flush;
   }

   return 1;
}
