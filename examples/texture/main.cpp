#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include "Texture.h"

int gMainWindowID = 0;
int gWidth = 640;
int gHeight = 480;

// Is the left mouse button currently down?
bool gMouseDown = false;

// The last position of the mouse while held down
int gLastMouse[] = {0,0};

// Current rotation of our cube as (x,y,z)
int gRot[] = {0,0,0};

// Array of texture object pointers
Texture* gTextures[6];

// Flag so we can toggle the drawing of the textures
bool gTexturesEnabled = true;

// Out light's properties
GLfloat gDiffuse[] = {1, 1, 1, 0};     // diffuse
GLfloat gSpecular[] = {0.5f, 0, 0, 1}; // specular
GLfloat gLightPos[] = {5, 5, -5, 1};   // position

// The ambient light for the scene
GLfloat gAmbient[] = {0.3f, 0.3f, 0.3f};

// Flag so we can toggle lighting
bool gLightsEnabled = true;

//-----------------------------------------------------------------------------

void
drawCube()
{
   // Front Face (note that the texture's corners have to match the quad's corners)
   gTextures[0]->bind();
   glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      // bottom left, bottom right, top right, top left
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1,  1);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 1, -1,  1);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 1,  1,  1);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,  1,  1);
   glEnd();

   // Back Face
   gTextures[1]->bind();
   glBegin(GL_QUADS);
      glNormal3f(0,0,-1);
      // bottom right, top right, top left, bottom left
      glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(-1,  1, -1);
      glTexCoord2f(0.0f, 1.0f); glVertex3f( 1,  1, -1);
      glTexCoord2f(0.0f, 0.0f); glVertex3f( 1, -1, -1);
   glEnd();

   // Top Face
   gTextures[2]->bind();
   glBegin(GL_QUADS);
      glNormal3f(0,1,0);
      // top left, bottom left, bottom right, top right
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,  1, -1);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1,  1,  1);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 1,  1,  1);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 1,  1, -1);
   glEnd();

   // Bottom Face
   gTextures[3]->bind();
   glBegin(GL_QUADS);
      glNormal3f(0,-1,0);
      // top right, top left, bottom left, bottom right
      glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, -1, -1);
      glTexCoord2f(0.0f, 1.0f); glVertex3f( 1, -1, -1);
      glTexCoord2f(0.0f, 0.0f); glVertex3f( 1, -1,  1);
      glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1,  1);
   glEnd();

   // Right face
   gTextures[4]->bind();
   glBegin(GL_QUADS);
      glNormal3f(1,0,0);
      // bottom right, top right, top left, bottom left
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 1, -1, -1);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 1,  1, -1);
      glTexCoord2f(0.0f, 1.0f); glVertex3f( 1,  1,  1);
      glTexCoord2f(0.0f, 0.0f); glVertex3f( 1, -1,  1);
   glEnd();

   // Left Face
   gTextures[5]->bind();
   glBegin(GL_QUADS);
      glNormal3f(-1,0,0);
      // bottom left, bottom right, top right, top left
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, -1);
      glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1,  1);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(-1,  1,  1);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,  1, -1);
   glEnd();
}

//////////////////////////////////////////////////
// This is called on a glutPostRedisplay
//////////////////////////////////////////////////
void onRedisplay()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   // set up the projection matrix
   glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(80.0f, (float)gWidth / (float)gHeight, 0.01f, 1000.0f);

   // initialize your matrix stack used for transforming your models
   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   glTranslatef(0, 0, -10);

   glColor4f(1,1,1,1);
   glPushMatrix();
      glScalef(2,2,2);
      glRotatef(gRot[0], 1,0,0);  // rotate on the x axis
      glRotatef(gRot[1], 0,1,0);  // rotate on the y axis
      glRotatef(gRot[2], 0,0,1);  // rotate on the z axis

      if (gTexturesEnabled)
      {
         glEnable(GL_TEXTURE_2D);
      }
      drawCube();

      if (gTexturesEnabled)
      {
         glDisable(GL_TEXTURE_2D);
      }
   glPopMatrix();

   // swaps the front and back frame buffers.
   // hint: you've been drawing on the back, offscreen, buffer.
   // This command then brings that framebuffer onscreen.
   glutSwapBuffers();
}

//////////////////////////////////////////////////
// This is called repeatedly, as fast as possible
//////////////////////////////////////////////////
void onIdle()
{
   // According to the GLUT specification, the current window is
   // undefined during an idle callback.  So we need to explicitly change
   // it if necessary
   if (glutGetWindow() != gMainWindowID)
   {
      glutSetWindow(gMainWindowID);
   }

   // tell glut to call redisplay (which then calls onRedisplay)
   glutPostRedisplay();
}

/////////////////////////////////////////////
// This is called on a Resize of the glut window
/////////////////////////////////////////////
void onReshape(int width, int height)
{
   // save these params in case your app needs them
   gWidth = width;
   gHeight = height;

   // set your viewport to the extents of the window
   glViewport(0, 0, width, height);

   // let the app run idle, while resizing,
   // glut does not do this for us automatically, so call onIdle explicitly.
   onIdle();
}

////////////////////////////////
// This is called on a Down Keypress
////////////////////////////////
void onKeyboardDown(unsigned char key, int x, int y)
{
   switch (key)
   {
   // If user pressed 'q' or 'ESC', then exit the app.
   // this is really ungraceful, but necessary since GLUT does a while(1)
   // as it's control loop.  There is no GLUT method to exit, unfortunately.
   case 'q':
   case 27:
      exit(0);
      break;
   case 't':
      gTexturesEnabled = ! gTexturesEnabled;
      break;
   case 'l':
      gLightsEnabled = ! gLightsEnabled;
      if (gLightsEnabled)
      {
         glEnable(GL_LIGHTING);
      }
      else
      {
         glDisable(GL_LIGHTING);
      }
      break;
   default:
      // do nothing if no key is pressed
      break;
   }
}

void onMouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON)
   {
      gMouseDown = (state == GLUT_DOWN) ? true : false;
      gLastMouse[0] = x;
      gLastMouse[1] = y;
   }
}

void onMouseMove(int x, int y)
{
   // only rotate the cube a mouse button is being held down
   if (gMouseDown)
   {
      gRot[1] += (x - gLastMouse[0]);
      gRot[0] += (y - gLastMouse[1]);
   }
   gLastMouse[0] = x;
   gLastMouse[1] = y;
}

void main(int argc, char** argv)
{
   // Set the window's initial size
   glutInitWindowSize(640, 480);
   glutInit(&argc, argv);

   // Set to double buffer to reduce flicker
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

   // Set the window title
   gMainWindowID = glutCreateWindow("Texturing Example");

   // display callbacks.
   glutReshapeFunc(onReshape);
   glutIdleFunc(onIdle);
   glutDisplayFunc(onRedisplay);

   // keyboard callback functions.
   glutKeyboardFunc(onKeyboardDown);

   // disable key repeating.
   glutIgnoreKeyRepeat(1);

   glutMouseFunc(onMouse);
   glutMotionFunc(onMouseMove);

   // Create our textures
   gTextures[0] = new Texture("face0.tga");
   gTextures[1] = new Texture("face1.tga");
   gTextures[2] = new Texture("face2.tga");
   gTextures[3] = new Texture("face3.tga");
   gTextures[4] = new Texture("face4.tga");
   gTextures[5] = new Texture("face5.tga");

   // Setup our one light
   glLightfv(GL_LIGHT0, GL_DIFFUSE, gDiffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, gSpecular);
   glLightfv(GL_LIGHT0, GL_POSITION, gLightPos);

   // Set the global ambience
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmbient);
   glEnable(GL_LIGHT0);

   glEnable(GL_LIGHTING);

   // here we go. wheee ....
   glutMainLoop();
}
