#ifndef DRIVING_APP_H
#define DRIVING_APP_H


#include <gk/gk.h>


class DrivingApp : public gk::AbstractGameApp {
public:
  DrivingApp();
  virtual ~DrivingApp();

  /**
   * Called by the game kernel when the application is being initialized,
   * but before the system driver has been started.
   *
   * We initialize the input interfaces here.
   *
   * @param kernel     the IGameKernel initializing this driver
   */
  virtual void onAppInit(gk::IGameKernel* kernel);

  /**
   * Called by the game kernel when the window is initialized.
   */
  virtual void onContextInit();

  /**
   * Called by the game kernel each frame for each window open.
   *
   * @param context    the context of the window being drawn
   */
  virtual void onContextDraw(int context);

  /**
   * Called by the game kernel immediately after each frame is drawn.
   */
  virtual void onPostFrame();

public:
  gk::DigitalInterface
    mAccelerate,
    mBrake,
    mTurnLeft,
    mTurnRight,
    mPause,
    mQuit;

  gk::IGameKernel* mKernel;

  struct Vector3f {
    Vector3f() {
      x = y = z = 0;
    }

    float x, y, z;
  };

  Vector3f m_position;
  Vector3f m_orientation;
  float m_velocity;
};


#endif
