#ifndef DEVICE
#define DEVICE

class Device
{
public:
   Device() {}
   virtual ~Device() {}
   virtual void setNumInputs( int n ) = 0;
   virtual void update() = 0;
};

#endif
