#include <Python.h>
#include <siren/siren.h>

int
main(int argc, char** argv)
{
   try
   {
      // Init the python interpreter
      Py_Initialize();
      PySys_SetArgv(argc, argv);
      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.path.append('../../../src/siren')");

      // Run our python script
      PyRun_SimpleString("import startup");
   }
   catch(std::runtime_error& e)
   {
      std::cerr << "Caught Exception: " << e.what() << std::endl;
   }

   return 0;
}
