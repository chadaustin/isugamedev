
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     Mouse     =-
//
// Description: "Useful mouse class, keeps track of button 
//               states such as edge triggering, 
//               and keeps track of previous position, 
//               and change in position"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Mouse.h,v $
//    $Date: 2002-01-28 09:17:12 $
//    $Revision: 1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////

//////////////////////////////////////////////////////////////////////////////
#ifndef MOUSE_INCLUDED
#define MOUSE_INCLUDED

#include <assert.h>

//: Mouse class
// keeps track of mouse position and button state in a simulation
// you must call update() each frame of your simulation
// before you read any data from Mouse (like position and button states)
class Mouse
{
// Types
public:
    enum Button
    {
      LEFT = 0, MIDDLE = 1, RIGHT = 2
    };
    
    enum EdgeTriggerState
    {
      EDGE_DOWN, DOWN, EDGE_UP, UP, FLOATING
    };
    
    enum BinaryState
    {
      ON, OFF
    };
    
// Required methods for promised functionality:
public:
    //Constructor.
    Mouse();
    
    //: Call this on every frame of your simulation
    // Mouse events include position change, and button change
   // you must call update() each frame of your simulation
   // before you read any data from Mouse (like position and button states)

    void       update();
    
    // Set the binary state of the button, ON or OFF
    // call this on every Mouse event
    // (a button change or position change)
    // give - b:     Mouse::LEFT or Mouse::MIDDLE or Mouse::RIGHT
    // give - state: Mouse::ON or Mouse::OFF
    // result - updates internal data, 
    //          after this call the edge trigger states are valid.
    void       setState( const Button& b, 
                           const Mouse::BinaryState& state);

    // Set the position of the Mouse object
    // Call this on a Mouse-Move event (when the mouse moves)
    // give - x and y mouse coordinates
    void       setPosition( const int& x, const int& y );
    
    void       addOffset( const int& x, const int& y );
    
// Preferred methods - total flexibility
public:
    // Get the edge triggered state of the button
    // returns - Mouse::EDGE_DOWN or Mouse::EDGE_UP, etc...
    const EdgeTriggerState& leftEdgeState() const;
    const EdgeTriggerState& middleEdgeState() const;
    const EdgeTriggerState& rightEdgeState() const;
    
    // Get the binary state of the button
    // returns - Mouse::ON or Mouse::OFF
    const BinaryState&       leftBinaryState() const;
    const BinaryState&       middleBinaryState() const;
    const BinaryState&       rightBinaryState() const;
    
    const EdgeTriggerState& edgeState( const Mouse::Button& b ) const { return mEdge[b]; }
    const BinaryState& binaryState( const Mouse::Button& b ) const { return mBinary[b]; }
    
    // return the x position of the mouse.
    const int&          x() const;
    
    // return the y position of the mouse.
    const int&          y() const;
    
    // return the previous x position of the mouse.
    int              xOld() const;
    
    // return the previous y position of the mouse.
    int              yOld() const;
    
    // get the change between mouse's previous and current x positions
    const int&          dx() const;
    
    // get the change between mouse's previous and current y positions
    const int&          dy() const;

// Alternate Methods
public:
    // Get the mouse position
    // result - x and y are in viewport coordinates
    void          getPosition( int& x, int& y ) const;
    
    // Get the previous position of mouse
    void          getPreviousPosition( int& x, int& y ) const;

    // Get the change between mouse's previous and current positions
    void getOffset( int& xOffset, int& yOffset ) const;

// Private member data
private:
    int             _xCurrent, _xFuture, _xDelta;
    int             _yCurrent, _yFuture, _yDelta;
    BinaryState          mBinary[3];
    EdgeTriggerState       mEdge[3];
    bool mNeedToCallUpdate;
};



//Constructor.
inline Mouse::Mouse() : 
       _xCurrent( 0 ), _yCurrent( 0 ), _xFuture( 0 ), _yFuture( 0 ), 
       mNeedToCallUpdate( false )
{
   mEdge[Mouse::LEFT] = Mouse::UP;
   mEdge[Mouse::MIDDLE] = Mouse::UP; 
   mEdge[Mouse::RIGHT] = Mouse::UP;
   
   mBinary[Mouse::LEFT] = Mouse::OFF;
   mBinary[Mouse::MIDDLE] = Mouse::OFF;
   mBinary[Mouse::RIGHT] = Mouse::OFF;
}

// Get the state of the button
inline const Mouse::EdgeTriggerState& Mouse::leftEdgeState() const
{
   assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
   return mEdge[Mouse::LEFT];
}
inline const Mouse::EdgeTriggerState& Mouse::middleEdgeState() const
{
   assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
    return mEdge[Mouse::MIDDLE];
}
inline const Mouse::EdgeTriggerState& Mouse::rightEdgeState() const
{
   assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
    return mEdge[Mouse::RIGHT];
}
inline const Mouse::BinaryState& Mouse::leftBinaryState() const
{
   assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
    return mBinary[Mouse::LEFT];
}
inline const Mouse::BinaryState& Mouse::middleBinaryState() const
{
   assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
    return mBinary[Mouse::MIDDLE];
}
inline const Mouse::BinaryState& Mouse::rightBinaryState() const
{
   assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
    return mBinary[Mouse::RIGHT];
}



// return the x position of the mouse.
inline const int& Mouse::x() const
{
    assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
   return _xCurrent;
}

// return the y position of the mouse.
inline const int& Mouse::y() const
{
    assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
   return _yCurrent;
}

// get the mouse position
// you must call update() before you are ready to "get" position
inline void Mouse::getPosition( int& x, int& y ) const
{
    x = this->x();
    y = this->y();
}

// return the previous x position of the mouse.
inline int Mouse::xOld() const
{
   assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
    return _xCurrent - _xDelta;
}

// return the previous y position of the mouse.
inline int Mouse::yOld() const
{
    assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
   return _yCurrent - _yDelta;
}

// get the change between mouse's previous and current x positions
inline const int& Mouse::dx() const
{
    assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
   return _xDelta;
}

// get the change between mouse's previous and current y positions
inline const int& Mouse::dy() const
{
    assert( mNeedToCallUpdate == false && "you need to call Mouse::update once per frame" );
   return _yDelta;
}

// set the position that the mouse is currently
// you must call update() before you are ready to "get" position
inline void Mouse::setPosition( const int& x, const int& y )
{
   mNeedToCallUpdate = true;
    _xFuture = x;
    _yFuture = y;
}

inline void Mouse::addOffset( const int& x, const int& y )
{
   mNeedToCallUpdate = true;
   _xFuture += x;
   _yFuture += y;
}

// get the previous position of mouse
inline void Mouse::getPreviousPosition( int& x, int& y ) const
{
    x = this->xOld();
    y = this->yOld();
}

// get the offset between mouse's previous and current positions
inline void Mouse::getOffset( int& xOffset, int& yOffset ) const
{
    xOffset = this->dx();
    yOffset = this->dy();
}

inline void Mouse::setState( const Button& b, 
                             const Mouse::BinaryState& state )
{
    //set the binary state for button 'b'
    switch( b )
    {
    case LEFT:   mBinary[Mouse::LEFT] = state;  break;
    case MIDDLE: mBinary[Mouse::MIDDLE] = state;break;
    case RIGHT:  mBinary[Mouse::RIGHT] = state; break;
    default: assert( false );
    }
}

//: Call this on every frame of your simulation
// Mouse events include position change, and button change
inline void Mouse::update()
{
   mNeedToCallUpdate = false;
   
    //find out if...
    switch( mBinary[Mouse::LEFT] )
    {
    case ON:
      //button has been held down or it is just down.
      switch( mEdge[Mouse::LEFT] )
      {   
      case EDGE_UP:
      case UP:    mEdge[Mouse::LEFT] = EDGE_DOWN;  break;
      case EDGE_DOWN:mEdge[Mouse::LEFT] = DOWN; break;
      }
      break;
   
    case OFF:
      //button has been up or it is just up.
      switch( mEdge[Mouse::LEFT] )
      {
      case EDGE_DOWN:
      case DOWN:  mEdge[Mouse::LEFT] = EDGE_UP; break;
      case EDGE_UP:  mEdge[Mouse::LEFT] = UP; break;
      }
      break;

    default: assert(false);
    }
    
    //find out if...
    switch( mBinary[Mouse::MIDDLE] )
    {
    case ON:
       //button has been held down or it is just down.
       switch( mEdge[Mouse::MIDDLE] )
       {   
       case EDGE_UP:
       case UP:    mEdge[Mouse::MIDDLE] = EDGE_DOWN;  break;
       case EDGE_DOWN:mEdge[Mouse::MIDDLE] = DOWN; break;
       }
       break;
   
    case OFF:
      //button has been up or it is just up.
      switch( mEdge[Mouse::MIDDLE] )
      {
      case EDGE_DOWN:
      case DOWN:  mEdge[Mouse::MIDDLE] = EDGE_UP; break;
      case EDGE_UP:  mEdge[Mouse::MIDDLE] = UP; break;
      }
      break;

    default: assert(false);
    }
    
    //find out if...
    switch( mBinary[Mouse::RIGHT] )
    {
    case ON:
      //button has been held down or it is just down.
      switch( mEdge[Mouse::RIGHT] )
      {   
      case EDGE_UP:
      case UP:    mEdge[Mouse::RIGHT] = EDGE_DOWN;  break;
      case EDGE_DOWN:mEdge[Mouse::RIGHT] = DOWN; break;
      }
      break;
   
    case OFF:
      //button has been up or it is just up.
      switch( mEdge[Mouse::RIGHT] )
      {
      case EDGE_DOWN:
      case DOWN:  mEdge[Mouse::RIGHT] = EDGE_UP; break;
      case EDGE_UP:  mEdge[Mouse::RIGHT] = UP; break;
      }
      break;
   
    default: assert(false);
    }
    
    // do the position update...
    
    //get the offset the mouse has moved
    _xDelta = _xFuture - _xCurrent;
    _yDelta = _yFuture - _yCurrent;
    
    // save the new current position
    _xCurrent = _xFuture;
    _yCurrent = _yFuture;
}

#endif
