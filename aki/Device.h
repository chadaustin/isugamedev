#ifndef DEVICE
#define DEVICE

#include <string>
#include "Input.h"
class Device
{
public:
   Device() {}
   virtual ~Device() {}
   virtual Input* getInput( const std::string& s ) = 0;
   virtual Input* getInput( const int& id ) = 0;
   virtual void update() = 0;
};

template< typename bok >
class TypedDevice : virtual public Device
{
public:
   TypedDevice() {}
   virtual ~TypedDevice() {}
   
   void setNumInputs( int n )
   {
      mInput.resize( n );
   }  
   
   virtual Input* getInput( const std::string& input_name )
   {
      int k = 0;
      if (mMap.count( input_name ) > 0)
      {
         k = (*(mMap.find( input_name ))).second;
         return &mInput[k];
      }
      else
         return NULL;
   }   
   
   virtual Input* getInput( const int& id )
   { 
      return &mInput[id];
   }
   
   virtual void update()
   {
      for (int x = 0; x < mInput.size(); ++x)
      {
         mInput[x].update();
      }
   }
   
   std::vector< bok > mInput;
   std::map< std::string, unsigned int > mMap;
};

#endif
