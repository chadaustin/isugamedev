#include <algorithm>
#include <memory>
#include <corona.h>
#include "ImageTerrain.h"


ImageTerrain::ImageTerrain(const char* filename) {
   std::auto_ptr<corona::Image> img(corona::OpenImage(filename,
                                                      corona::FF_AUTODETECT,
                                                      corona::PF_R8G8B8));
   if (!img.get()) {
      mWidth  = 2;
      mHeight = 2;
      mHeightMap = new float[mWidth * mHeight];
      std::fill(mHeightMap, mHeightMap + mWidth * mHeight, 0.5f);
   } else {
      mWidth  = img->getWidth();
      mHeight = img->getHeight();
      mHeightMap = new float[mWidth * mHeight];

      unsigned char* byte = (unsigned char*)img->getPixels();
      float* h = mHeightMap;
      for (int y = 0; y < mHeight; ++y) {
         for (int x = 0; x < mWidth; ++x) {
            *h++ = float(byte[0] + byte[1] + byte[2]) / (255 * 3);
            byte += 3;
         }
      }
   }
   
}


ImageTerrain::~ImageTerrain() {
   delete[] mHeightMap;
}
