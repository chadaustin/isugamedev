#ifndef ANALOG_INTERFACE
#define ANALOG_INTERFACE

#include "InputInterface.h"
#include "AnalogInput.h"

class AnalogInterface : public InputInterface
{
public:
   AnalogInterface() {}
   virtual ~AnalogInterface() {}
   
   /* get the analog data from the analog device. */
   virtual float getAnalogData()
   {
      // this can surely be optimized...
      AnalogInput* ana = GameInput::instance().getInput( mDevice, mInput );

      if (ana == NULL)
         return 0.0f;

      return ana->getAnalogData();
   }
};

#endif
