#ifndef ABSTRACT_DEVICE_INTERFACE
#define ABSTRACT_DEVICE_INTERFACE

#include <string>

class DeviceInterface
{
public:
   DeviceInterface()
   {
   }
   virtual ~DeviceInterface() {}
   
   /* initialize this interface with the action-event name */
   virtual void init( std::string& event )
   {
      mName = event;
   }

   
public:
   std::string mName;
};

#endif
