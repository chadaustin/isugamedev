#ifndef LR_BAD_GUY_H
#define LR_BAD_GUY_H

#include <math.h>


#include "Player.h"
#include "Block.h"


namespace lr
{
   // forward declarations
   class Level;
   class Texture;
   class Player;

   /**
    * I wish I woudl have created an abstract base person class to derive 
    * both player and badguy from but since I didn't think that far ahead
    * I'm stuck with duplicating a bunch of code :(  
    */
   class BadGuy 
   {
   public:
      /**
       * default constructor
       */
      BadGuy();

      /**
       * constructor
       * sets the position of the player to 0,1
       */
      BadGuy(Level& theLevel, Player& thePlayer);
      
      /**
       * copy constructor
       * automatically starts with texture 0 for running.
       * @params Pheight and Ppos should take a floats between 0 and 1024 and 0
       * and 768 respectively.
       */
      BadGuy(float Pheight, float Ppos, playerState Pstate)
      {
         realHeight = Pheight;
         realPos = Ppos;
         mState = Pstate;
         mTextureState = runright1;  // set the texture state to 0;
      }

      /**
       * destructor
       */
      virtual ~BadGuy();
      
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
       * Set the position of the badguy to a certain location
       * @params pos is the actual position NOT the grid position
       */
      void setPos(int pos);

      /** 
       * set the height of the badguy to a certain location
       * @params h is the actual height NOT the grid height
       */
      void setHeight(int h);
           
      /**
       * this is the keypress handler, it stores which keys were pressed since
       * the last update that we went through
       */
      void handleKeyPress(SDLKey sym, bool down);

      
      /**
       * here are all the methods for collision detection and figureing out what
       * state to put the player in
       */
      bool solidUnder();   // returns true if there is something that we can walk on under us
      bool onWire();       // returns true if there is a wire where we are at
      bool onLadder();     // returns true if we are on a ladder 
      bool brickRight();   // returns true if there are bricks directly to our right
      bool brickLeft();    // returns true if there are bricks directly to our left
      bool ladderUnder();  // returns true if there is a ladder under us
      bool brickUnder();   // returns true if there is bricks under us
      bool isMoney();      // returns true if we are touching a money bag.
      
   private:
      float realPos;    // players real position on the screen from 0 to 1024
      float realHeight; // players real height on the screen from 0 to 768
      
      playerState mState;			// players current state either hang1,2, climb1,2, or run1,2,
      
      Texture* run1leftImage, *run2leftImage, *run3leftImage, *run1rightImage, *run2rightImage, *run3rightImage, *climb1Image, *climb2Image, *hang1rightImage, *hang2rightImage, *hang3rightImage, *hang1leftImage, *hang2leftImage, *hang3leftImage;
      
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
                              //  0 = running
                              //  1 = running
                              //  2 = climbing
                              //  3 = climbing
                              //  4 = hanging
                              //  5 = hanging
      
      /** 
       * the badguy keeps a reference to the level so that he can test to see what
       * is in it
       */
      Level* mLevel;

      /** 
       * the badguy keeps a reference to the player so he knows where he is at all times
       */
      Player* mPlayer;

      
      /** variables for update that get set in handleKeyPress - blah */
      bool keyup, keydown, keyleft, keyright;

      /** float to help us with timing issues with textures */
      float initTime;

   /**************************************************************************
    * The last thing we need is the ai methods the following methods all realte
    * to the the ai system so that we have intelligent bad guys. :)
    * NOTE: there is only one place that I am aware of that has ai code in it
    * other than those things listed below and that is in the fall method to
    * reset the guys since they would lose track of where they are if we didn't
    * do this.
    */
   public:
      /*----------------------------------*\
       * This boolean is true if we are 
       * currently at a goal point and we 
       * need to look for a new goal to 
       * go to
       *----------------------------------*/
      bool atGoal;
      Block* goal;
      
      
      /*----------------------*\
       * command functions
      \*----------------------*/
      void moveRight()
      {
         keyright=true;
         keyleft=false;
         keyup=false;
         keydown=false;
      }
      void moveLeft()
      {
         keyright=false;
         keyleft=true;
         keyup=false;
         keydown=false;
      }
      void moveUp()
      {
         keyright=false;
         keyleft=false;
         keyup=true;
         keydown=false;
      }
      void moveDown()
      {
         keyright=false;
         keyleft=false;
         keyup=false;
         keydown=false;
      }
      void stop()
      {
         keyright=false;
         keyleft=false;
         keyup=false;
         keydown=false;
      }


      
      void chooseNextGoal();
                     
                  
            

      /*----------------*\
       * Test Functions 
      \*----------------*/
      bool isPlayerLeft()
      {
         if(mPlayer->getGridHeight()==getGridHeight() && mPlayer->getGridPos()<getGridPos()){ // the player is directly left of us
            atGoal = true;
            return true;
         }else{
            return false;
         }
      }
      bool isPlayerRight()
      {
         if(mPlayer->getGridHeight()==getGridHeight() && mPlayer->getGridPos()>getGridPos()){
            atGoal=true;
            return true;
         }else{
            return false;
         }
      }

      bool isPlayerAbove()
      {
         if(mPlayer->getGridHeight()>getGridHeight()){
            return true;
         }else{
            return false;
         }
      }
      bool isPlayerBelow()
      {
         return !isPlayerAbove();
      }

      bool isAtGoal()
      {
         return atGoal;
      }
      
      
      
   };

} // end namespace
#endif     

 
