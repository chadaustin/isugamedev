#ifndef PHUI_GLUT_BRIDGE_H
#define PHUI_GLUT_BRIDGE_H


#include "Input.h"


namespace phui {

   class RootWidget;

   InputKey GlutToPhuiKey(char key);
   InputKey GlutSpecialToPhuiKey(int key);
   InputButton GlutToPhuiButton(int button);

   void glutRegisterRoot(RootWidget* root);

}


#endif
