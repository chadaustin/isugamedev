#ifndef DEVICE
#define DEVICE

#include <string>
#include "Input.h"
class Device
{
public:
   Device() {}
   virtual ~Device() {}
   virtual void setNumInputs( int n ) = 0;
   virtual Input* getInput( const std::string& s ) = 0;
   virtual void update() = 0;
};

#endif
