#ifndef GAMEINPUT
#define GAMEINPUT

#include "Mouse.h"
#include "Keyboard.h"
#include "Singleton.h"

class Input
{
public:
};
class DigitalInput : public Input
{
public:
   
};

class GameInput : public kev::Singleton<GameInput>
{
public:
   // Return a Input ptr to a deviced named
   //!RETURN: NULL - Not found
   Input* getDevice( std::string deviceName );

   //: Add a device to InputManager.
   //
   // Add the devPtr to the device Array, devPtr should
   // not already be in the array.  Returns -1 on failure
   //
   //! MODIFIES: self
   bool addDevice( Input* devPtr );
   
public:
   /* Poll for input state: */
   inline const Mouse&        mouse() const { return mMouse; }
   inline Mouse&              mouse() { return mMouse; }
   inline const Keyboard&     keyboard() const { return mKeyboard; }
   inline Keyboard&           keyboard() { return mKeyboard; }
   inline const char&         modifier() const { return mKeyboardModifier; }
   inline char&               modifier() { return mKeyboardModifier; }

private:
   Mouse            mMouse;
   Keyboard         mKeyboard;
   char             mKeyboardModifier;
};

#endif
