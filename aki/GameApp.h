#ifndef BASE_GAME_APP_INCLUDED
#define BASE_GAME_APP_INCLUDED

#include <string>
#include <vector>
#include <Mouse.h>
#include <Keyboard.h>

/* Base game application class.  for use with the "GameKernel" 
 * don't modify this class... instead derive a class "MyApp" from this, 
 *  and overload the virtual members.  
 *  Derivation goes like this:
 *
 *      class MyApp : public GameApp
 */
class GameApp
{
public:
   GameApp() {}
   virtual ~GameApp() {}

   /*  draw function, called each frame once per window */
   virtual void OnContextDraw( int context = 0 ) {}

   /*  called before draw */
   virtual void OnPreFrame() {}

   /*  called during draw (on some platforms..) */
   virtual void OnIntraFrame() {}

   /*  called after draw */
   virtual void OnPostFrame() {}

// Init methods
public:
   /* called before any windows are opened */
   virtual void OnAppInit() {}

   /* called once for each window */
   virtual void OnContextInit() {};
   
   /* called on each window exit */
   virtual void OnContextExit() {};
};


#endif
