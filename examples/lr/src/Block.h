#ifndef LR_BLOCK_H
#define LR_BLOCK_H

namespace lr
{
   class Block
   {
   public:
      Block(int p, int h)
      {
         time = 0;
         pos = p;
         height = h;
      }
      ~Block(){}
      int pos;
      int height;
      float time; // the time past since the block was last done anything with
   };
} // end namespace

#endif
