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

float mouseX, mouseY;

class model
{
public:
   model(){
      worldX=0.0f;
      worldY=0.0f;
      worldZ=0.0f;
   }
   float xhi;
   float xlo;
   float yhi;
   float ylo;
   float r,g,b;
   std::string name;
   float worldX, worldY,worldZ;
};


std::vector<model> modelsInWorld;
std::vector<model> modelsInMenu;

float cameraPan[2];


using namespace cppdom;

void processObjNode(XMLNode &node)
{
   model* mModel = new model();
   XMLString name = node.getName();
      
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
   XMLString name = node.getName();
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
      XMLString errmsg;
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

void drawModels()
{
   for(int i=0;i<modelsInWorld.size();i++)
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
   x=x/(SCALE/2)+cameraPan[0]-(app.width/2)/(SCALE/2);
   y=y/(SCALE/2)-cameraPan[1]-(app.height/2)/(SCALE/2);
   std::cout << "x and y: " << x << " "  << y << std::endl;
}

void drawObjAtMouse()
{
   float TEMPSCALE=SCALE/2;
   glColor3f(modelsInMenu[drawOnMouse-1].r, modelsInMenu[drawOnMouse-1].g, modelsInMenu[drawOnMouse-1].b);
   if(snapOn)
   {
      std::cout << "mouseX,Y: " << mouseX << "  " << mouseY << std::endl;
      float tX, tY;
      tX = mouseX;
      tY = mouseY;
      getMouseCoords(tX, tY);
      
      glTranslatef(mouseX, mouseY, 0);
   }else{
      glTranslatef(mouseX, mouseY, 0);
   }
   std::cout << "newMouseX,Y: " << mouseX << "  " << mouseY << std::endl;
   glBegin(GL_POLYGON);
      glVertex2f(modelsInMenu[drawOnMouse-1].xhi*TEMPSCALE, modelsInMenu[drawOnMouse-1].yhi*TEMPSCALE);
      glVertex2f(modelsInMenu[drawOnMouse-1].xlo*TEMPSCALE, modelsInMenu[drawOnMouse-1].yhi*TEMPSCALE);
      glVertex2f(modelsInMenu[drawOnMouse-1].xlo*TEMPSCALE, modelsInMenu[drawOnMouse-1].ylo*TEMPSCALE);
      glVertex2f(modelsInMenu[drawOnMouse-1].xhi*TEMPSCALE, modelsInMenu[drawOnMouse-1].ylo*TEMPSCALE);
   glEnd();
   glTranslatef(-mouseX, -mouseY, 0);
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
   
   // !!!todo!!!: replace the following with your own opengl commands!
   if(gridOn)
   {
      drawGrid(app.width/2);
   }
   drawModels();
   glPushMatrix();
   glTranslatef(5,5,0);

   glPopMatrix();
   
   float tempx, tempy;
   getWorldCoords(tempx, tempy);
   app.cursor.draw(tempx,tempy);
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
   mouseX = (float)x;
   mouseY = (float)y;
}

void addObjToWorld(float& x, float& y)
{
   getWorldCoords(modelsInMenu[drawOnMouse-1].worldX, modelsInMenu[drawOnMouse-1].worldY);
   modelsInWorld.push_back(modelsInMenu[drawOnMouse-1]);
   drawOnMouse=0;
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
      
      
      std::cout << x << " : " << y << std::endl;
      if(drawOnMouse!=0)
         addObjToWorld(x,y);
   }
      
   
   // !!!todo!!!: need mouse interaction?
   //             read the glut docs/manpage to find out how to query 
   //             which button was pressed...
   //             you may have to get this from the glut website 
   //             (use www.google.com to search for it)
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
   std::cout << "size of vector: " << modelsInWorld.size() << std::endl;
   for(int i=0;i<modelsInWorld.size();i++)
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
   }
}


void fileFunc(int a)
{
   if(a==3)
   {
      std::cout << "parcing" << std::endl;
      parceobjectsfile(std::string("modelFile.xml"));
      glutSetMenu(menuGetModels);
      for(int i=0;i<modelsInMenu.size();i++)
      {
         std::cout << "i" << i << std::endl;
         glutAddMenuEntry(modelsInMenu[i].name.c_str(), i+1);
      }
   }else if(a==1)
   {
/*      std::cout << "writing level file...";
      XMLNodePtr levelNode;
      setupOutputLevelFile(levelNode);
      XMLDocumentPtr levelDoc(new XMLDocument);
      levelDoc->addChild(levelNode);
      levelDoc->saveFile(std::string("level.xml"));
 */
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
}
void modelFunc(int a)
{}
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
   std::cout << "changing snapOn to: " << a << std::endl;
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

   glutSetMenu(menuOptions);
   glutAddSubMenu("Snap", menuSnap);
   glutAddSubMenu("Grid", menuGrid);

   glutSetMenu(menuSnap);
   glutAddMenuEntry("on", 1);
   glutAddMenuEntry("off", 2);

   glutSetMenu(menuGrid);
   glutAddMenuEntry("on", 1);
   glutAddMenuEntry("off", 2);
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
    ::glutIgnoreKeyRepeat( 1 );

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

