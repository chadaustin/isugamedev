#ifndef TERRAIN_H
#define TERRAIN_H


class Terrain {
public:
   virtual ~Terrain() { }

   virtual float* getHeightMap() = 0;
   virtual int getWidth() = 0;
   virtual int getHeight() = 0;

   float getHeightAt(int x, int y) {
      return getHeightMap()[y * getWidth() + x];
   }
};


#endif
