#include <GL/glut.h>
#include <algorithm>
#include <stdio.h>
#include "HoverCamera.h"
#include "RotationCamera.h"
#include "TerrainApplication.h"


static const float FOG_COLOR[4] = { 0.2f, 0.2f, 0.2f, 1 };


TerrainApplication::TerrainApplication(Terrain* terrain) {
  mWidth = 0;
  mHeight = 0;

  mCurrentCamera = 0;
  mCameras[0] = new RotationCamera();
  mCameras[1] = new FlyCamera();
  mCameras[2] = new HoverCamera(terrain);

  mTerrain = terrain;

  mGroundTexture = new Texture("ground.png");
  mGrassTexture  = new Texture("grass.png");
  mSnowTexture   = new Texture("snow.png");

  mDetailReduction = 1;

  mFogEnabled = true;
  mHelpShown  = false;

  initializeGL();
}


TerrainApplication::~TerrainApplication() {
  delete mCameras[0];
  delete mCameras[1];
  delete mCameras[2];

  delete mTerrain;
}


void
TerrainApplication::draw() {
  // set up projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect_ratio = (mHeight == 0 ? 1 : float(mWidth) / mHeight);
  gluPerspective(45, aspect_ratio, 0.001f, 100);

  // set up view matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(90, -1, 0, 0);  // z should be up (towards the sky)
  glScalef(1, -1, 1);       // the cameras assume "x is right" and "z is down"
  getCamera()->apply();

  // draw the world
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawTerrain();
  mSnow.draw();
  drawHUD();
}


void
TerrainApplication::resize(int width, int height) {
  mWidth  = width;
  mHeight = height;
}


void
TerrainApplication::onKeyDown(unsigned char key) {
  switch (key) {
    case 'c':
      mCurrentCamera = (mCurrentCamera + 1) % CAMERA_COUNT;
      return;

    case 'f':
      enableFog(!mFogEnabled);
      return;

    case 'h':
      mHelpShown = !mHelpShown;
      return;

    case 'q':
    case 27:
      exit(0);

    case '+':
      ++mDetailReduction;
      return;

    case '-':
      mDetailReduction = std::max(mDetailReduction - 1, 1);
      return;

    default:
      getCamera()->onKeyDown(key);
      return;
  }
}


void
TerrainApplication::onKeyUp(unsigned char key) {
  getCamera()->onKeyUp(key);
}


void
TerrainApplication::onSpecialDown(int key) {
  getCamera()->onSpecialDown(key);
}


void
TerrainApplication::onSpecialUp(int key) {
  getCamera()->onSpecialUp(key);
}


void
TerrainApplication::update(int elapsedTime) {
  getCamera()->update(elapsedTime);
  mSnow.update(elapsedTime);
  mAmbientWind.update(elapsedTime);
}


Camera*
TerrainApplication::getCamera() {
  return mCameras[mCurrentCamera];
}


void
TerrainApplication::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POLYGON_OFFSET_FILL);
  enableFog(mFogEnabled);

  glEnable(GL_POINT_SMOOTH);
  glPointSize(4);
}


void
TerrainApplication::enableFog(bool enabled) {
  mFogEnabled = enabled;

  if (enabled) {
    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.5f);
    glFogf(GL_FOG_START, 5);
    glFogf(GL_FOG_END, 15);
    glFogfv(GL_FOG_COLOR, FOG_COLOR);
    glClearColor(FOG_COLOR[0], FOG_COLOR[1], FOG_COLOR[2], FOG_COLOR[3]);
  } else {
    glDisable(GL_FOG);
  }
}


void
TerrainApplication::drawTerrain() {
  glPolygonOffset(0, 0);
  drawTerrainPass(mGrassTexture, 0, 1, 1, 1);

  glPolygonOffset(0, -1);
  const float g_range = 2;  // don't know what to call this...
  drawTerrainPass(mGroundTexture,
                  1 / g_range, g_range - 1,
                  -1 / g_range, -g_range);

  glPolygonOffset(0, -2);
  const float s_range = 3;
  drawTerrainPass(mSnowTexture, 0, 1, 1 / s_range - 1, s_range);

  // reset it for everybody else
  glPolygonOffset(0, 0);
}


class VertexGenerator {
public:
  VertexGenerator(float colorAdd, float colorMul,
                  float alphaAdd, float alphaMul)
  {
    mColorAdd = colorAdd;
    mColorMul = colorMul;
    mAlphaAdd = alphaAdd;
    mAlphaMul = alphaMul;
  }

  void vertex(float x, float y, float z) {
    float color = mColorMul * (z + mColorAdd);
    float alpha = mAlphaMul * (z + mAlphaAdd);
    glColor4f(color, color, color, alpha);
    glVertex3f(x, y, z);
  }

private:
  float mColorAdd;
  float mColorMul;
  float mAlphaAdd;
  float mAlphaMul;
};

void
TerrainApplication::drawTerrainPass(
  Texture* texture,
  float colorAdd,
  float colorMul,
  float alphaAdd,
  float alphaMul)
{
  VertexGenerator vg(colorAdd, colorMul, alphaAdd, alphaMul);

  glPushMatrix();

  const int dr = mDetailReduction;  // shorthand

  int width = mTerrain->getWidth();
  int height = mTerrain->getHeight();
  glTranslatef(-0.5f, -0.5f, 0);
  glScalef(1.0f / (width - dr), 1.0f / (height - dr), 1);

  float* heightMap = mTerrain->getHeightMap();

  texture->bind();

  const int REPETITION_COUNT_X = 8;
  const int REPETITION_COUNT_Y = 8;

  for (int j = 0; j < height - dr; j += dr) {
    const int j1 = j + dr;

    float* h1 = heightMap + j  * width;
    float* h2 = heightMap + j1 * width;

    for (int i = 0; i < width - dr; i += dr) {
      const int i1 = i + dr;

      const float u1 = REPETITION_COUNT_X * float(i)  / (width  - dr);
      const float v1 = REPETITION_COUNT_Y * float(j)  / (height - dr);
      const float u2 = REPETITION_COUNT_X * float(i1) / (width  - dr);
      const float v2 = REPETITION_COUNT_Y * float(j1) / (height - dr);

      glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(u1, v1); vg.vertex(i,  j,  h1[i]);
      glTexCoord2f(u1, v2); vg.vertex(i,  j1, h2[i]);
      glTexCoord2f(u2, v2); vg.vertex(i1, j1, h2[i1]);
      glTexCoord2f(u2, v1); vg.vertex(i1, j,  h1[i1]);
      glEnd();
    }
  }

  glPopMatrix();
}


std::string itos(int i) {
  char str[20];
  sprintf(str, "%d", i);
  return str;
}


void
TerrainApplication::drawHUD() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 640, 480, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);

  glColor3f(1, 1, 1);
  drawString(2, 20, getCamera()->getName());
  drawString(2, 40, "Detail Reduction: " + itos(mDetailReduction));
  drawString(2, 60, "Press H to toggle help.");

  if (mHelpShown) {
    drawHelp();
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}


void
TerrainApplication::drawHelp() {
  // fade what we've already rendered
  glColor4f(0, 0, 0, 0.5f);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0,   0);
  glVertex2f(640, 0);
  glVertex2f(640, 480);
  glVertex2f(0,   480);
  glEnd();

  glColor3f(1, 0.8f, 0);
  int base_x = 80;
  int base_y = 80;
  drawString(base_x, base_y += 20, "C      - Cycle camera");
  drawString(base_x, base_y += 20, "F      - Toggle fog");
  drawString(base_x, base_y += 20, "H      - Toggle help");
  drawString(base_x, base_y += 20, "Q, ESC - Quit");
  drawString(base_x, base_y += 20, "+      - Increase detail reduction");
  drawString(base_x, base_y += 20, "-      - Decrease detail reduction");
}


void
TerrainApplication::drawString(int x, int y, const std::string& str) {
  drawString(x, y, str.c_str());
}


void
TerrainApplication::drawString(int x, int y, const char* str) {
  glRasterPos2i(x, y);
  while (char c = *str++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
}
