#include <stdlib.h>
#include <time.h>
// stupid gcc 2.9x  :(
// #include <limits>
#include "MyTerrain.h"


MyTerrain::MyTerrain(int power) {
   srand(time(0));

   // generate a size from the power
   mSize = 1;
   for (int i = 0; i < power; ++i) {
      mSize = mSize * 2 + 1;
   }

   mHeightMap = new float[getWidth() * getHeight()];

   mMaxHeight = -10000;
   mMinHeight = 10000;

   // stupid gcc 2.9x  :(
   // mMaxHeight = std::numeric_limits<float>::min();
   // mMinHeight = std::numeric_limits<float>::max();

   // generate terrain using plasma subdivision
   int w = getWidth()  - 1;
   int h = getHeight() - 1;
   setH(0, 0, frand());
   setH(0, h, frand());
   setH(w, 0, frand());
   setH(w, h, frand());
   generate(0, 0, w, h);

   normalize();
}


MyTerrain::~MyTerrain() {
   delete[] mHeightMap;
}

void
MyTerrain::generate(int x1, int y1, int x2, int y2) {

   // get size of the rectangle we're working with
   int size = x2 - x1;  // this should be the same as y2 - y1

   if (size <= 1) {
      return;
   }

   // find midpoints
   int midx = (x1 + x2) / 2;
   int midy = (y1 + y2) / 2;

   // set center of rectangle
   float v_ul = getHeightAt(x1, y1);
   float v_ur = getHeightAt(x2, y1);
   float v_lr = getHeightAt(x2, y2);
   float v_ll = getHeightAt(x1, y2);
   float avg = (v_ul + v_ur + v_lr + v_ll) / 4;
   setH(midx, midy, avg + frand() * size / 2);

   // set edge midpoints
   setH(x1, midy, (v_ul + v_ll) / 2 + frand() * size / 4);
   setH(midx, y1, (v_ul + v_ur) / 2 + frand() * size / 4);
   setH(x2, midy, (v_ur + v_lr) / 2 + frand() * size / 4);
   setH(midx, y2, (v_ll + v_lr) / 2 + frand() * size / 4);

   // generate quadrants
   generate(x1,   y1,   midx, midy);
   generate(midx, y1,   x2,   midy);
   generate(x1,   midy, midx, y2);
   generate(midx, midy, x2,   y2);
}


void
MyTerrain::normalize() {
   float* p = mHeightMap;
   int c = mSize * mSize;
   while (c--) {
      *p = (*p - mMinHeight) / (mMaxHeight - mMinHeight);
      ++p;
   }
}


float
MyTerrain::frand() {
   // return a random value between -1 and 1
   return (rand() / float(RAND_MAX)) * 2 - 1;
}
