#ifndef TERRAIN_APPLICATION_H
#define TERRAIN_APPLICATION_H


#include <string>
#include "AmbientWind.h"
#include "Application.h"
#include "FlyCamera.h"
#include "RotationCamera.h"
#include "SnowSystem.h"
#include "Terrain.h"
#include "Texture.h"


class TerrainApplication : public Application {
public:
  TerrainApplication(Terrain* terrain);
  ~TerrainApplication();

  void draw();
  void resize(int width, int height);
  void update(int elapsedTime);

  void onKeyDown(unsigned char key);
  void onKeyUp(unsigned char key);
  void onSpecialDown(int key);
  void onSpecialUp(int key);

private:
  Camera* getCamera();

  static const int CAMERA_COUNT = 3;

  void initializeGL();
  void enableFog(bool enabled);
  void drawTerrain();
  void drawTerrainPass(
    Texture* texture,
    float colorAdd, float colorMul,
    float alphaAdd, float alphaMul);
  void drawHUD();
  void drawHelp();

  static void drawString(int x, int y, const std::string& str);
  static void drawString(int x, int y, const char* str);

  int      mWidth;
  int      mHeight;
  Terrain* mTerrain;

  Texture* mGroundTexture;
  Texture* mGrassTexture;
  Texture* mSnowTexture;

  int mCurrentCamera;
  Camera* mCameras[CAMERA_COUNT];

  int mDetailReduction;  // 1 = default

  bool mFogEnabled;
  bool mHelpShown;

  SnowSystem mSnow;
  AmbientWind mAmbientWind;
};


#endif
