#ifndef LR_GAME_STATE_H
#define LR_GAME_STATE_H

#include <SDL.h>

// loom includes for AI
#include <loom/aiSystem.h>
#include <loom/reflex.h>
#include <loom/behavior.h>
#include <loom/unit.h>
#include <loom/command.h>

#include "State.h"


namespace lr
{
   class Application;
   class Level;
   class Player;
   class Texture;
   class ScoreBoard;
   class BadGuy;

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


      int switchStates();
      
   private:
   
      lm::aiSystem AI;

      
      
      Level* mLevel;
      Player* mPlayer;
      ScoreBoard* mScoreBoard;
      BadGuy* mBadGuy;

      
      lm::aiNode* badGuy1;
      lm::aiNode* badGuy2;
      
      lm::command* moveLeftCommand; 
      lm::command* moveRightCommand;
      lm::command* moveUpCommand;
      lm::command* moveDownCommand;

      lm::behavior* moveLeftBehavior;
      lm::behavior* moveRightBehavior;
      lm::behavior* moveUpBehavior;
      lm::behavior* moveDownBehavior;
      
      lm::testing* playerIsLeftTest;
      lm::testing* playerIsRightTest;
      lm::testing* playerIsUpTest;
      lm::testing* playerIsDownTest;

      lm::reflex* mReflex1;
      lm::reflex* mReflex2;
      lm::reflex* mReflex3;
      lm::reflex* mReflex4;

      
      bool transition;
   };

} // end namespace

#endif
