#ifndef DIGITAL_INPUT
#define DIGITAL_INPUT

#include "Input.h"

class DigitalInput : public Input
{
public:
   virtual ~DigitalInput() {}
 
   enum BinaryState
   {
      ON, OFF
   };
   enum EdgeTriggerState
   {
      DOWN, EDGE_DOWN, EDGE_UP, UP, FLOATING
   };
      
   DigitalInput() : mEdge( UP ), mBinary( OFF )
   {
   }
   
   virtual void update() {}
   
   
   EdgeTriggerState& edgeState()
   {
      return mEdge;
   }
   
   const EdgeTriggerState& edgeState() const
   {
      return mEdge;
   }
  
   const BinaryState& binaryState() const
   {
      return mBinary;
   }
   
   BinaryState& binaryState()
   {
      return mBinary;
   }
   
   void updateEdgeStates()
   {
      //find out if...
      switch( mBinary )
      {
      case ON:
         //button has been held down or it is just down.
         switch( mEdge )
         {
         case FLOATING:
         case EDGE_UP:
         case UP:       mEdge = EDGE_DOWN;  break;
         case EDGE_DOWN: mEdge = DOWN; break;
         }
      break;

      case OFF:
         //button has been up or it is just up.
         switch( mEdge )
         {
         case FLOATING:
         case EDGE_DOWN:
         case DOWN:    mEdge = EDGE_UP; break;
         case EDGE_UP:  mEdge = UP; break;
         }
      break;

      default: 
         //std::cout<<"broken on key: "<<x<<" of "<<mBinarys.size()<<" == "<<mBinarys[x]<<"\n"<<std::flush;
         assert(false);
      }
   }
   
private:
   EdgeTriggerState mEdge;
   BinaryState mBinary;
};

#endif
