#include <algorithm>
#include <functional>
#include <list>
#include <vector>
#include <GL/glut.h>
#include "glui.h"


struct Vector3f {
protected:
   Vector3f(float x_, float y_, float z_) {
      x = x_;
      y = y_;
      z = z_;
   }

public:
   float x, y, z;
};

struct Matrix4f {
   Matrix4f() {
      for (int i = 0; i < 16; ++i) {
         matrix[i] = 0;
      }
      for (int i = 0; i < 4; ++i) {
         matrix[i * 5] = 1;
      }
   }

   float matrix[16];
};

struct Translation : Vector3f {
   Translation(): Vector3f(0, 0, 0) { }
};

struct Scale : Vector3f {
   Scale(): Vector3f(1, 1, 1) { }
};

struct Rotation : Matrix4f {
};

void glTranslate(const Translation& translation) {
   glTranslatef(translation.x, translation.y, translation.z);
}

void glScale(const Scale& scale) {
   glScalef(scale.x, scale.y, scale.z);
}

void glRotate(const Rotation& rotation) {
   glMultMatrixf(rotation.matrix);
}


struct Node;


Node* gSelectedNode = 0;


struct Node {
   virtual ~Node() { }

   virtual void draw() = 0;

   Translation translation;
   Scale       scale;
   Rotation    rotation;

   void pushTransform() {

      if (this == gSelectedNode) {
         glColor3f(1, 0, 0);
      }

      glPushMatrix();
      glTranslate(translation);
      glScale(scale);
      glRotate(rotation);
   }

   void popTransform() {
      glPopMatrix();

      if (this == gSelectedNode) {
         glColor3f(1, 1, 1);
      }
   }

   void walk() {
      pushTransform();
      draw();
      popTransform();
   }
};


struct GroupNode : Node {
   static void destroy(Node* n) {
      delete n;
   }

   ~GroupNode() {
      for_each(mNodes.begin(), mNodes.end(), destroy);
      mNodes.clear();
   }

   void draw() {
      for_each(mNodes.begin(), mNodes.end(), mem_fun(&Node::walk));
   }

   void add(Node* node) {
      mNodes.push_back(node);
   }

   Node* remove(Node* node) {
      for (int i = 0; i < mNodes.size(); ++i) {
         if (mNodes[i] == node) {
            mNodes.erase(mNodes.begin() + i);
            return (mNodes.empty() ? 0 : mNodes[0]);
         }
      }

      // we didn't find one to delete
      return (mNodes.empty() ? 0 : mNodes[0]);
   }

   Node* getNext(Node* node) {
      for (int i = 0; i < mNodes.size(); ++i) {
         if (mNodes[i] == node) {
            return mNodes[(i + 1) % mNodes.size()];
         }
      }

      // we didn't find any
      return (mNodes.empty() ? 0 : mNodes[0]);
   }

   bool isEmpty() {
      return mNodes.empty();
   }

   std::vector<Node*> mNodes;
};


struct TorusNode : Node {
   void draw() {
      glutWireTorus(.5, 1, 20, 20);
   }
};


struct TeapotNode : Node {
   void draw() {
      glutWireTeapot(1);
   }
};


class SphereNode : public Node {
   void draw() {
      glutWireSphere(1, 10, 10);
   }
};


class CubeNode : public Node {
   void draw() {
      glutWireCube(1);
   }
};


GroupNode* gRoot = new GroupNode;
Rotation gSceneRotation;
GroupNode* gGroup = new GroupNode;


void drawAxes() {
   glBegin(GL_LINES);

   glColor3f (1, 0, 0);
   glVertex3f(0, 0, 0);
   glVertex3f(1, 0, 0);

   glColor3f (0, 1, 0);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 1, 0);
   
   glColor3f (0, 0, 1);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 0, 1);

   glEnd();
}


void display() {
   glClear(GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-4, 4, -4, 4, -100, 100);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // initial scene view
   gluLookAt(2, 2, 2, 0, 0, 0, 0, 0, 1);

   glRotate(gSceneRotation);
   
   drawAxes();

   // display the scene graph
   glColor3f(1, 1, 1);
   gRoot->walk();

   gGroup->walk();
   
   glutSwapBuffers();
}


void reshape(int w, int h) {
   glViewport(0, 0, w, h);
}


enum {
   ID_NEW_TORUS,
   ID_NEW_TEAPOT,
   ID_NEW_SPHERE,
   ID_NEW_CUBE,
   ID_QUIT,
   ID_TRANSLATION_X,
   ID_TRANSLATION_Y,
   ID_TRANSLATION_Z,
   ID_ROTATION,
   ID_SCALE_X,
   ID_SCALE_Y,
   ID_SCALE_Z,
   ID_NEXT,
   ID_DELETE,
   ID_ADD,
   ID_CLOSE,
   ID_SCENE_ROTATION,
};


GLUI_Translation* gTranslationX;
GLUI_Translation* gTranslationY;
GLUI_Translation* gTranslationZ;
GLUI_Rotation* gRotation;
GLUI_Spinner* gScaleX;
GLUI_Spinner* gScaleY;
GLUI_Spinner* gScaleZ;


void setSelected(Node* node) {
   gSelectedNode = node;

   if (node) {
      gTranslationX->set_x(node->translation.x);
      gTranslationY->set_y(node->translation.y);
      gTranslationZ->set_z(node->translation.z);
      gRotation->set_float_array_val(node->rotation.matrix);
      gScaleX->set_float_val(node->scale.x);
      gScaleY->set_float_val(node->scale.y);
      gScaleZ->set_float_val(node->scale.z);
   }
}


void add(Node* node) {
   gRoot->add(node);
   setSelected(node);
}


void gluiUpdate(int id) {
   switch (id) {
      case ID_NEW_TORUS:  add(new TorusNode);  break;
      case ID_NEW_TEAPOT: add(new TeapotNode); break;
      case ID_NEW_SPHERE: add(new SphereNode); break;
      case ID_NEW_CUBE:   add(new CubeNode);   break;
      case ID_QUIT: exit(0);

      case ID_TRANSLATION_X: 
      case ID_TRANSLATION_Y: 
      case ID_TRANSLATION_Z: 
         if (gSelectedNode) {
            gSelectedNode->translation.x = gTranslationX->get_x();
            gSelectedNode->translation.y = gTranslationY->get_y();
            gSelectedNode->translation.z = gTranslationZ->get_z();
         }
         break;

      case ID_ROTATION:
         if (gSelectedNode) {
            gRotation->get_float_array_val(gSelectedNode->rotation.matrix);
         }
         break;

      case ID_SCALE_X:
      case ID_SCALE_Y:
      case ID_SCALE_Z:
         if (gSelectedNode) {
            gSelectedNode->scale.x = gScaleX->get_float_val();
            gSelectedNode->scale.y = gScaleY->get_float_val();
            gSelectedNode->scale.z = gScaleZ->get_float_val();
         }
         break;

      case ID_NEXT:
         setSelected(gRoot->getNext(gSelectedNode));
         break;

      case ID_DELETE:
         if (gSelectedNode) {
            Node* n = gSelectedNode;
            setSelected(gRoot->remove(n));
            delete n;
         }
         break;

      case ID_ADD:
         if (gSelectedNode) {
            gGroup->add(gSelectedNode);
            setSelected(gRoot->remove(gSelectedNode));
         }
         break;

      case ID_CLOSE:
         if (!gGroup->isEmpty()) {
            add(gGroup);
            gGroup = new GroupNode;
         }
         break;
   }
   
   glutPostRedisplay();
}


int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(640, 480);
   
   int main_window = glutCreateWindow("Elementary Scene Graph - Chad Austin");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   
   GLUI* glui = GLUI_Master.create_glui("Scene Graph Manipulator");
   glui->set_main_gfx_window(main_window);
   glui->add_button("New Torus",  ID_NEW_TORUS,  gluiUpdate);
   glui->add_button("New Teapot", ID_NEW_TEAPOT, gluiUpdate);
   glui->add_button("New Sphere", ID_NEW_SPHERE, gluiUpdate);
   glui->add_button("New Cube",   ID_NEW_CUBE,   gluiUpdate);
   glui->add_button("Quit",       ID_QUIT,       gluiUpdate);

   gTranslationX = glui->add_translation("Translate X", GLUI_TRANSLATION_X, 0, ID_TRANSLATION_X, gluiUpdate);
   gTranslationY = glui->add_translation("Translate Y", GLUI_TRANSLATION_Y, 0, ID_TRANSLATION_Y, gluiUpdate);
   gTranslationZ = glui->add_translation("Translate Z", GLUI_TRANSLATION_Z, 0, ID_TRANSLATION_Z, gluiUpdate);
   gTranslationX->set_speed(0.5f);
   gTranslationY->set_speed(0.5f);
   gTranslationZ->set_speed(0.5f);

   gRotation = glui->add_rotation("Rotate", 0, ID_ROTATION, gluiUpdate);

   gScaleX = glui->add_spinner("Scale X", GLUI_SPINNER_FLOAT, 0, ID_SCALE_X, gluiUpdate);
   gScaleY = glui->add_spinner("Scale Y", GLUI_SPINNER_FLOAT, 0, ID_SCALE_Y, gluiUpdate);
   gScaleZ = glui->add_spinner("Scale Z", GLUI_SPINNER_FLOAT, 0, ID_SCALE_Z, gluiUpdate);
   gScaleX->set_float_val(1);
   gScaleY->set_float_val(1);
   gScaleZ->set_float_val(1);

   glui->add_button("Next",   ID_NEXT,   gluiUpdate);
   glui->add_button("Delete", ID_DELETE, gluiUpdate);
   glui->add_button("Add",    ID_ADD,    gluiUpdate);
   glui->add_button("Close",  ID_CLOSE,  gluiUpdate);
   glui->add_rotation("Scene Rotation", gSceneRotation.matrix, ID_SCENE_ROTATION, gluiUpdate);

   glutMainLoop();
}
