#ifdef WIN32
    #include <windows.h>
#endif
#include <GL/gl.h>    // OpenGL
#include <GL/glut.h>  // ::gl utility library

#include <Matrix4f.h>
#include <NavBall.h> //trackball
#include <HyperBall.h> //trackball

#include <Light.h>
#include <Material.h>

#include "Force.h"

#include "glRenderMaterial.h"
#include "glRenderLight.h"
#include "glClearViewport.h"

#include "MyApp.h"

#include "EulerODEsolver.h"
#include "ModifiedEulerODEsolver.h"
#include "RungeKuttaODEsolver.h"
#include "HeunODEsolver.h"
#include "GState.h"
#include "ImageManager.h"
#include "glTexture.h"
#include "OpenGL/glRender.h"
#include "glParticleSystemRender.h" // Particle render funcs for OGL

// bitmaps...
#include "resources/ballImage.h"
#include "resources/groundhexImage.h"
#include "resources/smokeImage.h"

class TextBeacon
{
public:
   void set( const std::string& t ) { mTimeLeft = 10.0f; mText = t; }
   void growOld( float seconds ) { if (seconds >= 0.0f && seconds <=
   10.0f) mTimeLeft -= seconds; }
   float age() const { return mTimeLeft; }
   const std::string& text() { return mText; }

private:
    float mTimeLeft;
   std::string mText;
} beacon;
int fontBase = 0;
char statusline[256];

GlutKernelApplication::Register< MyApp >* applicationRegistration = new GlutKernelApplication::Register< MyApp >;

kev::GState* groundgstate = NULL;


MyApp::MyApp() : _trackBall( new HyperBall ), stopWatch(), torch(), spiral(), trispring(), sorting( true )
{
   this->setWidth( 800 );
   this->setHeight( 600 );
   this->setName( "particle" );
   
	// add a light to the scene
	Light* newLight = new Light;
	newLight->setNumber( 0 );
	newLight->setColor( Light::ambient, 0.3f, 0.2f, 0.2f );
	newLight->setColor( Light::diffuse, 0.8f, 0.7f, 0.7f );
	newLight->setColor( Light::specular, 1.0f, 1.0f, 1.0f );
	newLight->setPos( 1, 1, 1, 0 );
	newLight->setAtten( 1, 0, 0 );
	_light.push_back( newLight );

   newLight = new Light;
	newLight->setNumber( 1 );
	newLight->setColor( Light::ambient, 0.2f, 0.2f, 0.3f );
	newLight->setColor( Light::diffuse, 0.7f, 0.7f, 0.8f );
	newLight->setColor( Light::specular, 1.0f, 1.0f, 1.0f );
	newLight->setPos( 1, -1, 1, 0 );
	newLight->setAtten( 1, 0, 0 );
	_light.push_back( newLight );

	// init the default material
	_defaultMaterial.setShininess( 0.3f );
	_defaultMaterial.setTransparency( 0.5f );
	_defaultMaterial.setAmbient( 0.3f, 0.3f, 0.3f );
	_defaultMaterial.setDiffuse( 0.8f, 0.8f, 0.8f );
	_defaultMaterial.setSpecular( 1.0f, 1.0f, 1.0f );
	_defaultMaterial.setEmissive( 0.0f, 0.0f, 0.0f );
   
   torch = new Torch;
   spiral = new SpiralThing;
   trispring = new TriSpring;
}

MyApp::~MyApp()
{
	// delete the trackball
	delete _trackBall;
	_trackBall = NULL;

	// delete all lights
	for (int x = 0; x < _light.size(); ++x)
	{
		delete _light[x];
		_light[x] = NULL;
	}
	_light.clear();
   
   torch->deref();
   spiral->deref();
   trispring->deref();
}

//: MyApplication init
//  Called once only.
//  NOTE: When this is called, there is no OpenGL context available.
void MyApp::OnAppInit( int argc, char *argv[] )
{
   beacon.set( "Version 0.2.2" );

   _trackBall->setViewport( TrackBall::top, 0 );
	_trackBall->setViewport( TrackBall::left, 0 );
	_trackBall->setViewport( TrackBall::right, this->width() );
	_trackBall->setViewport( TrackBall::bottom, this->height() );
	_trackBall->setTranslation( 0, 0, 40 );
   _trackBall->setRotation( 10.0f * TO_RAD_F, 1,0,0 );

	// Output a message about what this loader can do.
   cout<<"\n";
   cout<<"* Particle\n";
   cout<<"  Contact Kevin Meinert - KevinMeinert@bigfoot.com for bugs or suggestions.\n"<<flush;
	cout<<"\n";

   groundgstate = new kev::GState;
   groundgstate->texture.setUserData( new kev::glResourceID );
   groundgstate->name = "ground";
   groundgstate->mat.setAmbient( 0.1, 0.1, 0.1 );
   groundgstate->mat.setDiffuse( 0.5, 0.5, 0.5 );
   groundgstate->mat.setSpecular( 0.7, 0.7, 0.7 );
   //groundgstate->mapName = "ground-hex.tga";
   groundgstate->texture.image() = groundhexImage; // defined in groundhexImage.cxx
   /*
   if (ImageManager::instance().load( groundgstate->mapName.c_str(), groundgstate->texture.image() ) == false)
   {
      cout<<"         \""<<groundgstate->mapName.c_str()<<"\" not found.\n"<<flush;
   }
   */
   //groundgstate->texture.model = Texture::DECAL;

   ///////////////////////////////////////////////////////////
   // set up the renderers for the psystems...
   glRenderParticleAsSprite* fire_particle_render = new glRenderParticleAsSprite;
   fire_particle_render->set( smokeImage );
   torchRender.setParticleRender( fire_particle_render );
   fire_particle_render->deref();

   glRenderParticleAsSprite* ball_particle_render = new glRenderParticleAsSprite;
   ball_particle_render->set( ballImage );
   springRender.setParticleRender( ball_particle_render );
   ball_particle_render->deref();

   glRenderParticleAsSprite* water_particle_render = new glRenderParticleAsSprite;
   water_particle_render->set( smokeImage );
   waterRender.setParticleRender( water_particle_render );
   water_particle_render->deref();
}

//: initialization for each GL context (window)
//  NOTE: Called once for every window created
void MyApp::OnContextInit()
{
   cout<<"OnContextInit\n";
	glEnable(GL_TEXTURE_2D);
    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    
    glEnable(GL_LIGHTING); 
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable( GL_COLOR_MATERIAL );
    
    glShadeModel( GL_SMOOTH );
    glEnable(GL_CULL_FACE);   
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 


    //set up font in display list
    cout<<"Loading Helvetica Font\n\n"<<flush;
    fontBase = glGenLists(128);
    for (int i=0; i<128; i++)
    {
        glNewList(fontBase+i, GL_COMPILE);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, i);
        glEndList();
    }
}



void renderStatus(float time)
{
   //draw the text overlay in ortho mode...
    //render perspective
   ::glMatrixMode(GL_MODELVIEW);
   ::glPushMatrix();
      ::glLoadIdentity();     

       glMatrixMode( GL_PROJECTION );
       glPushMatrix();
           glPushAttrib(GL_ENABLE_BIT);
                   glLoadIdentity();
                   glOrtho(-50,50,-50,50,0,500);
                   char buff[256];
                   glDisable(GL_LIGHTING);

                   // Display status line
                   if( beacon.age() > 0 )
                   {
                           glColor4f(1,1,1,1);
                           glListBase(fontBase);
                           glRasterPos3f( -48, 48, 0);
                           glCallLists(beacon.text().size(), GL_BYTE,
                           beacon.text().c_str());
                           beacon.growOld(time);
                   }

                   // Display usage
                   glColor4f(.7,.7,1,1);
                   glListBase(fontBase);
                   glRasterPos3f(-48,-48,0);
                   glCallLists(strlen(statusline), GL_BYTE, statusline);

                   // Display my info
                   sprintf(buff,"Kevin Meinert");
                   glColor4f(1,1,1,1);
                   glListBase(fontBase);
                   glRasterPos3f(-48,-45,0);
                   glCallLists(strlen(buff), GL_BYTE, buff);

           glPopAttrib();
       glPopMatrix();
   ::glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}


//: Do your frame calculations here.
//  NOTE: Called every frame
void MyApp::OnPostFrame()
{
   GlutKernelApplication::OnPostFrame();
   
	stopWatch.stop();
   stopWatch.start();
   
	if (this->keyboard().edgeState( Keyboard::ESC ) == Keyboard::EDGEDOWN ||
      this->keyboard().edgeState( Keyboard::q ) == Keyboard::EDGEDOWN )
   {
      delete applicationRegistration;
		exit(0); 
   }   
   if (this->keyboard().edgeState( Keyboard::r ) == Keyboard::EDGEDOWN)
   {
      trispring->init();
   }
   if (this->keyboard().edgeState( Keyboard::s ) == Keyboard::EDGEDOWN)
   {
      sorting = !sorting;
	}   
   
	// Trackball:
    if(this->mouse().rightEdgeState() == Mouse::DOWN)
    {
		//if( this->modifier() == GLUT_ACTIVE_ALT )
			
		bool usingNavBall = (dynamic_cast<NavBall*>( _trackBall ) != NULL);
		if (!usingNavBall)
		{
         if ( this->modifier() == GLUT_ACTIVE_CTRL )
				_trackBall->applyXYtrans(this->mouse().x(), this->mouse().y(), this->mouse().xOld(), this->mouse().yOld());
			
			else if ( this->modifier() == GLUT_ACTIVE_SHIFT )
				_trackBall->applyZtrans(this->mouse().y(), this->mouse().yOld());
			
			// mouse normally does a rotation
			else 
				_trackBall->applyGeneralRot(this->mouse().x(), this->mouse().y(), this->mouse().xOld(), this->mouse().yOld());
		}
		
		if (usingNavBall)
		{
			if ( this->modifier() == GLUT_ACTIVE_CTRL )
				_trackBall->applyXYtrans(this->mouse().x(), this->mouse().y(), this->mouse().xOld(), this->mouse().yOld());
		
			else if ( this->modifier() == GLUT_ACTIVE_SHIFT )
			{
				_trackBall->applyXrot(this->mouse().y(), this->mouse().yOld());
				_trackBall->applyZrot(this->mouse().x(), this->mouse().xOld());
			} 
			
			// mouse normally does forward, and yaw.
			else 
			{
				_trackBall->applyZtrans(this->mouse().y(), this->mouse().yOld());
				_trackBall->applyYrot(this->mouse().x(), this->mouse().xOld());
			}
		}
	}
   
   sprintf(	statusline, "PS: FPS:%f Particles:%d Operators:%d", stopWatch.fpsAverage, spiral->particles().size() + torch->particles().size() + trispring->particles().size(), spiral->operators().size() + torch->operators().size() + trispring->operators().size() );
   torch->step( stopWatch.timeInstant );
   spiral->step( stopWatch.timeInstant );
   trispring->step( stopWatch.timeInstant );

   Matrix4f projection;
   projection.makePerspective( 80.0f, (float)this->width()/(float)this->height(), 0.1f, 900.0f );
   camera.setProjectionXform( projection );
   camera.setCameraXform( _trackBall->getMatrix() );
}

void drawground()
{
   if (groundgstate != NULL)
   {
      int& textureObjID = kev::getTexObjID( groundgstate->texture );
      if (textureObjID == -1)
      {
         kev::glTextureBind( groundgstate->texture, textureObjID );
      }

      kev::glTextureRender( groundgstate->texture, textureObjID );
   }

   ::glBegin( GL_TRIANGLE_STRIP );
         ::glTexCoord2f( 0.0f, 0.0f );
         ::glColor3f( 0.7f, 1.0f, 0.7f );
         ::glNormal3f( 0.0f, 1.0f, 0.0f ); 
         ::glVertex3f( -7.5, 0.0, -7.5 );

         ::glTexCoord2f( 1.0f, 0.0f );
         ::glColor3f( 1.0f, 0.7f, 0.7f );
         ::glVertex3f( -7.5, 0.0,  7.5 );
         
         ::glTexCoord2f( 0.0f, 1.0f );
         ::glColor3f( 0.7f, 0.7f, 1.0f );
         ::glVertex3f( 7.5, 0.0, -7.5 );

         ::glTexCoord2f( 1.0f, 1.0f );
         ::glColor3f( 1.0f, 1.0f, 1.0f );
         ::glVertex3f( 7.5, 0.0, 7.5 );
      ::glEnd();
}

//////////////////////////////////////////////////
// This is called when the window needs to redraw  
//////////////////////////////////////////////////
void MyApp::OnContextDraw()
{
   ::glDisable( GL_TEXTURE_2D );
   ::glDisable( GL_DEPTH_TEST );
   kev::glClearViewport( 0.3,0.3,0.6, 0.1,0.1,0.1 );
	
   ::glFrontFace( GL_CCW );
   
   ::glEnable( GL_DEPTH_TEST );
   //::glDisable( GL_DEPTH_TEST );
   

   //::glEnable( GL_LIGHTING ); 
   //::glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE );
   //::glEnable( GL_COLOR_MATERIAL );
   
   ::glShadeModel( GL_SMOOTH );
    
    ::glEnable(GL_CULL_FACE);   
    ::glCullFace( GL_BACK );
    
    ::glEnable( GL_BLEND );
    ::glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 

    


    
	 // use perspective for the 3D scene
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();                     
    ::glMultMatrixf( camera.projectionXform().data() );

    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();   
      
 		// render all of the lights
		for (int x = 0; x < _light.size(); ++x)
		{
			::glRender( *_light[x] );
		}

      // render the camera
      ::glMultMatrixf( camera.cameraXform().data() );
      //::glMultMatrixf( camera.matrix().data() );

      renderStatus( stopWatch.timeInstant );
      
		// render the geometry's material
		::glRender( _defaultMaterial );


      ::glEnable( GL_TEXTURE_2D );

      // render the particle system
      const float separation = 25;
		::glPushMatrix();
         ::glTranslatef( -separation, 0, 0 );
         drawground();
         this->torchRender.render( *torch, camera, sorting, true );
      ::glPopMatrix();
     
      ::glPushMatrix();
         ::glTranslatef( separation, 0, 0 );
         drawground();
         this->waterRender.render( *spiral, camera, sorting, true );
      ::glPopMatrix();
      
      ::glPushMatrix();
         ::glTranslatef( 0, 0, separation );
         drawground();
         this->springRender.render( *trispring, camera, sorting, true );
      ::glPopMatrix();
}

//: Window reshape
//  Called on reshape of a window.
//  Put MyApplication code in here.
void MyApp::OnAppReshape(int width, int height)
{
	// call the base class function (to preserve base functionality)
   GlutKernelApplication::OnAppReshape( width, height);
   
	_trackBall->setViewport( TrackBall::top, 0 );
	_trackBall->setViewport( TrackBall::left, 0 );
	_trackBall->setViewport( TrackBall::right, width );
	_trackBall->setViewport( TrackBall::bottom, height );
}

//: Window reshape
//  Called on reshape of a window.
//  Put MyApplication code in here.
void MyApp::OnContextReshape(int width, int height)  
{                 
    // call the base class function (to preserve base functionality)
	GlutKernelApplication::OnContextReshape( width, height );

	::glViewport( 0, 0, width, height );
}
