#ifndef DIGITAL_INTERFACE
#define DIGITAL_INTERFACE

#include "InputInterface.h"
#include "DigitalInput.h"

class DigitalInterface : public InputInterface
{
public:
   DigitalInterface() {}
   virtual ~DigitalInterface() {}
   
   /* get the analog data from the analog device. */
   virtual DigitalInput::EdgeTriggerState getDigitalData()
   {
      // this can surely be optimized...
      Input* in = GameInput::instance().getInput( mAlias );
      DigitalInput* dig = dynamic_cast<DigitalInput*>( in );
      
      if (dig == NULL)
         return DigitalInput::UP;

      return dig->edgeState();
   }
};

#endif
