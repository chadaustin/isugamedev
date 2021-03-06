#include <iostream>
#include <string>

#include <SDL_opengl.h>



#include "Application.h"
#include "BadGuy.h"
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include "ScoreBoard.h"
#include "Texture.h"

namespace lr
{
   GameState::GameState(Application* app) : State(app)
   {
      mLevel = new Level();

// add the names of all the levels in order
      std::vector<std::string> levels;
      std::string l1("level1.lvl");
      std::string l2("level2.lvl");
      levels.push_back(l1);
      levels.push_back(l2);
      
      // register the levels with the level object
      mLevel->loadLevelFiles(levels);

      // now that we have the level we create the player and give him the level
      // to work with
      mPlayer = new Player(*mLevel);
      
      // now read the first level
      mLevel->readLevelFile(mPlayer, mBadGuys);
      
      

      
      
      // create a scoreboard
      mScoreBoard = new ScoreBoard();

      
      // initialize transitions to false
      transition = false;

      setupBadGuys();
      
      
      
      

   }

   GameState::~GameState()
   {
      delete mLevel;

   }

   void GameState::setupBadGuys()
   {
      for(int i=0;i<mBadGuys.size();i++)
      {
         badGuy1 = new lm::aiNode(NULL,0,0);
         
         lm::command* moveLeftCommand; 
         lm::command* moveRightCommand;
         lm::command* moveUpCommand;
         lm::command* moveDownCommand;
         lm::command* chooseNewGoalCommand;
         lm::command* moveToGoalCommand;

         lm::behavior* moveLeftBehavior;
         lm::behavior* moveRightBehavior;
         lm::behavior* moveUpBehavior;
         lm::behavior* moveDownBehavior;
         lm::behavior* chooseNewGoalBehavior;
         lm::behavior* goTowardGoalBehavior;
         
         lm::testing* playerIsLeftTest;
         lm::testing* playerIsRightTest;
         lm::testing* playerIsUpTest;
         lm::testing* playerIsDownTest;
         lm::testing* atGoalTest;
         lm::testing* notAtGoalTest;

         lm::reflex* mReflex1;
         lm::reflex* mReflex2;
         lm::reflex* mReflex3;
         lm::reflex* mReflex4;


         moveLeftCommand = new lm::simpleCommand<BadGuy>(mBadGuys[i], &BadGuy::moveLeft); 
         moveRightCommand = new lm::simpleCommand<BadGuy>(mBadGuys[i], &BadGuy::moveRight);
         moveUpCommand = new lm::simpleCommand<BadGuy>(mBadGuys[i], &BadGuy::moveUp);
         moveDownCommand = new lm::simpleCommand<BadGuy>(mBadGuys[i], &BadGuy::moveDown);

         chooseNewGoalCommand = new lm::simpleCommand<BadGuy>(mBadGuys[i], &BadGuy::chooseNextGoal);
         moveToGoalCommand = new lm::simpleCommand<BadGuy>(mBadGuys[i], &BadGuy::moveToGoal);

         moveLeftBehavior = new lm::behavior;
         moveRightBehavior = new lm::behavior;
         moveUpBehavior = new lm::behavior;
         moveDownBehavior = new lm::behavior;
         
         chooseNewGoalBehavior = new lm::behavior;
         goTowardGoalBehavior = new lm::behavior;

         moveLeftBehavior->addCommand(moveLeftCommand);
         moveRightBehavior->addCommand(moveRightCommand);
         moveUpBehavior->addCommand(moveUpCommand);
         moveDownBehavior->addCommand(moveDownCommand);
         
         chooseNewGoalBehavior->addCommand(chooseNewGoalCommand);
         goTowardGoalBehavior->addCommand(moveToGoalCommand);
         
         playerIsLeftTest = new lm::nodeTestCommand<BadGuy>(mBadGuys[i], &BadGuy::isPlayerLeft);
         playerIsRightTest = new lm::nodeTestCommand<BadGuy>(mBadGuys[i], &BadGuy::isPlayerRight);
         playerIsUpTest = new lm::nodeTestCommand<BadGuy>(mBadGuys[i], &BadGuy::isPlayerAbove);
         playerIsDownTest = new lm::nodeTestCommand<BadGuy>(mBadGuys[i], &BadGuy::isPlayerBelow);

         atGoalTest = new lm::nodeTestCommand<BadGuy>(mBadGuys[i], &BadGuy::isAtGoal);
         notAtGoalTest = new lm::nodeTestCommand<BadGuy>(mBadGuys[i], &BadGuy::notAtGoal);

         // these two reflexes are for if the player is directly left or right of us
         mReflex1 = new lm::reflex(badGuy1, moveLeftBehavior, playerIsLeftTest);
         mReflex2 = new lm::reflex(badGuy1, moveRightBehavior, playerIsRightTest);
 
         mReflex4 = new lm::reflex(badGuy1, goTowardGoalBehavior, notAtGoalTest);
         mReflex3 = new lm::reflex(badGuy1, chooseNewGoalBehavior, atGoalTest);

         AI.registerNode(badGuy1);
      }
   }

   void GameState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_CULL_FACE);
      
      glClearColor(1.0f,1.0f,1.0f,1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // first draw the scoreboard in it's own viewport
      glViewport(0,0,this->getApp().getWidth(),32);
   
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      
      glOrtho(0, this->getApp().getWidth(), 0, 32, -1, 1);
      
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      
      glColor4f(0,0,0,1);
      glBegin(GL_LINE_LOOP);
         glVertex2f(1.0f, 1.0f);
         glVertex2f(1023.0f, 1.0f);
         glVertex2f(1023.0f, 30.0f);
         glVertex2f(1.0f, 30.0f);
      glEnd();
      
      glColor4f(1,0,0,1);
      glTranslatef(3,3,0);
      mScoreBoard->draw();



      // now setup and draw the game in it's own viewport
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      // TODO: this is currently flipped upside down but when I display stuff it
      // displays correctly, so I need to figure out why this is doing what it's
      // doing.
      glOrtho(0, this->getApp().getWidth(), 0, this->getApp().getHeight(), -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      // draw the level
      glColor4f(1, 1, 1, 1);


      // create the game viewport where the game is displayed then draw all the
      // contents of the game there
      glViewport(0,32,this->getApp().getWidth(),this->getApp().getHeight()-32);
      if(mPlayer->getLives()!=0)
      {
         mLevel->draw();
      }
         mPlayer->draw();
         for(int i=0;i<mBadGuys.size();i++)
            mBadGuys[i]->draw();
      transition = false;
   }

   void GameState::update(float dt)
   {
      if(mPlayer->getLives()==0)
      {
         mLevel->resetToFirstLevel();
         mLevel->readLevelFile(mPlayer, mBadGuys);
      }
      
      FPS = 1.0/dt; // store the frames per second
      
      
      bool first=true;
      bool done=false;
      if(mLevel->getNumBags()==0)  // if there is no money left then the player 
                                 // got all the money and we go to the next
                                 // level.
      {
  
         for(int i=0;i<mLevel->getLevels().size() && !done;i++)
         {
         
            if(mLevel->getCurrentLevel()==mLevel->getLevels()[i])
            {
               if((i+1)==mLevel->getLevels().size())
               {
                  mLevel->setCurrentLevel(mLevel->getLevels()[0]);
               }
               else
               { 
                  mLevel->setCurrentLevel(mLevel->getLevels()[i+1]);
               }
               done = true;
               mLevel->readLevelFile(mPlayer, mBadGuys);
               setupBadGuys();
            }
            mLevel->nextLevel==true;
         }
      }
      
      mLevel->update(dt);
      mScoreBoard->update(mPlayer->getScore(), mPlayer->getLives(), FPS);
      
      for(int i=0;i<mBadGuys.size();i++)
         mBadGuys[i]->update(dt);
      mPlayer->update(dt);
      AI.update();
   }

   int GameState::switchStates()
   {
      if(transition){
         mLevel->readLevelFile(mPlayer, mBadGuys);
         mPlayer->setScore(0);
         mPlayer->setLives(3);
         return 1;
      }
      if(mPlayer->getGameOver())
      {
         mPlayer->setScore(0);
         mPlayer->setLives(3);
         mPlayer->reset();
         for(int i=0;i<mBadGuys.size();i++)
         {
            mBadGuys[i]->reset();
         }

         return 1;
      }
	   return 0;
   }

   void GameState::onKeyPress(SDLKey sym, bool down)
   {
      if(sym == SDLK_ESCAPE && down)
      {
         transition = true;
      }
      mPlayer->handleKeyPress(sym, down);
      for(int i=0;i<mBadGuys.size();i++)
         mBadGuys[i]->handleKeyPress(sym, down);
   }


} // end namespace
