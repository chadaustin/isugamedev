// simple glut application: look for the !!!TODO!!!s, and fill in your code 
//                          there as needed
// Josh Brown - browner@iastate.edu
// Public domain
//


#ifdef WIN32
   #include <windows.h>  // make the app win32 friendly. :)
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cppdom/cppdom.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
 #include "HUD.h"

// a place to store application data...
class App
{
public:
   App() : width( 0 ), height( 0 ), mainWin_contextID( -1 )
   {
   }
   int width, height;
   int mainWin_contextID;
   HUD cursor;
};
App app;

int* grid;
float SCALE=4;
int LIMIT;
float camera=0.0f;
int arg1, arg2, arg3;
float rot1, rot2;
bool KEY_PUSH;
bool snapOn, gridOn;
bool removeObj;

int addingNavNodeLink; // -1 not adding :: 0 adding no-node selected :: 1 adding 1 node selected
int addingNavNode;  // 0 if not adding :: 1 if adding

int drawOnMouse;

GLint menuMain;
GLint menuFile;
GLint menuModel;
GLint menuOptions;
GLint menuGetModels;
GLint menuSnap;
GLint menuGrid;
float rd,gn,bl;
float transX;

int mouseX, mouseY;

int navNodeCounter;

class model
{
public:
   model(){
      worldX=0.0f;
      worldY=0.0f;
      worldZ=0.0f;
   }
   virtual ~model()
   {}
   
   float xhi;
   float xlo;
   float yhi;
   float ylo;
   float r,g,b;
   std::string name;
   float worldX, worldY,worldZ;
};

class navNodeId : public model
{
public:
   ~navNodeId()
   {}
   int id;
};

class pair
{
public:
   pair()
   {
      model1 = NULL;
      model2 = NULL;
   }

   pair(navNodeId* m)
   {
      model1 = m;
      model2 = NULL;
   }

   pair(navNodeId* m1, navNodeId* m2)
   {
      model1 = m1;
      model2 = m2;
   }
   navNodeId* model1;
   navNodeId* model2;
};


std::vector<model> modelsInWorld;
std::vector<model> modelsInMenu;

std::vector<pair> navNodeLinks;
std::vector<navNodeId*> navNodes;

float cameraPan[2];


using namespace cppdom;

void processObjNode(XMLNode &node)
{
   model* mModel = new model();
   std::string name = node.getName();
      
   std::cout << "This Node is a: " << name << std::endl;


   
   XMLNodePtr cNode = node.getChild(std::string("size"));
   std::cout << "node: " << cNode->getName() << std::endl;
   mModel->xhi = cNode->getAttribute("xhi").getValue<float>();
   mModel->xlo = cNode->getAttribute("xlo").getValue<float>();
   mModel->yhi = cNode->getAttribute("yhi").getValue<float>();
   mModel->ylo = cNode->getAttribute("ylo").getValue<float>();
   std::cout << "mModel.xlo: " << mModel->xlo << "  mModel.ylo: " << mModel->b << std::endl;
   std::cout << "type: " << cNode->getType() << std::endl;
   cNode = node.getChild(std::string("color"));
   mModel->r = cNode->getAttribute(std::string("r")).getValue<float>();
   mModel->g = cNode->getAttribute(std::string("g")).getValue<float>();
   mModel->b = cNode->getAttribute(std::string("b")).getValue<float>();
   cNode = node.getChild(std::string("type"));
   mModel->name = cNode->getAttribute(std::string("name")).getValue<std::string>();
   modelsInMenu.push_back(*mModel);
}
   

void dumpObjectNode(XMLNode &node)
{
   std::string name = node.getName();
   XMLNodeList& nlist = node.getChildren();
   XMLNodeList::const_iterator itr, stop;
   itr = nlist.begin();
   stop = nlist.end();
   
   XMLNodePtr node1 = *itr;
   nlist = node1->getChildren();
   itr = nlist.begin();
   stop = nlist.end();
   
   while(itr != stop)
   {
      XMLNodePtr node1 = *itr;

      std::cout << "node: " << node1->getName() << std::endl;
      processObjNode(*node1);
      ++itr;
   }
}
   

void parceobjectsfile(std::string filename)
{
   std::cout << "processing [" << filename << "] ..." << std::endl;

   XMLContextPtr context( new XMLContext );
   XMLDocument node(context);
   std::ifstream istr( filename.c_str());


   
   if(!istr)
   {
      std::cerr << "bad file: " << filename << std::endl;
      return;
   }

   try
   {
      node.load( istr, context);
      dumpObjectNode(node);
      std::ofstream ostr( "parsetest.xml");
      node.save(ostr);
      ostr.close();
   }
   catch (XMLError e)
   {
      XMLLocation where( context->getLocation() );
      std::string errmsg;
      e.getStrError(errmsg);
      // print out where the error occured
      std::cout << filename << ":" << std::cout << filename << ":" << where.getLine() << " ";
         std::cout << "at position " << where.getPos();
         std::cout << ": error: " << errmsg.c_str();
         std::cout << std::endl;

         // print out line where the error occured
         std::ifstream errfile( filename.c_str() );
         if(!errfile)
         {
            std::cerr << "Can't open file [" << filename << "] to output error" << std::endl;
         }

         int linenr = where.getLine();
         char linebuffer[1024];
         for(int i=0; i<linenr && !errfile.eof(); i++)
            errfile.getline( linebuffer,1024 );

         int pos = where.getPos();
         if (pos>=80)
            pos %= 80;

         std::string err_line( linebuffer + (where.getPos()-pos) );
         if (err_line.length()>=79)
            err_line.erase(79);
         std::cout << err_line << std::flush;
         std::cout << err_line.c_str() << std::endl;
         std::cout << linebuffer << std::endl;
         for(int j=2;j<pos;j++)
            std::cout << " ";
      std::cout << '^' << std::endl;
   
      }
   }

void menuFunc(int option)
{
   switch (option)
   {
      case 1:
         rd=1;
         gn=0;
         bl=0;
         break;
      case 2:
         rd=0;
         gn=1;
         bl=0;
         break;
      case 3:
         rd=0;
         gn=0;
         bl=1;
         break;
   }
   return;
}


void drawOrigin()
{
   glColor3f(1.0f,0.0f,0.0f);
   glBegin(GL_LINES);
      glVertex2f(0.5f,0.5f);
      glVertex2f(-0.5f,-0.5f);
      glVertex2f(-0.5f,0.5f);
      glVertex2f(0.5f,-0.5f);
   glEnd();
}

void drawNavNodeLinks()
{
   glColor3f(0.6f, 0.6f, 0.6f);
   for(std::vector<pair>::iterator itr=navNodeLinks.begin();itr!=navNodeLinks.end();itr++)
   {
      if((*itr).model2!=NULL)
      {
         glBegin(GL_LINES);
            glVertex2f((*itr).model1->worldX-.3, (*itr).model1->worldY-.3);
            glVertex2f((*itr).model2->worldX-.3, (*itr).model2->worldY-.3);
         glEnd();
      }
   }
}

void drawNavNodes()
{
   for(std::vector<navNodeId*>::iterator itr=navNodes.begin();itr!=navNodes.end();itr++)
   {
      glPushMatrix();
      glTranslatef((*itr)->worldX, (*itr)->worldY,0);
      glColor3f(0.6f, 0.6f, 0.6f);
      glBegin(GL_POLYGON);
         glVertex2f(0.75, 0.75);
         glVertex2f(0.75, -0.75);
         glVertex2f(-0.75, -0.75);
         glVertex2f(-0.75, 0.75);
      glEnd();
      glPopMatrix();
   }
}

void drawModels()
{
   for(unsigned int i=0;i<modelsInWorld.size();i++)
   {
      glPushMatrix();
      glTranslatef(modelsInWorld[i].worldX, modelsInWorld[i].worldY, 0);
      glColor3f(modelsInWorld[i].r, modelsInWorld[i].g, modelsInWorld[i].b);
      glBegin(GL_POLYGON);
         glVertex2f(modelsInWorld[i].xhi, modelsInWorld[i].yhi);
         glVertex2f(modelsInWorld[i].xlo, modelsInWorld[i].yhi);
         glVertex2f(modelsInWorld[i].xlo, modelsInWorld[i].ylo);
         glVertex2f(modelsInWorld[i].xhi, modelsInWorld[i].ylo);
      glEnd();
      glPopMatrix();
   }
   
}
   


void drawGrid(int limit)
{
   grid = new int[limit*limit];
   LIMIT = limit;
   glColor3f(0.3f, 0.3f, 0.3f);
   for(int i=-(limit/2);i<(limit/2);i++){
         glBegin(GL_LINES);
            glVertex2f(-(limit/2),i);
            glVertex2f((limit/2),i);
         glEnd();
         glBegin(GL_LINES);
            glVertex2f(i,-(limit/2));
            glVertex2f(i,(limit/2));
         glEnd();
   }     
   delete[] grid;
}


void getWorldCoords(float& x, float& y){
   x=(mouseX-(app.width/2))/(SCALE/2)-cameraPan[0];
   y=-((mouseY-(app.height/2))/(SCALE/2)+cameraPan[1]);
}

//x and y are overwritten here pass in the world coordinates and they are
//replaced by the windows coordinates
void getMouseCoords(float& x, float& y)
{
   x=x+cameraPan[0]*(SCALE/2)+(app.width/2);
   y=(y-cameraPan[1]*(SCALE/2)+(app.height/2));
   
}





void drawObjAtMouse()
{
   if(drawOnMouse!=-1)
   {
      float TEMPSCALE=SCALE/2;
      int snapOffsetX;
      int snapOffsetY;
      glColor3f(modelsInMenu[drawOnMouse-1].r, modelsInMenu[drawOnMouse-1].g, modelsInMenu[drawOnMouse-1].b);
      
      int tempX = static_cast<int>(cameraPan[0]);
      int tempY = static_cast<int>(cameraPan[1]);
      
      if(snapOn) // then add to mouseX and mouseY the offset that we need for snap it. 
      {
         snapOffsetX=static_cast<int>(app.width/(app.width/SCALE*2));
         snapOffsetY=static_cast<int>(app.height/(app.height/SCALE*2));
         mouseX=mouseX-mouseX%snapOffsetX;
         if(tempX!=cameraPan[0]) mouseX+=snapOffsetX/2;
         mouseY=mouseY-mouseY%snapOffsetY;
         if(tempY!=cameraPan[1]) mouseX+=snapOffsetY/2;
      }
         
      
      glTranslatef(mouseX, mouseY, 0);
      glBegin(GL_POLYGON);
         glVertex2f(modelsInMenu[drawOnMouse-1].xhi*TEMPSCALE, -modelsInMenu[drawOnMouse-1].yhi*TEMPSCALE);
         glVertex2f(modelsInMenu[drawOnMouse-1].xlo*TEMPSCALE, -modelsInMenu[drawOnMouse-1].yhi*TEMPSCALE);
         glVertex2f(modelsInMenu[drawOnMouse-1].xlo*TEMPSCALE, -modelsInMenu[drawOnMouse-1].ylo*TEMPSCALE);
         glVertex2f(modelsInMenu[drawOnMouse-1].xhi*TEMPSCALE, -modelsInMenu[drawOnMouse-1].ylo*TEMPSCALE);
      glEnd();
      glTranslatef(-mouseX, -mouseY, 0);  // translate back
   }
   else // drawOnMouse == -1 so we are drawing the a new NavNode
   {
      float TEMPSCALE=SCALE/2;
      int snapOffsetX;
      int snapOffsetY;
      glColor3f(0.6f, 0.6f, 0.6f);
      int tempX = static_cast<int>(cameraPan[0]);
      int tempY = static_cast<int>(cameraPan[1]);

      if(snapOn) // then adjust mouseX and mouseY for the snap
      {
         snapOffsetX=static_cast<int>(app.width/(app.width/SCALE*2));
         snapOffsetY=static_cast<int>(app.height/(app.height/SCALE*2));
         
         mouseX=mouseX-mouseX%snapOffsetX;
         if(tempX!=cameraPan[0]) 
            mouseX+=snapOffsetX/2;
         
         mouseY=mouseY-mouseY%snapOffsetY;
         if(tempY!=cameraPan[1]) 
            mouseX+=snapOffsetY/2;
      }

      glPushMatrix();
      glTranslatef(mouseX, mouseY, 0);
      glBegin(GL_POLYGON);
         glVertex2f(0.75*TEMPSCALE, -0.75*TEMPSCALE);
         glVertex2f(0.75*TEMPSCALE, 0.75*TEMPSCALE);
         glVertex2f(-0.75*TEMPSCALE, 0.75*TEMPSCALE);
         glVertex2f(-0.75*TEMPSCALE, -0.75*TEMPSCALE);
      glEnd();
      glPopMatrix(); // pop off the transform
   }
}


//////////////////////////////////////////////////
// this is called on a glutpostredisplay
//////////////////////////////////////////////////
static void OnRedisplay()
{ 
   glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
   
   
   // set up the projection matrix
   glMatrixMode( GL_PROJECTION );
        glLoadIdentity();                     
        gluOrtho2D(-app.width/SCALE , app.width/SCALE, -app.height/SCALE , app.height/SCALE);
                           
   // initialize your matrix stack used for transforming your models
    glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();      

      
      
   // move by the camera coordinates:
   glTranslatef(cameraPan[0], cameraPan[1], 0);
   

   //draw the origin
   drawOrigin();
   
   if(gridOn)
   {
      drawGrid(app.width);
   }
   drawModels();
   drawNavNodes();
   
   drawNavNodeLinks();
   
   glPushMatrix();
   glTranslatef(5,5,0);

   glPopMatrix();
   
   float tempx, tempy;
   getWorldCoords(tempx, tempy);
   app.cursor.draw(tempx,tempy, app.width, app.height);
   glLoadIdentity();

   if(drawOnMouse!=0)
   {
      drawObjAtMouse();
   }
   
   // !!!todo!!!: ////////////////////////////////////////
   
   // swaps the front and back frame buffers.
   // hint: you've been drawing on the back, offscreen, buffer.  
   // this command then brings that framebuffer onscreen.
   glutSwapBuffers();
}

//////////////////////////////////////////////////
// this is called repeatedly, as fast as possible
//////////////////////////////////////////////////
static void OnIdle()
{
   // according to the glut specification, the current window is
   // undefined during an idle callback.  so we need to explicitly change
   // it if necessary
   if ( glutGetWindow() != app.mainWin_contextID )
           glutSetWindow( app.mainWin_contextID );

   // tell glut to call redisplay (which then calls onredisplay)
   glutPostRedisplay();
}

/////////////////////////////////////////////
// this is called on a resize of the glut window
/////////////////////////////////////////////
static void OnReshape( int width, int height ) 
{
   // save these params in case your app needs them
   app.width = width;
   app.height = height;
   
   // set your viewport to the extents of the window
   glViewport( 0, 0, width, height );
   
   // let the app run idle, while resizing, 
   // glut does not do this for us automatically, so call onidle explicitly.
   OnIdle();
}

////////////////////////////////
// this is called on a down keypress        
////////////////////////////////
static void OnKeyboardDown( unsigned char k, int x, int y )
{ 
   switch (k)
   {
   // if user pressed 'q' or 'esc', then exit the app.
   // this is really ungraceful, but necessary since glut does a while(1)
   // as it's control loop.  there is no glut method to exit, unfortunately.
   case 'q':
   case 27:
      exit( 0 );
      break;

   case 'z':
      KEY_PUSH = true;
      // !!!todo!!!: add handler for when down is pressed
      break;

      
   default:
      // do nothing if no key is pressed
      break;
   }
}
////////////////////////////////
// this is called on a up keypress        
////////////////////////////////
static void OnKeyboardUp( unsigned char k, int x, int y ) 
{
   switch (k)
   {
   case 'a':
      // !!!todo!!!: add handler for when up is released
      break;

   case 'z':
      KEY_PUSH = false;
      // !!!todo!!!: add handler for when down is released
      break;
   
   default:
      // do nothing if no key is pressed
      break;
   }
}

////////////////////////////////
// this is called on a down keypress 
// of a "special" key such as the grey arrows.
////////////////////////////////
static void OnSpecialKeyboardDown(int k, int x, int y) 
{
   switch (k)
   {
case GLUT_KEY_PAGE_UP:
      // !!!todo!!!: add handler for when up is pressed
      if(SCALE<64)
         SCALE*=2;
      break;
   case GLUT_KEY_PAGE_DOWN:
      // !!!todo!!!: add handler for when down is pressed
      if(SCALE>4)
         SCALE*=.5;
      break;
   case GLUT_KEY_UP:
      if(cameraPan[1]<LIMIT/2);
         cameraPan[1]+=.5;
      break;
   case GLUT_KEY_DOWN:
      if(cameraPan[1]>-LIMIT/2)
         cameraPan[1]-=.5;
      break;
   case GLUT_KEY_RIGHT:
      if(cameraPan[0]<LIMIT/2)
         cameraPan[0]+=.5;
      break;
   case GLUT_KEY_LEFT:
      if(cameraPan[0]>-LIMIT/2)
         cameraPan[0]-=.5;
      break;
   default:
      // do nothing if no special key pressed
      break;
   }
}

////////////////////////////////
// this is called on a up keypress        
////////////////////////////////
static void OnSpecialKeyboardUp( int k, int x, int y ) 
{
   switch (k)
   {
   case GLUT_KEY_UP:
      // !!!todo!!!: add handler for when up is released
      break;
   case GLUT_KEY_DOWN:
      // !!!todo!!!: add handler for when down is released
      break;
   default:
      // do nothing if no special key pressed
      break;
   }
}

////////////////////////////////
// this is called when mouse changes position
// x and y are the screen position 
// in your 2d window's coordinate frame
////////////////////////////////
static void OnMousePos( int x, int y ) 
{
   // !!!todo!!!: do something based on mouse position
   mouseX = x;
   mouseY = y;
}

void addObjToWorld(float& x, float& y)
{
   getWorldCoords(modelsInMenu[drawOnMouse-1].worldX, modelsInMenu[drawOnMouse-1].worldY);
   modelsInWorld.push_back(modelsInMenu[drawOnMouse-1]);
   drawOnMouse=0;
}

void addNavNodeToWorld(float& x, float& y)
{
   navNodeId* tempNode = new navNodeId();
   tempNode->id = navNodeCounter;
   getWorldCoords(tempNode->worldX, tempNode->worldY);
   navNodes.push_back(tempNode);
   navNodeCounter++;
   drawOnMouse=0;
   std::cout << "adding navNode " << tempNode->id << " to world." << std::endl;
}
   

////////////////////////////////
// this is called when mouse clicks
////////////////////////////////
static void OnMouseClick( int a, int b, int c, int d )
{

   float x, y;
   if(a==GLUT_LEFT_BUTTON && b==GLUT_DOWN)
   {  
      x = c;
      y = app.height-d;
      
      
      if(drawOnMouse>0)
      {
         addObjToWorld(x,y);
      }
      else if(drawOnMouse==-1)
      {
         addNavNodeToWorld(x,y);
      }
      if(removeObj==true)
      {
         bool flag=false; 
         float tempX, tempY;
         getWorldCoords(tempX, tempY);
         std::vector<model>::iterator temp;
         for(std::vector<model>::iterator itr=modelsInWorld.begin();itr!=modelsInWorld.end();itr++)
         {
            // this checks to see if the mouse click happened over the top of an
            // object or not
            if((tempX<(itr->worldX+itr->xhi)) && (tempX>(itr->worldX+itr->xlo)) && 
                  (tempY<(itr->worldY+itr->yhi)) && (tempY>(itr->worldY+itr->ylo)))
            {
               flag=true;
               temp = itr;
               std::cout << "removing object!" << std::endl;
            }
         }
         if(flag){
            modelsInWorld.erase(temp);
            flag=false;
         }
         removeObj=false;
      }
      else if(addingNavNodeLink==0)
      {
         std::cout << "add navNodeLink ..." << std::endl;
         bool flag=false;
         float tempX, tempY;
         getWorldCoords(tempX, tempY);
         for(std::vector<navNodeId*>::iterator itr=navNodes.begin();itr!=navNodes.end();itr++)
         {
            if((tempX<((*itr)->worldX+0.75)) && (tempX>((*itr)->worldX-0.75)) && (tempY<((*itr)->worldY+0.75)) && (tempY>((*itr)->worldY-0.75)))
            {
               std::cout << "clicked on navNode" << std::endl;
               pair p(*itr);
               flag=true;
               navNodeLinks.push_back(p);
               std::cout << "marked first nav node!" << std::endl;
               addingNavNodeLink=1;
            }

         }
      }
      else if(addingNavNodeLink==1)
      {
         float tempX, tempY;
         getWorldCoords(tempX, tempY);
         for(std::vector<navNodeId*>::iterator itr=navNodes.begin();itr!=navNodes.end();itr++)
         {
            if((tempX<((*itr)->worldX+0.75)) && (tempX>((*itr)->worldX-0.75)) && (tempY<((*itr)->worldY+0.75)) && (tempY>((*itr)->worldY-0.75)))
            {
               navNodeLinks.back().model2 = (*itr);
               std::ostringstream s;
               s << (*itr)->id;
               std::cout << "Nav node link established! navNode: " << s.str() << std::endl;
               addingNavNodeLink=-1;
            }
         }
      }

   }
}


// initialize the application
// initialize the state of your app here if needed...
static void OnApplicationInit()
{
   // don't put open gl code here, this func may be called at anytime
   // even before the api is initialized 
   // (like before a graphics context is obtained)
   
   
   // !!!todo!!!: put your initialization code here.
   
   KEY_PUSH = false;

   cameraPan[0]=cameraPan[1]=0;
}

void setupOutputLevelFile(XMLNodePtr& mNode)
{
   XMLContextPtr mContext = XMLContextPtr(new XMLContext);
   mNode = XMLNodePtr(new XMLNode(mContext));
   mNode->setName("hi");
   mNode->setType(xml_nt_node);
   XMLNodePtr newNode(new XMLNode(mContext));
   newNode->setName("josh");
   newNode->setType(xml_nt_node);
   mNode->addChild(newNode);
}

void NowWeCanReallyAddTheLevel(XMLNodePtr& levelNode, XMLContextPtr& context)
{
   std::string temp;
   char namePostFix = 'A';  // a postfix character to add as a name so we can distinguish between different navNodes. -- this is an ugly hack.
   std::cout << "writing out models..." << std::endl;

   

   for(unsigned int i=0;i<modelsInWorld.size();i++)
   {
      XMLNodePtr staticNode(new XMLNode(context));
      XMLNodePtr posNode(new XMLNode(context));
      XMLNodePtr rotNode(new XMLNode(context));
      XMLNodePtr nameNode(new XMLNode(context));
      XMLNodePtr realNameNode(new XMLNode(context));
      
      
      staticNode->setName("static");
      posNode->setName("pos");
      rotNode->setName("rot");
      nameNode->setName("model");

               
      
      staticNode->setType(xml_nt_node);
      posNode->setType(xml_nt_leaf);
      nameNode->setType(xml_nt_node);
      rotNode->setType(xml_nt_leaf);
      realNameNode->setType(xml_nt_cdata);
      
      
      levelNode->addChild(staticNode);
      
      posNode->setAttribute("x", modelsInWorld[i].worldX);
      posNode->setAttribute("y", modelsInWorld[i].worldZ);
      posNode->setAttribute("z", modelsInWorld[i].worldY);
      
      staticNode->addChild(posNode);
      rotNode->setAttribute("x", 0.0f);
      rotNode->setAttribute("y", 0.0f);
      rotNode->setAttribute("z", 0.0f);
      staticNode->addChild(rotNode);

      realNameNode->setCdata(modelsInWorld[i].name);
      nameNode->addChild(realNameNode);
      staticNode->addChild(nameNode);

      if(modelsInWorld[i].name==std::string("turret"))
      {
         std::cout << "adding turret info to xml node" << std::endl;
         staticNode->setName("turret");
         XMLNodePtr turretNameNode(new XMLNode(context));
         XMLNodePtr maxChildNode(new XMLNode(context));
         XMLNodePtr aiLevelNode(new XMLNode(context));
         XMLNodePtr parentNode(new XMLNode(context));
         XMLNodePtr realParentNode(new XMLNode(context));
         XMLNodePtr realTurretNameNode(new XMLNode(context));

         turretNameNode->setType(xml_nt_node);
         realTurretNameNode->setType(xml_nt_cdata);
         parentNode->setType(xml_nt_node);
         realParentNode->setType(xml_nt_cdata);
         aiLevelNode->setType(xml_nt_leaf);
         maxChildNode->setType(xml_nt_leaf);

         turretNameNode->setName("name");
         parentNode->setName("parent");
         aiLevelNode->setName("level");
         maxChildNode->setName("maxChildren");
         
         realParentNode->setCdata("null");
         realTurretNameNode->setCdata("turret");
         
         aiLevelNode->setAttribute("nu", -1);
         maxChildNode->setAttribute("num", 0);
         parentNode->addChild(realParentNode);
         turretNameNode->addChild(realTurretNameNode);

         staticNode->addChild(aiLevelNode);
         staticNode->addChild(parentNode);
         staticNode->addChild(turretNameNode);
         staticNode->addChild(maxChildNode);
      }
      else if(modelsInWorld[i].name==std::string("security_droid"))
      {
         std::cout << "adding droid info to xml node" << std::endl;
         staticNode->setName("security_droid");

         XMLNodePtr droidNameNode(new XMLNode(context));
         XMLNodePtr maxChildNode(new XMLNode(context));
         XMLNodePtr aiLevelNode(new XMLNode(context));
         XMLNodePtr parentNode(new XMLNode(context));
         XMLNodePtr realParentNode(new XMLNode(context));
         XMLNodePtr realDroidNameNode(new XMLNode(context));

         droidNameNode->setType(xml_nt_node);
         realDroidNameNode->setType(xml_nt_cdata);
         parentNode->setType(xml_nt_node);
         realParentNode->setType(xml_nt_cdata);
         aiLevelNode->setType(xml_nt_leaf);
         maxChildNode->setType(xml_nt_leaf);

         droidNameNode->setName("name");
         parentNode->setName("parent");
         aiLevelNode->setName("level");
         maxChildNode->setName("maxChildren");

         realParentNode->setCdata("null");
         realDroidNameNode->setCdata("droid");

         aiLevelNode->setAttribute("nu", -1);
         maxChildNode->setAttribute("num", 0);
         parentNode->addChild(realParentNode);
         droidNameNode->addChild(realDroidNameNode);

         staticNode->addChild(aiLevelNode);
         staticNode->addChild(parentNode);
         staticNode->addChild(droidNameNode);
         staticNode->addChild(maxChildNode);
      }
      
      
   }
   std::cout << "writing out navNodes ..." << std::endl;
   for(std::vector<navNodeId*>::iterator itr=navNodes.begin();itr!=navNodes.end();itr++)
   {
      XMLNodePtr staticNode(new XMLNode(context));
      XMLNodePtr posNode(new XMLNode(context));
      XMLNodePtr rotNode(new XMLNode(context));
      XMLNodePtr nameNode(new XMLNode(context));
      XMLNodePtr realNameNode(new XMLNode(context));
      
      
      staticNode->setName("navNode");
      posNode->setName("pos");
      rotNode->setName("rot");
      nameNode->setName("name");

               
      
      staticNode->setType(xml_nt_node);
      posNode->setType(xml_nt_leaf);
      nameNode->setType(xml_nt_node);
      rotNode->setType(xml_nt_leaf);
      realNameNode->setType(xml_nt_cdata);
      
      
      levelNode->addChild(staticNode);
      
      posNode->setAttribute("x", (*itr)->worldX);
      posNode->setAttribute("y", (*itr)->worldZ);
      posNode->setAttribute("z", (*itr)->worldY);
      
      staticNode->addChild(posNode);
      rotNode->setAttribute("x", 0.0f);
      rotNode->setAttribute("y", 0.0f);
      rotNode->setAttribute("z", 0.0f);
      staticNode->addChild(rotNode);

      
      std::ostringstream s;
      s << (*itr)->id;
      
      realNameNode->setCdata(s.str());
      nameNode->addChild(realNameNode);
      staticNode->addChild(nameNode);
   }

   std::cout << "writing out NavNodeLinks ... " << std::endl;
   for(std::vector<pair>::iterator itr=navNodeLinks.begin();itr!=navNodeLinks.end();itr++)
   {
      XMLNodePtr staticNode(new XMLNode(context));
      staticNode->setName("navNodeLink");
      staticNode->setType(xml_nt_node);
       
      XMLNodePtr navNode1(new XMLNode(context));
      XMLNodePtr navNode2(new XMLNode(context));
      
      navNode1->setType(xml_nt_node);
      navNode2->setType(xml_nt_node);
      
      navNode1->setName("navNode1");
      navNode2->setName("navNode2");

      XMLNodePtr nameNavNode1(new XMLNode(context));
      XMLNodePtr nameNavNode2(new XMLNode(context));

      nameNavNode1->setType(xml_nt_cdata);
      nameNavNode2->setType(xml_nt_cdata);

      std::ostringstream s1, s2;
      s1 << (*itr).model1->id;
      s2 << (*itr).model2->id;
      
      nameNavNode1->setCdata(s1.str());
      nameNavNode2->setCdata(s2.str());

      
      levelNode->addChild(staticNode);
      staticNode->addChild(navNode1);
      staticNode->addChild(navNode2);
      navNode1->addChild(nameNavNode1);
      navNode2->addChild(nameNavNode2);
      
      
   }
}

std::string trim(const std::string& in)
{
   int beg = in.find_first_not_of(' ');
   int end = in.find_last_not_of(' ');
   return in.substr(beg, in.size() - end);
}

void loadStatic(XMLNodePtr node)
{
   XMLNodePtr pos = node->getChild("pos");
   XMLNodePtr rot = node->getChild("pos");
   std::string model_name = (*node->getChild("model")->getChildren().begin())->getCdata();
   model_name = trim(model_name);

   // Find the corresponding model type in the model menu list
   std::cout << "Looking for model '" << model_name << "'" << std::endl;
   model mod;
   for (std::vector<model>::iterator itr = modelsInMenu.begin();
        itr != modelsInMenu.end();
        ++itr)
   {
      model old_model = *itr;
      if (old_model.name == model_name)
      {
         mod = old_model;
         std::cout << "\tSuccess" << std::endl;
      }
   }


   mod.worldX = pos->getAttribute("x").getValue<float>();
   mod.worldZ = pos->getAttribute("y").getValue<float>();
   mod.worldY = pos->getAttribute("z").getValue<float>();
   mod.name = model_name;

   std::cout << "Adding model: " << mod.name << std::endl
             << "low:  (" << mod.xlo << ", " << mod.ylo << ")" << std::endl
             << "high: (" << mod.xhi << ", " << mod.yhi << ")" << std::endl
             << "pos:  (" << mod.worldX << ", " << mod.worldZ << ", " << mod.worldY << ")" << std::endl;
   modelsInWorld.push_back(mod);
}

void loadGroup(XMLNodePtr node)
{
   XMLNodeList children = node->getChildren();
   for (XMLNodeList::iterator itr = children.begin();
        itr != children.end();
        ++itr)
   {
      XMLNodePtr node = *itr;
      if (node->getName() == "static" || node->getName() == "turret" || node->getName() == "security_droid" || node->getName() == "navNode" )
      {
         loadStatic(node);
      }
   }
}

void loadLevel(const std::string& file)
{
   // Clear the existing level
   modelsInWorld.clear();

   // Read in the level file
   XMLContextPtr context(new XMLContext());
   XMLDocument doc(context);
   std::ifstream in(file.c_str());
   if (!in)
   {
      std::cerr << "bad file: " << file << std::endl;
      return;
   }

   try
   {
      doc.load(in, context);
      XMLNodePtr level_node = doc.getChild("game")->getChild("level");
      XMLNodeList groups = level_node->getChildren("group");
      for (XMLNodeList::iterator itr = groups.begin();
           itr != groups.end();
           ++itr)
      {
         loadGroup(*itr);
      }
   }
   catch (XMLError& e)
   {
      XMLLocation where( context->getLocation() );
      std::string errmsg;
      e.getStrError(errmsg);
      // print out where the error occured
      std::cout << file << ":" << std::cout << file << ":" << where.getLine() << " ";
      std::cout << "at position " << where.getPos();
      std::cout << ": error: " << errmsg.c_str();
      std::cout << std::endl;

      // print out line where the error occured
      std::ifstream errfile( file.c_str() );
      if(!errfile)
      {
         std::cerr << "Can't open file [" << file << "] to output error" << std::endl;
      }

      int linenr = where.getLine();
      char linebuffer[1024];
      for(int i=0; i<linenr && !errfile.eof(); i++)
         errfile.getline( linebuffer,1024 );

      int pos = where.getPos();
      if (pos>=80)
         pos %= 80;

      std::string err_line( linebuffer + (where.getPos()-pos) );
      if (err_line.length()>=79)
         err_line.erase(79);
      std::cout << err_line << std::flush;
      std::cout << err_line.c_str() << std::endl;
      std::cout << linebuffer << std::endl;
      for(int j=2;j<pos;j++)
         std::cout << " ";
      std::cout << '^' << std::endl;
   }
}


void fileFunc(int a)
{
   switch (a)
   {
   case 3: // read in the modelFile to get a list of all the models .. appends to the ones read at startup
      {
         std::cout << "parcing" << std::endl;
         parceobjectsfile(std::string("modelFile.xml"));
         glutSetMenu(menuGetModels);
         for(unsigned int i=0;i<modelsInMenu.size();i++)
         {
            glutAddMenuEntry(modelsInMenu[i].name.c_str(), i+1);
         }
      }
      break;
   case 1: // write the level file out
      {
         std::string tag("<?xml version=\"1.0\"?>\n");
         XMLContextPtr context( new XMLContext);
         XMLNodePtr gameNode(new XMLNode(context));
         XMLNodePtr levelNode(new XMLNode(context));
         XMLNodePtr groupNode(new XMLNode(context));
         gameNode->setName("game");
         gameNode->setType(xml_nt_node);
         levelNode->setName("level");
         levelNode->setType(xml_nt_node);
         groupNode->setName("group");
         groupNode->setType(xml_nt_node);
         
         
         std::cout << "writing level file...";
         XMLDocument docNode( context );
         docNode.addChild(gameNode);
         gameNode->addChild(levelNode);
         levelNode->addChild(groupNode);
         NowWeCanReallyAddTheLevel(groupNode, context);
         std::ofstream ostr( "level.xml" );
         ostr << tag;
         docNode.save( ostr );
         ostr.close();
         std::cout << " Complete" << std::endl;
      }
      break;
   case 2: // load the level file
      {
         loadLevel("level.xml");
      }
      break;
   }
}
void modelFunc(int a)
{
   if(a==2)
   {
      modelsInWorld.clear();
   }
   else if(a==3)
   {
      removeObj=true;
   }
   else if(a==4)
   {
      if(addingNavNodeLink==-1)
         addingNavNodeLink=0;
      std::cout << "adding nav node link: " << addingNavNodeLink << std::endl;
   }
   else if(a==5)
   {
      drawOnMouse=-1;
   }
}
void optionFunc(int a)
{}
void getModelFunc(int a)
{
   //place a copy of the model at the mouse
   drawOnMouse = a;
   // set our process flag
}
void snapFunc(int a)
{
   if(a==1)
      snapOn=true;
   else
      snapOn=false;
}
void gridFunc(int a )
{
   std::cout << "changing gridOn to: " << a << std::endl;
   if(a==1)
      gridOn=true;
   else
      gridOn=false;
}

void myInit(int a)
{
   snapOn=false;
   gridOn=true;
   removeObj=false;
   addingNavNodeLink=-1;
   addingNavNode = 1;
   navNodeCounter = 0;
   
   menuFile = glutCreateMenu(fileFunc);
   menuModel = glutCreateMenu(modelFunc);
   menuOptions = glutCreateMenu(optionFunc);
   menuGetModels = glutCreateMenu(getModelFunc);
   menuSnap = glutCreateMenu(snapFunc);
   menuGrid = glutCreateMenu(gridFunc);
   
   menuMain = glutCreateMenu(menuFunc);
   
   glutAddSubMenu("File", menuFile);
   glutAddSubMenu("Model", menuModel);
   glutAddSubMenu("Options", menuOptions);


   
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   glutSetMenu(menuFile);
   glutAddMenuEntry("write level file", 1);
   glutAddMenuEntry("read level file", 2);
   glutAddMenuEntry("read model file", 3);

   glutSetMenu(menuModel);
   glutAddSubMenu("Add", menuGetModels);
   glutAddMenuEntry("Clear all", 2);
   glutAddMenuEntry("Remove", 3);
   glutAddMenuEntry("Add NavNode", 5);
   glutAddMenuEntry("Add NavNodeLink", 4);

   glutSetMenu(menuOptions);
   glutAddSubMenu("Snap", menuSnap);
   glutAddSubMenu("Grid", menuGrid);

   glutSetMenu(menuSnap);
   glutAddMenuEntry("on", 1);
   glutAddMenuEntry("off", 2);

   glutSetMenu(menuGrid);
   glutAddMenuEntry("on", 1);
   glutAddMenuEntry("off", 2);

   fileFunc(3);
}

int main( int argc, char* argv[] )
{
   
   
    // Initialize the application
    // initialize the state of your app here if needed...
    OnApplicationInit();
   
    // Set the window's initial size
    ::glutInitWindowSize( 640, 640 );
    ::glutInit( &argc, argv );
  
    // Set to double buffer to reduce flicker
    ::glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    
    // Set the window title
    app.mainWin_contextID = ::glutCreateWindow( "GLUT application" );
    
    std::cout<<"\n"<<std::flush;
    std::cout<<"ME519 assignment 2 - by Josh brown - browner@iastate.edu\n"<<std::flush;
    std::cout<<"\n"<<std::flush;
    
    // display callbacks.
    ::glutReshapeFunc( OnReshape );
    ::glutIdleFunc( OnIdle );
    ::glutDisplayFunc( OnRedisplay );
 
    // tell glut to not call the keyboard callback repeatedly 
    // when holding down a key. (uses edge triggering, like the mouse)
    ::glutIgnoreKeyRepeat( 0 );

    // keyboard callback functions.
    ::glutKeyboardFunc( OnKeyboardDown );
    ::glutKeyboardUpFunc( OnKeyboardUp );
    ::glutSpecialFunc( OnSpecialKeyboardDown );
    ::glutSpecialUpFunc( OnSpecialKeyboardUp );

    // mouse callback functions...
    ::glutMouseFunc( OnMouseClick );
    ::glutMotionFunc( OnMousePos );
    ::glutPassiveMotionFunc( OnMousePos );
 
    // start the application loop, your callbacks will now be called
    // time for glut to sit and spin.
    myInit(1);
    
    ::glutMainLoop();
}

