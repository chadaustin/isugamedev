#ifndef LR_PLAYER_H
#define LR_PLAYER_H


#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Types.h"

namespace lr
{
   // forward declarations
   class Level;
   class Texture;

   class Player{
   public:
      /**
       * default constructor
       */
      Player();

      /**
       * constructor
       * sets the position of the player to 0,1
       */
      Player(Level& theLevel);
      
      /**
       * copy constructor
       * automatically starts with texture 0 for running.
       * @params Pheight and Ppos should take a floats between 0 and 1024 and 0
       * and 768.
       */
      Player(float Pheight, float Ppos, playerState Pstate)
      {
         realHeight = Pheight;
         realPos = Ppos;
         mState = Pstate;
         mTextureState = runright1;  // set the texture state to 0;
      }

      /**
       * destructor
       */
      ~Player();
      
      /**
       * update checks to see if we should move the player, if we should move then
       * the player pos and height is updated and we update the playerState as
       * needed.
       */
      void update(float dt);

      
      /**
       * the draw function draws the player in the correct location in the right
       * direction with the right texture based on his current state
       */
      void draw();
      
      /** 
       * helper functions to figure out what square on the grid we are currently
       * in. They simply divide the position and height by 32 to get the grid
       * location.
       */
      int getGridPos(){ return (int)realPos/32; }
      int getGridHeight(){ return (int)realHeight/32; }

      /**
       * Set the position of the player to a certain location
       * @params pos is the actual position NOT the grid position
       */
      void setPos(int pos);

      /** 
       * set the height of the player to a certain location
       * @params h is the actual height NOT the grid height
       */
      void setHeight(int h);

      void setInitPos(int pos);
      void setInitHeight(int h);
           
      
      /**
       * this is the keypress handler, it stores which keys were pressed since
       * the last update that we went through
       */
      virtual void handleKeyPress(SDLKey sym, bool down);

      
      /**
       * here are all the methods for collision detection and figureing out what
       * state to put the player in
       */
      bool solidUnder();   // returns true if there is something that we can walk on under us
      bool onWire();       // returns true if there is a wire where we are at
      bool onLadder();     // returns true if we are on a ladder 
      bool brickRight();   // returns true if there are bricks directly to our right
      bool brickLeft();    // returns true if there are bricks directly to our left
      bool brickAbove();   // returns true if there are bricks directly above
      bool ladderUnder();  // returns true if there is a ladder under us
      bool brickUnder();   // returns true if there is bricks under us
      bool isMoney();      // returns true if we are touching a money bag.
      
      /** 
       * method to return the integer number of lives this player currently has
       */
      int getLives();

      /**
       * mehtod to return the score the player has accumulated
       */
      int getScore();

      /**
       * setLives sets the number lives this player has to the given number
       */
      void setLives(int lives){ numLives = lives; }

      /**
       * setScore sets the score of for the player to s
       */
      void setScore(int s){ score = s; }

      void burnOutRightBrick(float dt);

      void burnOutLeftBrick(float dt);

      void caught()
      {
         die=true;
      }

      bool amDead()
      {
         return die;
      }
      
   private:
      float realPos;    // players real position on the screen from 0 to 1024
      float realHeight; // players real height on the screen from 0 to 768
      float initPos;
      float initHeight;
      
      playerState mState;			// players current state either hang1,2, climb1,2, or run1,2,
      Texture* run1leftImage, *run2leftImage, *run3leftImage, *run1rightImage, *run2rightImage, *run3rightImage, *climb1Image, *climb2Image, *hang1rightImage, *hang2rightImage, *hang3rightImage, *hang1leftImage, *hang2leftImage, *hang3leftImage, *dieTexture;
      
      /** 
       * now we create a currentTexture pointer that just points at the one we
       * need to draw 
       */
      Texture* currentTexture;
      
            
      /**
       * fall just drops the player a certain amount everyframe (divisible by 2)
       */
      void fall(float dt);

      // an enumeration to determin what textures we should be drawing
      textureState mTextureState;		
                              //: state to flip textures around
                              //  0 = runleft1
                              //  1 = runleft2
                              //  2 = runleft3
                              //  3 = runright1
                              //  4 = runright2
                              //  5 = runright3
                              //  6 = climb1
                              //  7 = climb2
                              //  8 = hang1
                              //  9 = hang2
      
      /** 
       * the player keeps a reference to the level so that he can test to see what
       * is in it
       */
      Level* mLevel;

      bool die;
      float dieTime;
      
      /** players score */
      int score;

      /** number of lives this player has left */
      int numLives;

      /** variables for update that get set in handleKeyPress - blah */
      bool keyup, keydown, keyleft, keyright, burnright, burnleft;

      /** float to help us with timing issues with textures */
      float initTime;
   };

} // end namespace
#endif
