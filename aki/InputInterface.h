#ifndef ABSTRACT_INPUT_INTERFACE
#define ABSTRACT_INPUT_INTERFACE

#include <string>

class InputInterface
{
public:
   InputInterface()
   {
   }
   virtual ~InputInterface() {}
   
   /* initialize this interface with the alias to the input */
   virtual void init( const std::string& alias )
   {
      mAlias = alias;
   }

   
public:
   std::string mAlias;
};

#endif
