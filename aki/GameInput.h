#ifndef GAMEINPUT
#define GAMEINPUT

#include <string>
#include <utility> // for pair

#include "Mouse.h"
#include "Keyboard.h"
#include "Singleton.h"

#include "DigitalInput.h"
#include "AnalogInput.h"


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
      
      std::pair<std::string, std::string>& p = mBindTable[alias];
      return this->getInput( p.first, p.second );
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
      mBindTable[alias] = std::pair<std::string, std::string>( device, input );
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
   inline const char&         modifier() const { return mKeyboardModifier; }
   inline char&               modifier() { return mKeyboardModifier; }

private:
   std::map<std::string, std::pair<std::string, std::string> > mBindTable;
   std::map<std::string, Device*> mDevices;
   Mouse*            mMouse;
   Keyboard*         mKeyboard;
   char              mKeyboardModifier;
};

#endif
