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
