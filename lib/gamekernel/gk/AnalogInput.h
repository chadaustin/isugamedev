#ifndef ANALOG_INPUT
#define ANALOG_INPUT

#include "Input.h"

class AnalogInput : virtual public Input
{
public:
   AnalogInput() : mCurrent( 0 ), mFuture( 0 ),
                   mNeedToCallUpdate( false ), mDelta( 0 )
   {
   }

   virtual ~AnalogInput() {}
   virtual void update();

   // return the analog data
   virtual float data() const { return mCurrent; }

public:
   // Set the position of the Mouse object
   // Call this on a Mouse-Move event (when the mouse moves)
   // give - x and y mouse coordinates
   void        setData( const float& x );

   void        addOffset( const float& x );

   // return the previous x position of the mouse.
   float         old() const;

   // Get the previous position of mouse
   float         previous() const;

   // Get the change between mouse's previous and current positions
   float         offset() const;

   // Private member data
private:
   float  mCurrent, mFuture, mDelta;
   bool mNeedToCallUpdate;
};

// return the previous x position of the mouse.
inline float AnalogInput::previous() const
{
   assert( mNeedToCallUpdate == false && "you need to call AnalogInput::update once per frame" );
   return mCurrent - mDelta;
}

// get the change between mouse's previous and current x positions
inline float AnalogInput::offset() const
{
   assert( mNeedToCallUpdate == false && "you need to call AnalogInput::update once per frame" );
   return mDelta;
}

// set the position that the mouse is currently
// you must call update() before you are ready to "get" position
inline void AnalogInput::setData( const float& x )
{
   mNeedToCallUpdate = true;
   mFuture = x;
}

inline void AnalogInput::addOffset( const float& x )
{
   mNeedToCallUpdate = true;
   mFuture += x;
}

//: Call this on every frame of your simulation
// Mouse events include position change, and button change
inline void AnalogInput::update()
{
   mNeedToCallUpdate = false;

   //get the offset the mouse has moved
   mDelta = mFuture - mCurrent;

   // save the new current position
   mCurrent = mFuture;
}

#endif
