#ifndef LR_SCORE_BOARD_H
#define LR_SCORE_BOARD_H

#include <gltext.h>
#include <iostream>

namespace lr
{
   class ScoreBoard
   {
   public:
      /** 
       * creates the font and renderer and sets the font of the renderer.
       */
      ScoreBoard()
      {
         font = gltext::CreateFont("arial.ttf", gltext::PLAIN, 26);
         if(! font)
         {
            std::cerr<<"Couldn't create font!"<<std::endl;
         }

         renderer = gltext::CreateRenderer(gltext::PIXMAP);
         if (! renderer)
         {
            std::cerr<<"Couldn't create font renderer!"<<std::endl;
         }
         renderer->setFont(font.get());

         numLives = 0;
         playerScore = 0;
         msg =  "";
         FPS= 0;
      }

      ~ScoreBoard()
      {
      }

      /** 
       * update the scoreboard with the current score and the number of lives
       */
      void update(int score, int lives, float fps)
      {
         numLives = lives;
         playerScore = score;
         FPS = fps;
      }

      /**
       * draw the scoreboard to the screen
       */
      void draw()
      {
//         renderer->getStream() << "Score: " << playerScore << "              lives: " << numLives << "     fps: "  << FPS << gltext::flush;
         renderer->getStream() << "Score: " << playerScore << "              lives: " << numLives << gltext::flush;
      }
   public:
      int numLives, playerScore;
      float FPS;
      std::string msg;
      
      gltext::FontPtr font;
      gltext::FontRendererPtr renderer;

   };
} // end namespace

#endif
      
