#ifndef DIGITAL_INTERFACE
#define DIGITAL_INTERFACE

#include "DeviceInterface.h"
#include "DigitalInput.h"

class DigitalInterface : public DeviceInterface
{
public:
   DigitalInterface() {}
   virtual ~DigitalInterface() {}
};

#endif
