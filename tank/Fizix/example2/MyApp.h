#ifndef APP_INCLUDED
#define APP_INCLUDED

#include "Mouse.h"
class Light;
#include "Singleton.h"
class TrackBall;
#include "Material.h"
#include "ParticleSystem.h"
#include "ParticleSystemRender.h"
#include "Torch.h"
#include "SpiralThing.h"
#include "TriSpring.h"

#include "GlutKernelApplication.h"
#include "StopWatch.h"
#include "Camera.h"
class MyApp : public GlutKernelApplication
{
// Construction/Destruction
public:
	MyApp();
	virtual ~MyApp();

// Init methods
public:
	virtual void OnAppInit( int argc = 0, char *argv[] = NULL );
	virtual void OnContextInit();

// Idle methods
public:
	void				OnContextDraw();

	//: Do your frame calculations here.
	//  NOTE: Called every frame
	virtual void OnPostFrame();

// Reshape methods
public:
	//: Window reshape
	//  Called on reshape of a window.
	//  Put application code in here.
	virtual void OnAppReshape(int width, int height);

	//: Window reshape for each GL context (window)
	//  Called on reshape of each gl window.
	//  Put GL code in here.
	virtual void OnContextReshape(int width, int height);

// Internal application data
private:
	std::string			stats;
	TrackBall*			_trackBall;
   std::vector<Light*> _light;
	Material			_defaultMaterial;
	Torch*             torch;
   SpiralThing*       spiral;
   TriSpring*         trispring;
	StopWatch			stopWatch;
   Camera            camera;
   bool              sorting;
   ParticleSystemRender torchRender, springRender, waterRender;
};



#endif
