#ifndef ANALOG_INPUT
#define ANALOG_INPUT

#include "Input.h"

class AnalogInput : public Input
{
public:
   virtual ~AnalogInput() {}
   virtual void update() {}
};

#endif