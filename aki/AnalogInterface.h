#ifndef ANALOG_INTERFACE
#define ANALOG_INTERFACE

#include "InputInterface.h"
#include "AnalogInput.h"

// TODO: test me (this hasn't been verified to work yet...)
class AnalogInterface : public InputInterface
{
public:
   AnalogInterface() {}
   virtual ~AnalogInterface() {}

   /* get the analog data from the analog device. */
   virtual float getAnalogData()
   {
      // this can surely be optimized...
      Input* in = GameInput::instance().getInput( mAlias );
      AnalogInput* ana = dynamic_cast<AnalogInput*>( in );

      if (ana == NULL)
      {
         return 0.0f;
      }

      return ana->data();
   }
};

#endif
