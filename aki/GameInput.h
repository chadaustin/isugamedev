#ifndef GAMEINPUT
#define GAMEINPUT

#include <string>
#include <utility> // for pair

#include "Mouse.h"
#include "Keyboard.h"
#include "Singleton.h"

#include "DigitalInput.h"
#include "AnalogInput.h"
#include "EventInput.h"

/* input manager for game input
 * try to use the Interface classes instead of this class directly
 * (i.e. use DigitalInterface or AnalogInterface)
 */
class GameInput : public kev::Singleton<GameInput>
{
public:
   GameInput()
   {
      mDevices["Keyboard"] = mKeyboard = new Keyboard;
      mDevices["Mouse"] = mMouse = new Mouse;
   }

   /* return an Input ptr
    * give the alias to the input 
    * i.e. ACCELERATE_ACTION
    * !RETURN: NULL - Not found
    */
   Input* getInput( const std::string& alias )
   {
      if (mBindTable.count( alias ) == 0)
         return NULL;
      
      EventInput& event_input = mBindTable[alias];
      return &event_input;
   }

   /* Return an Input ptr
    * give the real Device name (i.e. Keyboard) and 
    * give the real input name within that Device (i.e. KEY_UPARROW)
    * !RETURN: NULL - Not found
    */
   Input* getInput( const std::string& device, const std::string& input )
   {
      if (mDevices.count( device ) == 0)
         return NULL;
      
      Device* dev = mDevices[device];
      return dev->getInput( input );
   }   

   /* Add a device to InputManager.
    *
    * Add the devPtr to the device Array, devPtr should
    * not already be in the array.  Returns -1 on failure
    *
    * MODIFIES: self
    */
   bool addInput( Input* devPtr );
   
   void bind( const std::string& alias, const std::string& device, const std::string& input )
   {
      Input* in_put = GameInput::instance().getInput( device, input );
      mBindTable[alias].bind( in_put );
   }   
   
public:
   /* get the device directly */
   inline const Mouse&        mouse() const { return *mMouse; }
   
   /* get the device directly */
   inline Mouse&              mouse() { return *mMouse; }
   
   /* get the device directly */
   inline const Keyboard&     keyboard() const { return *mKeyboard; }
   
   /* get the device directly */
   inline Keyboard&           keyboard() { return *mKeyboard; }
   
   /* uh... how to deal with this? */
   inline char         modifier() const { return mKeyboardModifier; }

private:
   std::map<std::string, EventInput> mBindTable;
   std::map<std::string, Device*> mDevices;
   Mouse*            mMouse;
   Keyboard*         mKeyboard;
   char              mKeyboardModifier;
};

#endif
