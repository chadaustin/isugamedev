#ifndef PLASMA_TERRAIN_H
#define PLASMA_TERRAIN_H


#include "Terrain.h"


class PlasmaTerrain : public Terrain {
public:
   PlasmaTerrain(int power);
   ~PlasmaTerrain();

   int getWidth()  { return mSize; }
   int getHeight() { return mSize; }
   float* getHeightMap() { return mHeightMap; }

private:
   static int Rand1(int base, int delta);
   void initialize();

   int mSize;
   float* mHeightMap;

   int* mTerrain;
   int* mOldTerrain;
};


#endif
