#include <GL/glut.h>
#include "client/Scene.h"
#include "client/Camera.h"
#include <gmtl/Generate.h>
#include <gmtl/Convert.h>
#include <gmtl/MatrixOps.h>
#include <map>
#include <string>
using namespace client;

int gWidth = 640;
int gHeight = 480;
int gContext = 0;
Scene* gScene = NULL;
//Camera gCam;
std::map<std::string, bool> input;

int gLastTime;

const float PI = 3.141579;

template< class T >
T deg2rad(const T& deg)
{
   return (deg / T(180) * PI);
}

template< class T >
T rad2deg(const T& rad)
{
   return (rad * T(180) / PI);
}

void processInput(float dt)
{
   if (input["accel"])
   {
      osg::Vec3 forward(0,0,500);
      osg::Transform* tankTrans = gScene->getObject("tank");
      tankTrans->preMult(osg::Matrix::translate(forward * dt));
   }
   if (input["brake"])
   {
      osg::Vec3 backward(0,0,-500);
      osg::Transform* tankTrans = gScene->getObject("tank");
      tankTrans->preMult(osg::Matrix::translate(backward * dt));
   }
   if (input["turnleft"])
   {
      float ang = deg2rad(60.0f);
      osg::Transform* tankTrans = gScene->getObject("tank");
      tankTrans->preMult(osg::Matrix::rotate(ang * dt, 0,1,0));
   }
   if (input["turnright"])
   {
      float ang = deg2rad(-60.0f);
      osg::Transform* tankTrans = gScene->getObject("tank");
      tankTrans->preMult(osg::Matrix::rotate(ang * dt, 0,1,0));
   }
//   if (input["zoomout"])
//   {
//      float speed = 250.0f * dt;
//      gCam.setFollowDist(gCam.getFollowDist() + speed);
//   }
//   if (input["zoomin"])
//   {
//      float speed = 250.0f * dt;
//      gCam.setFollowDist(gCam.getFollowDist() - speed);
//   }
}

void display()
{
   glClearColor(0,0,0,1);
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gScene->draw();

   glDisable(GL_LIGHTING);
   int extent = 100000;
   glColor3f(0,0,1);
   glBegin(GL_LINES);
      for (int i=-extent; i<extent; i+=100)
      {
         glVertex3f(-extent, 0, i);
         glVertex3f( extent, 0, i);
         glVertex3f( i, 0, -extent);
         glVertex3f( i, 0,  extent);
      }
   glEnd();
   glEnable(GL_LIGHTING);

   glutSwapBuffers();
}

void reshape(int width, int height)
{
   gWidth = width;
   gHeight = height;
   glViewport(0, 0, gWidth, gHeight);

   glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(80.0f, (GLfloat)gWidth/(GLfloat)gHeight, 0.01f, 1000.0f);
}

void idle()
{
   if (glutGetWindow() != gContext)
   {
      glutSetWindow(gContext);
   }
   glutPostRedisplay();

   int curTime = glutGet(GLUT_ELAPSED_TIME);
   float dt = (float)(gLastTime - curTime) / 1000.0f;
   gLastTime = curTime;

   processInput(dt);

   osg::Matrix inv;
   inv.invert(gScene->getObject("tank")->getMatrix());
   gScene->mFollowTarget->setMatrix(inv);
/*
   // Figure out the camera's new target
   osg::Transform* t = gScene->getObject("tank");
   gmtl::Vec3f targetPos;
   targetPos.set(t->getMatrix().getTrans().ptr());

   osg::Quat q;
   q.set(t->getMatrix());
   gmtl::Vec3f rots;
   rots.set(q.asVec3().ptr());
   gmtl::Quatf targetRot;
   gmtl::convert(targetRot, rots);

   gCam.setTarget(targetPos, targetRot);
   gmtl::Matrix44f inv;
   gmtl::invert(inv, gCam.getTransform());
   osg::Matrix camMat(inv.getData());

   gScene->getView()->setMatrix(camMat);

   // Update the camera
   gCam.update(dt);
*/
}

void keyDown(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 27:
      exit(0);
      break;
   case 'w':
      input["accel"] = true;
      break;
   case 's':
      input["brake"] = true;
      break;
   case 'a':
      input["turnleft"] = true;
      break;
   case 'd':
      input["turnright"] = true;
      break;
   case 'q':
      input["zoomin"] = true;
      break;
   case 'e':
      input["zoomout"] = true;
      break;
   case 'f':
//      gCam.setFollow(! gCam.getFollow());
      break;
   }
/*
   case 'w':
      {
         osg::Vec3 forward(0,0,-1);
         osg::Transform* tankTrans = gScene->getObject("tank");
         tankTrans->preMult(osg::Matrix::translate(forward));
         gScene->getObject("tank")->postMult(osg::Matrix::translate(forward));
//         osg::Transform* t = gScene->getView();
//         osg::Vec3 forward(0,0,-5);
//         t->setPosition(t->getPosition() + forward);
         break;
      }
   case 's':
      {
         osg::Vec3 forward(0,0,1);
         osg::Transform* tankTrans = gScene->getObject("tank");
         tankTrans->preMult(osg::Matrix::translate(forward));
         tankTrans->postMult(osg::Matrix::translate(forward));
//         osg::Transform* t = gScene->getView();
//         osg::Vec3 forward(0,0,-5);
//         t->setPosition(t->getPosition() + forward);
         break;
      }
   case 'a':
      {
         float ang = deg2rad(5.0f);
         osg::Transform* tankTrans = gScene->getObject("tank");
         tankTrans->preMult(osg::Matrix::rotate(ang, 0,1,0));
      }
   case 'd':
      {
         float ang = deg2rad(-5.0f);
         osg::Transform* tankTrans = gScene->getObject("tank");
         tankTrans->preMult(osg::Matrix::rotate(ang, 0,1,0));
      }
*/
}

void keyUp(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'w':
      input["accel"] = false;
      break;
   case 's':
      input["brake"] = false;
      break;
   case 'a':
      input["turnleft"] = false;
      break;
   case 'd':
      input["turnright"] = false;
      break;
   case 'q':
      input["zoomin"] = false;
      break;
   case 'e':
      input["zoomout"] = false;
      break;
   }
}

int main(int argc, char** argv)
{
   glutInitWindowSize(gWidth, gHeight);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
   gContext = glutCreateWindow("Scene Test");

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutIdleFunc(idle);
   glutKeyboardFunc(keyDown);
   glutKeyboardUpFunc(keyUp);

   glutIgnoreKeyRepeat(1);

   gScene = new Scene();
   gScene->addObject("tank", "HoverTankBody.obj");
//   gScene->getObject("tank")->preMult(osg::Matrix::rotate(deg2rad(180.0f), 0,0,1));
   gScene->addObject("tank2", "HoverTankBody.obj");
   gScene->getObject("tank2")->preMult(osg::Matrix::rotate(deg2rad(180.0f), 0,0,1));
   gScene->getObject("tank2")->preMult(osg::Matrix::translate(300,0,-500));

//   gCam.setFollowDist(1000.0f);
//   gCam.setPitch(deg2rad(15.0f));
//   gCam.setFollow(false);

   gLastTime = glutGet(GLUT_ELAPSED_TIME);
   glutMainLoop();
}
