#ifndef DIGITAL_DEVICE
#define DIGITAL_DEVICE

#include "Device.h"
#include "DigitalInput.h"

/* a digital device
 * a keyboard, mouse, or joystick (for example) may be a digital device
 * a digital device can contain many inputs (or buttons)
 */
class DigitalDevice : public TypedDevice<DigitalInput>
{
public:
   DigitalDevice() {}
   DigitalInput& button( int x ) { return *((DigitalInput*)TypedDevice<DigitalInput>::getInput( x )); }
   DigitalInput* button( const std::string& x ) { return (DigitalInput*)TypedDevice<DigitalInput>::getInput( x ); }
};

#endif
