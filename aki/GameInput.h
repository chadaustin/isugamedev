#ifndef GAMEINPUT
#define GAMEINPUT

#include "Mouse.h"
#include "Keyboard.h"
#include "Singleton.h"

class GameInput : public kev::Singleton<GameInput>
{
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
