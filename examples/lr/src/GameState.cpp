#include <iostream>
#include <string>

#include <SDL_opengl.h>

#include "Application.h"
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
      mLevel->readLevelFile(std::string("level1.lvl"));

      // now that we have the level we create the player and give him the level
      // to work with
      mPlayer = new Player(*mLevel);

      mScoreBoard = new ScoreBoard();
   }

   GameState::~GameState()
   {
      delete mLevel;
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

      // set up projection matrix
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
      mLevel->draw();
      mPlayer->draw();

      // now draw the scoreboard
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
      
      
   }

   void GameState::update(float dt)
   {
      mPlayer->update(dt);
      mScoreBoard->update(mPlayer->getLives(), mPlayer->getScore());
   }

   bool GameState::switchStates()
   {
   }

   void GameState::onKeyPress(SDLKey sym, bool down)
   {
      mPlayer->handleKeyPress(sym, down);
   }


} // end namespace
