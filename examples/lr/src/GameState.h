#ifndef LR_GAME_STATE_H
#define LR_GAME_STATE_H

#include <SDL.h>

#include "State.h"

namespace lr
{
   class Application;
   class Level;
   class Player;
   class Texture;
   class ScoreBoard;

   class GameState : public State
   {
   public:

      /**
       * constrcutor
       */
      GameState(Application *app);

      /**
       * destructor
       */
      ~GameState();
      
      /**
       * overload the update method
       */
      void update(float dt);

      /** libs
       * overload the draw method from State
       */
      void draw();

      /**
       * overload the keypress from State
       */
      void onKeyPress(SDLKey sym, bool down);


      bool switchStates();
      
   private:
      Level* mLevel;
      Player* mPlayer;
      ScoreBoard* mScoreBoard;
   };

} // end namespace

#endif
