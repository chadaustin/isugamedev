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
      }

      ~ScoreBoard()
      {
      }

      void draw()
      {
         renderer->getStream() << "lives: " << gltext::flush;
      }
   public:
      gltext::FontPtr font;
      gltext::FontRendererPtr renderer;

   };
} // end namespace

#endif
      
