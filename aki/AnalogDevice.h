#ifndef ANALOG_DEVICE
#define ANALOG_DEVICE

#include "Device.h"
#include "AnalogInput.h"

/* an analog device
 * a mouse, or joystick (for example) may be an analog device
 * an analog device can contain many inputs (or axes)
 */
class AnalogDevice : public TypedDevice<AnalogInput>
{
public:
   AnalogDevice() {}
   AnalogInput& axis( int x )
   { 
      Input* in = TypedDevice<AnalogInput>::getInput( x );
      return *dynamic_cast<AnalogInput*>( in );
   }
   AnalogInput* axis( const std::string& x ) 
   { 
      Input* in = TypedDevice<AnalogInput>::getInput( x );
      return dynamic_cast<AnalogInput*>( in );
   }
};

#endif
