#ifndef MY_TERRAIN_H
#define MY_TERRAIN_H


#include <algorithm>
#include "Terrain.h"


class MyTerrain : public Terrain {
public:
   MyTerrain(int power);
   ~MyTerrain();

   float* getHeightMap() { return mHeightMap; }
   int getWidth()        { return mSize;      }
   int getHeight()       { return mSize;      }

private:
   void setH(int x, int y, float h) {
      mHeightMap[y * mSize + x] = h;
      mMaxHeight = std::max(h, mMaxHeight);
      mMinHeight = std::min(h, mMinHeight);
   }

   void generate(int x1, int y1, int x2, int y2);
   void normalize();
   static float frand();

   int mSize;
   float* mHeightMap;
   float mMaxHeight;
   float mMinHeight;
};


#endif
