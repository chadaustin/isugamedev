#ifndef IMAGE_TERRAIN_H
#define IMAGE_TERRAIN_H


#include "Terrain.h"


class ImageTerrain : public Terrain {
public:
   ImageTerrain(const char* filename);
   ~ImageTerrain();

   float* getHeightMap() { return mHeightMap; }
   int getWidth()        { return mWidth; }
   int getHeight()       { return mHeight; }

private:
   int mWidth;
   int mHeight;
   float* mHeightMap;
};


#endif
