#ifndef DIGITAL_DEVICE
#define DIGITAL_DEVICE

#include "Device.h"
#include "DigitalInput.h"

/* a digital device
 * a keyboard, mouse, or joystick (for example) may be a digital device
 * a digital device can contain many inputs (or buttons)
 */
class DigitalDevice : public Device
{
public:
   DigitalDevice() {}
   
   /* lookup button by input number */
   const DigitalInput& button( const int& b ) const  { return mButton[b]; }

   /* lookup button by input number */
   DigitalInput& button( const int& b ) { return mButton[b]; }
   
   /* lookup button by string */
   const DigitalInput& button( const std::string& name ) const
   {
      int k = 0;
      if (mMap.count( name ) > 0)
         k = (*(mMap.find( name ))).second;
      return mButton[k];
   }
   
   /* lookup button by string */
   DigitalInput& button( const std::string& name )
   {
      int k = 0;
      if (mMap.count( name ) > 0)
         k = (*(mMap.find( name ))).second;
      return mButton[k];
   }
   
   virtual void setNumInputs( int n )
   {
      mButton.resize( n );
   }   
   
   virtual void update()
   {
      for (int x = 0; x < mButton.size(); ++x)
      {
         mButton[x].updateEdgeStates();
      }
   }
   
protected:
   std::vector< DigitalInput > mButton;
   std::map< std::string, unsigned int > mMap;
};

#endif
