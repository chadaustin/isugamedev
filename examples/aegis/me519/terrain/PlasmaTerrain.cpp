#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "PlasmaTerrain.h"


PlasmaTerrain::PlasmaTerrain(int power) {
   srand(time(0));

   mSize = (1 << power);
   mHeightMap = new float[mSize * mSize];

   mTerrain = new int[mSize * mSize];
   mOldTerrain = new int[mSize * mSize];
   initialize();
   delete[] mTerrain;
}


PlasmaTerrain::~PlasmaTerrain() {
   delete mHeightMap;
}


int
PlasmaTerrain::Rand1(int base, int delta) {
   return base + (rand() % delta) - delta / 2;
}


void
PlasmaTerrain::initialize() {
   int row_offset = 0;
   for (int i = 0; i < mSize * mSize; ++i) {
      mTerrain[i] = 0;
   }

   for (int square_size = mSize; square_size > 1; square_size /= 2) {
      int random_range = square_size;
      for (int x1 = row_offset; x1 < mSize; x1 += square_size) {
         for (int y1 = row_offset; y1 < mSize; y1 += square_size) {

            // Get the four corner points.
            int x2 = (x1 + square_size) % mSize;
            int y2 = (y1 + square_size) % mSize;

            int i1 = mTerrain[x1 * mSize + y1];
            int i2 = mTerrain[x2 * mSize + y1];
            int i3 = mTerrain[x1 * mSize + y2];
            int i4 = mTerrain[x2 * mSize + y2];

            // Obtain new points by averaging the corner points.
            int p1 = ((i1 * 9) + (i2 * 3) + (i3 * 3) + (i4)) / 16;
            int p2 = ((i1 * 3) + (i2 * 9) + (i3) + (i4 * 3)) / 16;
            int p3 = ((i1 * 3) + (i2) + (i3 * 9) + (i4 * 3)) / 16;
            int p4 = ((i1) + (i2 * 3) + (i3 * 3) + (i4 * 9)) / 16;

            // Add a random offset to each new point.
            p1 = Rand1(p1, random_range);
            p2 = Rand1(p2, random_range);
            p3 = Rand1(p3, random_range);
            p4 = Rand1(p4, random_range);
    
            // Write out the generated points.
            int x3 = (x1 + square_size/4) % mSize;
            int y3 = (y1 + square_size/4) % mSize;
            x2 = (x3 + square_size/2) % mSize;
            y2 = (y3 + square_size/2) % mSize;
    
            mTerrain[x3 * mSize + y3] = p1;
            mTerrain[x2 * mSize + y3] = p2;
            mTerrain[x3 * mSize + y2] = p3;
            mTerrain[x2 * mSize + y2] = p4;
         }
      }
      row_offset = square_size / 4;
   }

   // make the terrain tileable
   for (int i = 0; i < mSize * mSize; ++i) {
      mOldTerrain[i] = mTerrain[i];
   }
   for (int i = 0; i < mSize; ++i) {
      for (int j = 0; j < mSize; ++j) {
         int ni = (i + mSize / 2) % mSize;
         int nj = (j + mSize / 2) % mSize;
         mTerrain[i * mSize + j] = (mOldTerrain[i * mSize + j] +
                                    mOldTerrain[ni * mSize + nj]) / 2;
      }
  
 }

   // normalize terrain and convert it to floats
   int max_v = INT_MIN;
   int min_v = INT_MAX;

   for (int i = 0; i < mSize * mSize; ++i) {
      max_v = std::max(max_v, mTerrain[i]);
      min_v = std::min(min_v, mTerrain[i]);
   }
   float* f = mHeightMap;
   for (int i = 0; i < mSize * mSize; ++i) {
      *f++ = float(mTerrain[i] - min_v) / (max_v - min_v);
   }
}
